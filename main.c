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
uint8_t player[7], dealerSelectPlayer, dealerPagaDealer, dealerPagaPlayer, keypad, i;
uint8_t playerAPagar, tablaLedPlayers;
uint8_t respuestaSpi;
uint8_t contador; // usado para los leds, replica en tmr0.c despues borrar
uint32_t monto=0; // usado para guardar el monto
bool botonPulsado_Bet = false, botonPulsado_Hold = false, botonPulsado_CashOut = false, botonPulsado_Clear = false;
char tablaApuestaPlayer[][5] = {{'_','P','P','D','D'},{'_','+','-','+','-'}}; // compensa diferencia de indices con un guion bajo
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
    sprintf(mensajeSpi,"01;B");
    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
    GAME_Status_SetBet(); // Enciende led verde indicando estado Bet
    while(1) // bucle principal del juego
    {        
        // BET equivale a PORTA.RA7 = 1, y Game_Status es PORTA.RA7
        // Inicializacion de variables, estados, indicadores
        monto = 0x00;
        playerAPagar = 0x00;
        tablaLedPlayers = 0x00;
        botonPulsado_Clear = botonPulsado_CashOut = botonPulsado_Bet = botonPulsado_Hold = false;
        GAME_Clear_Players(); // Apaga todos los leds indicadores de los players        
        // ToDo: Escribir algun mensaje en lcd?
        while(GAME_Status){
            // En estado Bet hay 4 posibilidades:
            // 1) Los botones del teclado numero por el monto de la apuesta y el player
            // 2) El pedido de cash out
            // 3) Los botones del player
            // 4) El boton de hold
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
                // ToDo: mostrar/actualizar datos en lcd
            }
            // 2) Cargar monto en un player o marcar para realizar pago
            if(dealerSelectPlayer>0){
                // Hay dos posibilidades: realizar apuesta o marcar player
                // para luego realizar cash out.
                // Almacenamos el player en la variable para indicar con led player
                playerAPagar = dealerSelectPlayer;
                // Enciende el player seleccionado para pagar
                GAME_Set_Player();
                if(monto > 0){
                    // significa que se habia ingresado un monto y esta listo
                    // para comprar creditos se debe enviar mensaje:
                    // 03;NroPlayer;Monto
                    sprintf(mensajeSpi,"03;%u;%u",dealerSelectPlayer,monto);
                    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf(mensajeSpi);
                    // ToDo: mostrar importe en pesos en el LCD, por ejemplo
                    // "Player %u", dealerSelectPlayer
                    // "Monto $ %u", monto
                    monto = 0x00;
                }
            }
            for(i = 0; i < 7; i++){
                if(player[i] > 0){
                    sprintf(mensajeSpi,"05;1;%c;%c",tablaApuestaPlayer[0][player[i]],tablaApuestaPlayer[1][player[i]]);
                    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf(mensajeSpi);
                    // ToDo: codigo de marcar led en caso que player haya apostado a otro player
                    if(player[i] < 3){
                        // esta tabla almacena las apuestas de player a player para luego mostrarlos
                        tablaLedPlayers |= (uint8_t) (0x01 << i);
                    }
                }
            }         
            if(botonPulsado_CashOut){
                if(playerAPagar > 0){
                    botonPulsado_CashOut = false;
                    sprintf(mensajeSpi,"04;%u",playerAPagar);
                    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    // ToDo: deberia esperar respuesta informando la cantidad
                    // ToDo: mensajes en lcd, por ejemplo
                    // "Cash Out Player %u", playerAPagar
                    // "Importe a cobrar $ %s", importe
                    printf(mensajeSpi);
                    GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                    playerAPagar = 0x00; // Elimina valor variable                    
                }
            }
            if(botonPulsado_Clear){
                botonPulsado_Clear = botonPulsado_CashOut = botonPulsado_Bet = botonPulsado_Hold = false;
                monto = 0x00;
                playerAPagar = 0x00;
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                // ToDo: borrar datos lcd
            }
            if(botonPulsado_Hold){
                sprintf(mensajeSpi,"01;H");
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetHold(); // Enciende led rojo indicando estado Hold
            }
            __delay_ms(250); // despues de tantas funciones probable que no sea necesario PROBAR
        }
        // HOLD equivale a PORTA.RA7 = 0, y Game_Status es PORTA.RA7
        // Se encienden los leds de los players que apostaron a players
        GAME_Set_Players();
        while(!GAME_Status){
            // En estado Hold hay X posibilidades:
            // x) El boton de Bet
            ReadCD4014();  // Lee entradas serie
            // Se ignoran las pulsaciones de los players y del teclado numerico
            player[0]=player[1]=player[2]=player[3]=player[4]=player[5]=player[6]=keypad=0x00;
            dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[5]);
            dealerPagaDealer=verificarPagoDealer(&DatosCD4014[6]);
            dealerPagaPlayer=verificarPagoPlayer(&DatosCD4014[7]);
            if(botonPulsado_Bet){
                sprintf(mensajeSpi,"01;B");
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetBet(); // Enciende led rojo indicando estado Hold
            }
            __delay_ms(250);
        }
    }
}