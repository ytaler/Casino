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
    //INTCONbits.PEIE = 1; // Enable interrupts on peripheral
    // EUSAR
    PIR1bits.RCIF = 0; // Clear EUSAR Receive Interrupt Flag
    //PIE1bits.RCIE = 1; // Enable EUSART Receive Interrupt
    IPR1bits.RCIP = 1; // Set High Priority EUSART Interrupt
    // SPI
    PIR1bits.SSPIF = 0;
    //PIE1bits.SSPIE = 1; // Enable SPI Interrupt
    IPR1bits.SSPIP = 1; // Set High Priority SPI Interrupt
}

void interrupt INTERRUPT_InterruptManagerHigh (void)
{
    if(INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1){
        // RB<4:7> pin status change IRQ
        // Corresponde a cash out, bet, hold y clear
        RB47_ISR();
    }
    else{
        if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1){
            // Recepcion EUSART
            printf("\r\n%u\r\n",RCREG);
        }
        else{
            if(PIE1bits.SSPIE == 1 && PIR1bits.SSPIF == 1){
                // Recepcion SPI
            }
            else{
                if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
                    // Desborde TMR0 
                    TMR0_ISR();
                }
                else
                    printf(";00;Error interrupcion no manejada");
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
