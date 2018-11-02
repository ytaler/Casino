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
 * controlarian led de estado hold/bet y led de players: un led por cada player
 * y el ultimo pin conmuuta entre hold (rojo) y bet (verde)
 * RA0: Player 1
 * RA1: Player 2
 * RA2: Player 3
 * RA3: Player 4
 * RA4: Player 5
 * RA5: Player 6
 * RA6: Player 7
 * RA7: Bet (verde) / Hold (rojo)
 * - PORTB -
 * RB0: Boton Seguridad Pago Dealer
 * RB1: Boton Seguridad Pago Player
 * RB2: libre
 * RB3: PWM para alimentacion negativa lcd
 * RB4: Bet
 * RB5: Hold
 * RB6: Cash out
 * RB7: Clear
 * - PORTC -
 * RC0: Shift registers clock 
 * RC1: Entrada datos serie shift registers
 * RC2: Salida pin load shift registers
 * RC3: SPI CLK (clock SPI)
 * RC4: SDI (serial data input)
 * RC5: SDO (serial data output)
 * RC6: USART TX
 * RC7: USART RX
 * - PORTD -
 * RD0: LCD data bus line 0
 * RD1: LCD data bus line 1
 * RD2: LCD data bus line 2
 * RD3: LCD data bus line 3
 * RD4: Señal E (enable) LCD
 * RD5: Señal RS (register select) LCD
 * RD6: ToDo: Señal RW (Read Write) LCD
 * RD7: ToDo: Control BackLight LCD.
 * - PORTE -
*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"

void PIN_MANAGER_Initialize(void)
{
    // LATx registers
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    // TRISx regusters --> Ver mapa de Pines arriba
    TRISA = 0x00; // 0000 - 0000
    TRISB = 0xF7; // 1111 - 0111
    TRISC = 0x92; // 1001 - 0010
    TRISD = 0x00; // 0000 - 0000
    TRISE = 0x07; // xxxx - x111 
    
    // ANSELx registers
    ANSEL = 0x00; // Apagar entradas analogicas
    ANSELH = 0x00; // Apagar entradas analogicas    
    
    // WPUx registers
    WPUB = 0x00; // deshabilita r pull up para puerto b
    INTCON2bits.nRBPU = 1; // Desabilita resistencias pull up

    /**
    ODx registers
    */
}

/**
 End of File
*/