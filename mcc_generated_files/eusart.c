/**
  EUSART Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.c

  @Summary
    This is the generated driver implementation file for the EUSART driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for EUSART.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F45K20
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */
#include "eusart.h"

/**
  Section: EUSART APIs
 */

void EUSART_Initialize(void) {
    
    /* BAUDCON: BAUD RATE CONTROL REGISTER - Pagina 248 manual
     * 
     * ABDOVF: Auto-Baud Detect Overflow bit = 0 --> Asynchronous mode: Auto-baud timer did not overflow
     * RCIDL: Receive Idle Flag bit = 0 --> Start bit has been detected and the receiver is active
     * DTRXP: Data/Receive Polarity Select bit = 0 --> Asynchronous mode: Receive data (RX) is not inverted (active-high)
     * CKTXP: Clock/Transmit Polarity Select bit = 0 --> Asynchronous mode: Idle state for transmit (TX) is high
     * 
     * BRG16: 16-bit Baud Rate Generator bit = 1 --> 1 = 16-bit Baud Rate Generator is used (SPBRGH:SPBRG)
     * Unimplemented: Read as ?0?
     * WUE: Wake-up Enable bit = 0 --> Asynchronous mode: Receiver is operating normally
     * ABDEN: Auto-Baud Detect Enable bit = 0 --> Auto-Baud Detect mode is disabled
     */
    BAUDCON = 0b00001000;

    /* RCSTA: RECEIVE STATUS AND CONTROL REGISTER - Pagina 247 manual
     * 
     * SPEN: Serial Port Enable bit = 1 --> Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
     * RX9: 9-bit Receive Enable bit = 0 --> Selects 8-bit reception
     * SREN: Single Receive Enable bit = 0 --> Asynchronous mode: Don?t care
     * CREN: Continuous Receive Enable bit = 1 --> Asynchronous mode: Enables receiver
     * 
     * ADDEN: Address Detect Enable bit = 0 --> Asynchronous mode 8-bit (RX9 = 0): Don?t care
     * FERR: Framing Error bit = 0 --> No framing error
     * OERR: Overrun Error bit = 0 --> No overrun error
     * RX9D: Ninth bit of Received Data = 0 --> This can be address/data bit or a parity bit and must be calculated by user firmware.
     */
    RCSTA = 0b10010000;
    
    /* TXSTA: TRANSMIT STATUS AND CONTROL REGISTER - Pagina 246 manual
     * 
     * CSRC: Clock Source Select bit = 0 --> Don't care in asynchronous mode.
     * TX9: 9-bit Transmit Enable bit = 0 --> Selects 8-bit transmission
     * TXEN: Transmit Enable bit = 1 --> Transmit enabled
     * SYNC: EUSART Mode Select bit = 0 --> Asynchronous mode
     * 
     * SENDB: Send Break Character bit = 0 --> Sync Break transmission completed
     * BRGH: High Baud Rate Select bit = 1 --> High speed
     * TRMT: Transmit Shift Register Status bit = 1 --> TSR empty
     * TX9D: Ninth bit of Transmit Data = 0 --> Can be address/data bit or a parity bit.
     */ 
    TXSTA = 0b00100110;

    // Estos valores dependen del clock del micro!! REVISAR!! Pagina 252
    // Para SYNC=0, BGRH=1 y BGR16=1 a 4 MHz el valor para 9600 baudios con un error de 0,16 es 103=0x067
    // Esta configuración se conoce como 8N1. Para utilizar con minicom desactivar control de flujo por hardware.
    SPBRGH=0x00;
    //SPBRG=0x67;    
    SPBRG=34; // para 16 mhz
    //SPBRG=103; // para 4 mhz
    //SPBRG=138; // para 64 mhz
}

bool EUSART_is_tx_ready(void)
{
    return (bool)(PIR1bits.TX1IF && TXSTAbits.TXEN);
}

bool EUSART_is_rx_ready(void)
{
    return PIR1bits.RC1IF;
}

bool EUSART_is_tx_done(void)
{
    return TXSTAbits.TRMT;
}

uint8_t EUSART_Read(void) {

    while (!PIR1bits.RCIF) {
    }

    if (1 == RCSTAbits.OERR) {
        // EUSART error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    return RCREG;
}

void EUSART_Write(uint8_t txData) {
    while (0 == PIR1bits.TXIF) {
    }

    TXREG = txData; // Write the data byte to the USART.
}

char getch(void) {
    return EUSART_Read();
}

void putch(char txData) {
    EUSART_Write(txData);
}
/**
  End of File
 */
