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
uint8_t contador = 1, player[8];
uint8_t oldDatosCD4014[NumeroCD4014];

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Initialize I/O and Peripherals for application */
    SYSTEM_Initialize();
    printf("UART Conectada\r\n");
    while(1)
    {
        ReadCD4014();  // Lee entradas serie
        if ((DatosCD4014[0] != oldDatosCD4014[0]) ||
            (DatosCD4014[1] != oldDatosCD4014[1]) ||
            (DatosCD4014[2] != oldDatosCD4014[2]) ||
            (DatosCD4014[3] != oldDatosCD4014[3]))
        {
            // Muestra los datos leidos solo si ha habido cambios
            printf("DatosCD4014 [0]:%02X  [1]:%02X  [2]:%02X  [3]:%02X\r\n",
            DatosCD4014[0], DatosCD4014[1], DatosCD4014[2], DatosCD4014[3]);
        }
        // Usado para comparar si ha habido cambios en las entradas
        oldDatosCD4014[0]=DatosCD4014[0];
        oldDatosCD4014[1]=DatosCD4014[1];
        oldDatosCD4014[2]=DatosCD4014[2];
        oldDatosCD4014[3]=DatosCD4014[3];
        // Se individualizan los valores leidos en una variable por player
        // Se normalizan todas las lecturas de los players a LSB
        // Para los players impares en donde el dato esta en MSB, se hace un shift
        // de 4 posiciones de tal modo que quede en el LSB
        // 7 players
        player[0]=verificarBotones(DatosCD4014[0]);
        player[1]=verificarBotones(DatosCD4014[0] >> 4);
        player[2]=verificarBotones(DatosCD4014[1]);
        player[3]=verificarBotones(DatosCD4014[1] >> 4);
        player[4]=verificarBotones(DatosCD4014[2]);
        player[5]=verificarBotones(DatosCD4014[2] >> 4);
        player[6]=verificarBotones(DatosCD4014[3]);
        // 
        __delay_ms(250);
    }
}