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
#include "lcd.h"

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
bool botonPulsado_PagoDealer = false, botonPulsado_PagoPlayer = false; 
char mensajeSpi[15];
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    // la inicializacion debe hacerlo de tal forma de dejar todos los disp
    // listos pero apagados o en stand by
    SYSTEM_Initialize();
    // funciones de comunicacion:
    // 1) printf --> escritura en uart
    // 2) lcd_puts --> escritura en lcd
    // 3) SPI_Exchange8bit y SPI_Exchange8bitBuffer --> escritura SPI
    LCD_BackLight_Off();
    printf("Inicio de sistema NetPozos\r\nEsperando activacion de mesa");
    lcd_command_8bit(LCD_CLEAR_DISPLAY);
    lcd_puts("Sistema NetPozos");
    sprintf(mensajeSpi,"02");
    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
    respuestaSpi = 0x00;
    // ToDo: respuesta SPI por IRQ o respuesta directa de mnesaje .. VER!!!
    while(respuestaSpi == 'I'){
        // chequeo si la mesa esta activa cada 5 segundos
        //sprintf(mensajeSpi,"02;"); // ya fue escrito anteriormente asi que no es necesario, se reusa
        SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
        //printf("02;%c\r\n", respuestaSpi);
        __delay_ms(5000);
    }
    LCD_BackLight_On();
    printf("Mesa activada, inicio de juego");
    lcd_command_8bit(LCD_CLEAR_DISPLAY);
    lcd_puts("Mesa Activada");
    lcd_command_8bit(LCD_SEGUNDA_LINEA);
    lcd_puts("Comienza juego");
    // Una vez activado el sistema se procede al bucle principal, comenzando
    // por el estado bet (01;B)
    sprintf(mensajeSpi,"01;B");
    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
    printf(mensajeSpi);
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
                    lcd_command_8bit(LCD_CLEAR_DISPLAY);
                    lcd_puts(sprintf("Player %u",dealerSelectPlayer));
                    lcd_command_8bit(LCD_SEGUNDA_LINEA);
                    lcd_puts(sprintf("Monto $ %u", monto));
                    monto = 0x00;
                }
            }
            for(i = 0; i < 7; i++){
                if(player[i] > 0){
                    sprintf(mensajeSpi,"05;1;%c;%c",tablaApuestaPlayer[0][player[i]],tablaApuestaPlayer[1][player[i]]);
                    SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf(mensajeSpi);
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
                    // usar respuestaSpi
                    lcd_command_8bit(LCD_CLEAR_DISPLAY);
                    lcd_puts(sprintf("Player %u",dealerSelectPlayer));
                    lcd_command_8bit(LCD_SEGUNDA_LINEA);
                    lcd_puts(sprintf("A cobrar $%u", monto));
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
                lcd_command_8bit(LCD_CLEAR_DISPLAY);
            }
            if(botonPulsado_Hold){
                sprintf(mensajeSpi,"01;H");
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf(mensajeSpi);
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetHold(); // Enciende led rojo indicando estado Hold
            }
            __delay_ms(250); // despues de tantas funciones probable que no sea necesario PROBAR
        }
        // HOLD equivale a PORTA.RA7 = 0, y Game_Status es PORTA.RA7
        // Se encienden los leds de los players que apostaron a players
        GAME_Set_Players();
        botonPulsado_Clear = botonPulsado_PagoDealer = botonPulsado_PagoPlayer = false;
        player[0]=player[1]=player[2]=player[3]=player[4]=player[5]=player[6]=0x00;
        playerAPagar = 0x00;
        while(!GAME_Status){
            // En estado Hold hay X posibilidades:
            // x) El boton de Bet
            ReadCD4014();  // Lee entradas serie
            // Se ignoran las pulsaciones de los players y del teclado numerico
            keypad = verificarTecladoNumerico((uint8_t)(DatosCD4014[3] >> 4),&DatosCD4014[4]);
            dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[5]);
            dealerPagaDealer=verificarPagoDealer(&DatosCD4014[6]);
            dealerPagaPlayer=verificarPagoPlayer(&DatosCD4014[7]);
            if(dealerSelectPlayer > 0){
                // almacenar el numero de player a pagar
                playerAPagar = dealerSelectPlayer;
            }
            if( (dealerPagaDealer > 0) && (botonPulsado_PagoDealer) ){
                botonPulsado_PagoDealer = false;
                // se deben pulsar las dos teclas simultaneamente por seguridad
                sprintf(mensajeSpi,"06;0;%u",dealerPagaDealer);
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf(mensajeSpi);
                // ToDo: mostrar mensaje de pago premio en lcd
                lcd_command_8bit(LCD_CLEAR_DISPLAY);
                lcd_puts("Ap. Dealer");
                lcd_command_8bit(LCD_SEGUNDA_LINEA);
                lcd_puts(premios[dealerPagaDealer]);
            }
            if( (dealerPagaPlayer > 0) && (botonPulsado_PagoPlayer) && (playerAPagar > 0) ){
                botonPulsado_PagoPlayer = false;
                // se debe elegir primero el nro de player a pagar y luego el premio
                // ademas de pulsar la tecla de pago por seguridad
                sprintf(mensajeSpi,"06;%u;%u",playerAPagar,dealerPagaDealer);
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf(mensajeSpi);
                lcd_command_8bit(LCD_CLEAR_DISPLAY);
                lcd_puts(sprintf("Ap. Player %u",playerAPagar));
                lcd_command_8bit(LCD_SEGUNDA_LINEA);
                lcd_puts(premios[dealerPagaPlayer]);           
                playerAPagar = 0x00;
            }
            if( (keypad == 1) && (botonPulsado_Clear) ){
                // se deben cancelar todos los pagos
                botonPulsado_Clear = botonPulsado_PagoDealer = botonPulsado_PagoPlayer = false;
                sprintf(mensajeSpi,"07");
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf(mensajeSpi);
                lcd_command_8bit(LCD_CLEAR_DISPLAY);
            }
            if(botonPulsado_Bet){
                sprintf(mensajeSpi,"01;B");
                SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf(mensajeSpi);
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetBet(); // Enciende led rojo indicando estado Hold
            }
            __delay_ms(250);
        }
    }
}