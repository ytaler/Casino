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
uint8_t contador = 1, player[8], dealerSelectPlayer, dealerPagaDealer, dealerPagaPlayer;
uint8_t oldDatosCD4014[NumeroCD4014];

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    // la inicializacion debe hacerlo de tal forma de dejar todos los disp
    // listos pero apagados o en stand by
    SYSTEM_Initialize();    
    printf("Inicio de sistema NetPozos\r\n");
    while(SPI_Exchange8bit(0x02)=='I'){
        // chequeo si la mesa esta activa cada 5 segundos
        __delay_ms(5000);
    }
    // Una vez activado el sistema se procede al bucle principal, comenzando
    // por el estado bet
    while(1)
    {
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
        //keypad =
        dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[4]);
        dealerPagaDealer=verificarPagoDealer(&DatosCD4014[5]);
        dealerPagaPlayer=verificarPagoPlayer(&DatosCD4014[6]);
        __delay_ms(250);
    }
}