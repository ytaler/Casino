/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F45K20
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
 * PIN MAP
 * - PORTA -
 * - PORTB -
 * - PORTC -
 * RC0: Shift registers clock 
 * RC1: Entrada datos serie shift registers
 * RC2: Salida load shift registers
 * RC3: SPI CLK (clock SPI)
 * RC4: SDI (serial data input)
 * RC5: SDO (serial data output)
 * RC6: USART TX
 * RC7: USART RX
 * - PORTD -
 * RD0: ahora led, proximo paso lcd
 * RD1: ahora led, proximo paso lcd
 * RD2: ahora led, proximo paso lcd
 * RD3: ahora led, proximo paso lcd
 * RD4: ahora led, proximo paso lcd
 * RD5: ahora led, proximo paso lcd
 * RD6: ahora led, proximo paso lcd
 * RD7: ahora led, proximo paso lcd
 * - PORTE -
*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx regusters --> Ver mapa de Pines arriba
    */
    TRISE = 0x07;
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0x92; // 1001 - 0010
    TRISD = 0x00; // en este puerto estan conectados los leds

    /**
    ANSELx registers
    */
    ANSEL = 0x00; // Apagar entradas analogicas
    ANSELH = 0x00; // Apagar entradas analogicas    
    
    /**
    WPUx registers
    */
    WPUB = 0x00; // deshabilita r pull up para puerto b
    INTCON2bits.nRBPU = 1; // Desabilita resistencias pull up

    /**
    ODx registers
    */    
}
  
void PIN_MANAGER_IOC(void)
{   
	// Clear global Interrupt-On-Change flag
    INTCONbits.RBIF = 0;
}

/**
 End of File
*/