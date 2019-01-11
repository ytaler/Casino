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
    //INTCON2bits.TMR0IP = 1; // TMRI - high priority

    // Set PORTB bits 4:7 change interrupt para las señales de:
    // Bet, Hold, CashOut, Clear
    INTCONbits.RBIF = 0; // Clear PORTB change interrupt flag before enabling the interrupt
    IOCB = 0xF0; // Enable all four individual interrupts on PORTB <7:4> bits change.
    INTCON2bits.RBIP = 1; // RBI <4:7> - high priority
    INTCONbits.RBIE = 1; // Enabling RB Port Change interrupt.
    
    // Set RB0 external interrupt para la señal de Pago Dealer
    INTCONbits.INT0IF = 0; // Clear RB0 external Interrupt flag before enabling the interrupt
    INTCON2bits.INTEDG0 = 1; // Interrupt RB0 on rising edge
    // RB0 external interrupt is always high priority
    INTCONbits.INT0IE = 1; // Enabling PORTB pin 0 external interrupt
    
    // Set RB1 external interrupt para la señal de Pago Player
    INTCON3bits.INT1F = 0; // Clear RB1 external Interrupt flag before enabling the interrupt
    INTCON2bits.INTEDG1 = 1; // Interrupt RB1 on rising edge
    INTCON3bits.INT1IP = 1; // RB1 - high priorityg edge    
    INTCON3bits.INT1E = 1; // Enabling PORTB pin 0 external interrupt
}

void interrupt INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
        // TMR0 IRQ
        TMR0_ISR();
    }
    else{
        if(INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1){
            // RB<4:7> pin status change IRQ
            RB47_ISR();
        }
        else
        {
            if(INTCONbits.INT0IE == 1 && INTCONbits.INT0IF == 1){
                // RB0 external IRQ
                RB0_ISR();
            }
            else{
                if(INTCON3bits.INT1E == 1 && INTCON3bits.INT1F == 1){
                    // RB1 external IRQ
                    RB1_ISR();
                }
                else{
                    //Unhandled Interrupt, no deberia pasar por aca
                    printf("Error: unhandled interrupt\r\n");
                }
            }
        }
    }
}

void RB47_ISR(void)
{   
    extern bool botonPulsado_Bet, botonPulsado_Hold, botonPulsado_CashOut, botonPulsado_Clear;
	// Clear global Interrupt-On-Change flag
    INTCONbits.RBIF = 0;

    if (BotonBet) botonPulsado_Bet = true;
    if (BotonHold) botonPulsado_Hold = true;    
    if (BotonCashOut) botonPulsado_CashOut = true;    
    if (BotonClear) botonPulsado_Clear = true;  
}

void RB0_ISR(void)
{   
    extern bool botonPulsado_PagoDealer;
    // cuando entra a esta subrutina sifnifica que se disparo segun la config
    // del flanco en INTCON2bits.INTEDG0, si es 1, es ascendente por lo que 
    // no hace falta IF, sino que se asigna la variable directamente    
    botonPulsado_PagoDealer = true;
}

void RB1_ISR(void)
{   
    extern bool botonPulsado_PagoPlayer;
    // cuando entra a esta subrutina sifnifica que se disparo segun la config
    // del flanco en INTCON2bits.INTEDG1, si es 1, es ascendente por lo que 
    // no hace falta IF, sino que se asigna la variable directamente    
    botonPulsado_PagoPlayer = true;
}

/**
 End of File
*/
