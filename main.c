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

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

int ciclos = 0;
uint8_t contador = 1;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Initialize I/O and Peripherals for application */
    SYSTEM_Initialize();

    uint8_t firstDigit, secondDigit, state, state2, state3;
    
    printf("UART Conectada\r\n");
    firstDigit = '0';
    PORTD = contador;
    while(1)
    {
        printf("Bienvenido al sistema, por favor ingrese una opcion: ");
        secondDigit = EUSART_Read();
        printf("\r\nUsted eligio: %c%c = ",firstDigit, secondDigit);
        switch (secondDigit)
        {
            case '1':
                printf("Infomacion de estado de juego\r\nSeleccione el estado hold(H) o bet(B): ");
                state = toupper(EUSART_Read());
                while ((state != 'B') && (state != 'H'))
                {
                    printf("\r\nEl comando ingresado no es correcto. Ingrese H o B: ");
                    state = toupper(EUSART_Read());
                }
                printf("\r\nEl comando a enviar es: %c%c;%c\r\n", firstDigit, secondDigit, state);
                break;
            case '2':
                printf("Consultar estado de la mesa\r\nSeleccione el estado de la mesa, inactiva(I) o activa(A): ");
                state = toupper(EUSART_Read());
                while ((state != 'A') && (state != 'I'))
                {
                    printf("\r\nEl comando ingresado no es correcto. Ingrese A o I: ");
                    state = toupper(EUSART_Read());
                }
                printf("\r\nEl comando a enviar es: %c%c;%c\r\n", firstDigit, secondDigit, state);
                break;
            case '3':
                printf("Informar compra de Creditos\r\n");
                state = toupper(EUSART_Read());
                printf("\r\nEl comando a enviar es: %c%c;%c\r\n", firstDigit, secondDigit, state);
                break;
            case '4':
                printf("Informar Cash Out\r\nIngrese el numero de player de 1 a 7: ");
                state = toupper(EUSART_Read());
                while ((state > '7') || (state < '1'))
                {
                    printf("\r\nEl player ingresado no es correcto. Ingrese un valor de 1 a 7: ");
                    state = EUSART_Read();
                }
                printf("\r\nEl comando a enviar es: %c%c;%c\r\n", firstDigit, secondDigit, state);
                
                // Este comando espera respuesta!!! el formato es 04;xx en donde xx el producto
                // de la cantidad de créditos por el costo de c/u 
                
                break;
            case '5':
                printf("Informar Apuesta del Player\r\nIngrese el numero de player de 1 a 7: ");
                state = EUSART_Read();
                // 49 es '1' y 55 '7' en ASCII
                //printf("\t%u\r\n", state);
                while ((state > '7') || (state < '1'))
                {
                    printf("\r\nEl player ingresado no es correcto. Ingrese un valor de 1 a 7: ");
                    state = EUSART_Read();
                }
                printf("\r\nAhora ingrese a quien le realiza la apuesta, delaer (D) o player (P): ");
                state2 = toupper(EUSART_Read());
                while ((state2 != 'D') && (state2 != 'P'))
                {
                    printf("\r\nEl valor ingresado no es correcto. Ingrese D o P: ");
                    state2 = toupper(EUSART_Read());
                }
                printf("\r\nPor ultimo ingrese que tipo de apuesta, mas (+) o menos (-): ");
                state3 = EUSART_Read();
                while ((state3 != '+') && (state3 != '-'))
                {
                    printf("\r\nEl valor ingresado no es correcto. Ingrese + o -: ");
                    state3 = EUSART_Read();
                }
                printf("\r\nEl comando a enviar es: %c%c;%c;%c;%c\r\n", firstDigit, secondDigit, state, state2, state3);
                break;
            case '6':
                printf("Informar Pago Realizado\r\n");
                state = toupper(EUSART_Read());
                printf("\r\nEl comando a enviar es: %c%c;%c\r\n", firstDigit, secondDigit, state);
                break;
            case '7':
                printf("Informar Cancelacion de Pagos\r\n");
                printf("\r\nEl comando a enviar es: %c%c\r\n", firstDigit, secondDigit);
                break;
            default:
                printf("Se ingreso una opcion invalida:\r\n");
        }
        contador <<= 1;
        if ( (contador > 128) || (contador == 0) ){
            contador = 1;
        }
        PORTD = contador;
        __delay_ms(500);
    }

}

