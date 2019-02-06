/**
  Generated Interrupt Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F45K20
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45 or later
        MPLAB 	          :  MPLAB X 4.15
*/

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors
    INTCON2bits.TMR0IP = 0; // TMRI - low priority

    // Set PORTB bits 4:7 change interrupt para las señales de:
    // Bet, Hold, CashOut, Clear
    INTCONbits.RBIF = 0; // Clear PORTB change interrupt flag before enabling the interrupt
    IOCB = 0xF0; // Enable all four individual interrupts on PORTB <7:4> bits change.
    INTCON2bits.RBIP = 1; // RBI <4:7> - high priority
    INTCONbits.RBIE = 1; // Enabling RB Port Change interrupt.
    
    // Ahora se habilita para los perifericos
    INTCONbits.PEIE = 1; // Enable interrupts on peripheral
    // EUSARTRC1IF
    PIR1bits.RCIF = 0; // Clear EUSART Receive Interrupt Flag
    PIE1bits.RCIE = 1; // Enable EUSART Receive Interrupt
    IPR1bits.RCIP = 1; // Set High Priority EUSART Interrupt
    // SPI
    //PIR1bits.SSPIF = 0;
    //PIE1bits.SSPIE = 1; // Enable SPI Interrupt
    //IPR1bits.SSPIP = 1; // Set High Priority SPI Interrupt
}

void interrupt INTERRUPT_InterruptManagerHigh (void)
{
    uint8_t uartTemp, uartTempAntes;
    extern bool finTransmision;
    extern uint8_t indiceRespuesta;
    extern char respuestaRaspBerryPi[18];
    
    if(INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1){
        // RB<4:7> pin status change IRQ
        // Corresponde a cash out, bet, hold y clear
        RB47_ISR();
    }
    else{
        if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1){
            // Recepcion EUSART
            // A 115200 Baudios, deberia tomar 174 us aprox en recibir todos los datos, 8,6 us aprox por dato
            PIR1bits.RCIF = 0;
            uartTemp = RCREG;
            //printf("*Valor: %u - Char: %c*\r\n",uartTemp,uartTemp);
            if( (indiceRespuesta == 0) && (uartTemp == '|') ){
                // significa comienzo de string, necesariamente debe venir '|' primero para indicar inicio
                respuestaRaspBerryPi[indiceRespuesta] = uartTemp;
                indiceRespuesta++;
            }
            else{
                // caso contrario suponemos que ya recibio el primer byte
                // por lo que verificamos que sea asi
                //uartTemp = (uint8_t) toupper((char) uartTemp);
                if( (indiceRespuesta > 0) && (indiceRespuesta < 18) ){
                    uartTempAntes = uartTemp;
                    filtroCaracteres(&uartTemp);
                    respuestaRaspBerryPi[indiceRespuesta] = uartTemp;
                    if(uartTemp == uartTempAntes)
                        indiceRespuesta++;
                    else{
                        // sino fin de mensaje
                        indiceRespuesta = 0x00;
                        finTransmision = true;
                    }
                }
                else{
                    // sino por seguridad anulamos mensaje
                    respuestaRaspBerryPi[indiceRespuesta] = 0x00;
                    indiceRespuesta = 0x00;
                    finTransmision = true;
                }                
            }
        }
        else{
            if(PIE1bits.SSPIE == 1 && PIR1bits.SSPIF == 1){
                // Recepcion SPI
                PIR1bits.SSPIF = 0;
                printf("|00;SPI IRQ");
            }
            else{
                if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
                    // Desborde TMR0 
                    TMR0_ISR();
                }
                else
                    printf("|00;Error interrupcion no manejada");
            }
        }
    }

}

void RB47_ISR(void)
{   
    extern bool botonPulsado_Bet, botonPulsado_Hold, botonPulsado_CashOut, botonPulsado_Clear;
	// Clear flag
    INTCONbits.RBIF = 0;

    if (BotonBet) botonPulsado_Bet = true;
    if (BotonHold) botonPulsado_Hold = true;    
    if (BotonCashOut) botonPulsado_CashOut = true;    
    if (BotonClear) botonPulsado_Clear = true;  
}

void filtroCaracteres(uint8_t *caracter){
    // verificamos que no se sea un valor menor a 48 (numero cero en ascii)
    if(*caracter < 48)
        *caracter = 0x00;
    else{
        // sino verificamos que no sea un numero mayor a 102 (letra f ascii)
        if(*caracter > 102){
            // la excepcion es letra i
            if(*caracter != 105)
                *caracter = 0x00;
        }
        else{
            // luego sigue la franja despues de 9 y antes de A
            if( (*caracter > 57) && (*caracter < 65) ){
                if(*caracter != 59)
                    *caracter = 0x00;
            }
            else{
                // luego sigue franja despues de F y antes de a
                if( (*caracter > 70) && (*caracter < 97) ){
                    // caso especial mantener I
                    if(*caracter != 73)
                        *caracter = 0x00;
                }
            }
        }
    }
}