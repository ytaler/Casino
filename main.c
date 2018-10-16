/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <ctype.h>

#endif

#include "mcc_generated_files/mcc.h"
#include "shift_io.h"
#include "net_pozos.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

int ciclos = 0;
uint8_t player[7], dealerSelectPlayer, dealerPagaDealer, dealerPagaPlayer, keypad;
uint8_t playerAPagar=0;
uint8_t respuestaSpi;
uint8_t contador; // usado para los leds, replica en tmr0.c despues borrar
uint32_t monto=0; // usado para guardar el monto
char mensajeSpi[15];
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    // la inicializacion debe hacerlo de tal forma de dejar todos los disp
    // listos pero apagados o en stand by
    SYSTEM_Initialize();    
    printf("Inicio de sistema NetPozos\r\n");
    SPI_Exchange8bit('0');
    respuestaSpi = SPI_Exchange8bit('2');
    printf("02;%c\r\n", respuestaSpi);
    while(respuestaSpi == 'I'){
        // chequeo si la mesa esta activa cada 5 segundos
        SPI_Exchange8bit('0');
        respuestaSpi = SPI_Exchange8bit('2');
        printf("02;%c\r\n", respuestaSpi);
        __delay_ms(5000);
    }
    // Una vez activado el sistema se procede al bucle principal, comenzando
    // por el estado bet (01;B)
    while(1) // bucle principal del juego
    {        
        sprintf(mensajeSpi,"01;B");
        SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
        GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
        GAME_Status_SetBet(); // Enciende led verde indicando estado Bet
        // BET equivale a PORTA.RA7 = 1, y Game_Status es PORTA.RA7
        while(GAME_Status){
            // En estado Bet hay 4 posibilidades:
            // 1) Los botones del teclado numero por el monto de la apuesta y el player
            // 2) El pedido de cash out
            // 3) Los botones del player
            // 4) El boton de hold --> ¿deberia ir a un RB para detectar por irq?
            ReadCD4014();  // Lee entradas serie
            // Se individualizan los valores leidos en una variable por player
            // Se normalizan todas las lecturas de los players a LSB
            // Para los players impares en donde el dato esta en MSB, se hace un shift
            // de 4 posiciones de tal modo que quede en el LSB
            // 7 players
            player[0]=verificarBotonesPlayer(DatosCD4014[0]);
            player[1]=verificarBotonesPlayer((uint8_t)(DatosCD4014[0] >> 4));
            player[2]=verificarBotonesPlayer(DatosCD4014[1]);
            player[3]=verificarBotonesPlayer((uint8_t)(DatosCD4014[1] >> 4));
            player[4]=verificarBotonesPlayer(DatosCD4014[2]);
            player[5]=verificarBotonesPlayer((uint8_t)(DatosCD4014[2] >> 4));
            player[6]=verificarBotonesPlayer(DatosCD4014[3]);
            keypad = verificarTecladoNumerico((uint8_t)(DatosCD4014[3] >> 4),&DatosCD4014[4]);
            dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[5]);
            // Una vez leidas todas las variables se procede a la toma de decisiones.
            // 1) Primero se calcula el monto de la apuesta (si es que cambio / hay)
            if(keypad>0){
                monto *= 10;
                monto += keypad;
                // Acciones a realizar: mostrar/actualizar datos en lcd
            }
            // 2) Cargar monto en un player o marcar para realizar pago
            if(dealerSelectPlayer>0){
                // Hay dos posibilidades: realizar apuesta o marcar player
                // para luego realizar cash out.
                if(monto > 0){
                    // significa que se habia ingresado un monto y esta listo
                    // para comprar creditos se debe enviar mensaje:
                    // 03;NroPlayer;Monto
                    sprintf(mensajeSpi,"03;%u;%u",dealerSelectPlayer,monto);
                    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf(mensajeSpi);
                }
                else{
                    // marcar player para esperar el cash out
                    playerAPagar = dealerSelectPlayer;
                    // Enciende el player seleccionado para pagar
                    GAME_Set_Player();
                }
            }
            // testear cash out, hold, y clear.
            // si es cash out se debe retirar dinero
            // si es hold se debe cambiar de estado 
            // si es clear se debe borrar el monto, apagar led players, borrar lcd...
            __delay_ms(250);
        }
        sprintf(mensajeSpi,"01;H");
        SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
        GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
        GAME_Status_SetHold(); // Enciende led rojo indicando estado Hold
        while(!GAME_Status){
            // En estado Hold hay X posibilidades:
            // x) El boton de Bet --> ¿deberia ir a un RB para detectar por irq?
            ReadCD4014();  // Lee entradas serie
            // Se ignoran las pulsaciones de los players
            dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[5]);
            dealerPagaDealer=verificarPagoDealer(&DatosCD4014[6]);
            dealerPagaPlayer=verificarPagoPlayer(&DatosCD4014[7]);
            __delay_ms(250);
        }
    }
}