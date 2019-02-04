/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F45K20
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45 or later
        MPLAB             :  MPLAB X 4.15
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc.h"
#include "../shift_io.h"
#include "../lcd.h"

void SYSTEM_Initialize(void)
{
    INTERRUPT_Initialize();
    PIN_MANAGER_Initialize(); //
    OSCILLATOR_Initialize(); // 
    SPI_Initialize(); // Used for interact with raspberry pi
    PWM2_Initialize(); // Used for generate the negative voltage for lcd contrast
    TMR2_Initialize(); // Used for PWM
    TMR0_Initialize(); // Used for led blinking on royal stair
    EUSART_Initialize(); //  115200 8N1 @ 16 Mhz
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

void OSCILLATOR_Initialize(void)
{    
//******************************************************************************    
//    OSCCON: OSCILLATOR CONTROL REGISTER
//    bit 7 IDLEN: Idle Enable bit
//        1 = Device enters Idle mode on SLEEP instruction
//        0 = Device enters Sleep mode on SLEEP instruction
    OSCCONbits.IDLEN=0b0;
//    bit 6-4 IRCF<2:0>: Internal Oscillator Frequency Select bits
//        111 = 16 MHz (HFINTOSC drives clock directly)
//        110 = 8 MHz
//        101 = 4 MHz
//        100 = 2 MHz
//        011 = 1 MHz
//        010 = 500 kHz
//        001 = 250 kHz
//        000 = 31 kHz (from either HFINTOSC/512 or LFINTOSC directly)
    OSCCONbits.IRCF=0b111;
//    bit 3 OSTS: Oscillator Start-up Time-out Status bit
//        1 = Device is running from the clock defined by FOSC<2:0> of the CONFIG1 register
//        0 = Device is running from the internal oscillator (HFINTOSC or LFINTOSC)
    OSCCONbits.OSTS=0b1;
//    bit 2 IOFS: HFINTOSC Frequency Stable bit --> 1 estable
//        1 = HFINTOSC frequency is stable
//        0 = HFINTOSC frequency is not stable
    OSCCONbits.IOFS=0b1;
//    bit 1-0 SCS<1:0>: System Clock Select bits --> 00 segun configuracion de registro CONFIG1 (bits de configuracion)
//        1x = Internal oscillator block
//        01 = Secondary (Timer1) oscillator
//        00 = Primary clock (determined by CONFIG1H[FOSC<3:0>]).
    OSCCONbits.SCS=0b00;

//******************************************************************************
//    OSCTUNE: OSCILLATOR TUNING REGISTER
//    bit 7 INTSRC: Internal Oscillator Low-Frequency Source Select bit
//        1 = 31.25 kHz device clock derived from 16 MHz HFINTOSC source (divide-by-512 enabled)
//        0 = 31 kHz device clock derived directly from LFINTOSC internal oscillator
    OSCTUNEbits.INTSRC=0b0;
//    bit 6 PLLEN: Frequency Multiplier PLL for HFINTOSC Enable bit (1)
//        1 = PLL enabled for HFINTOSC (8 MHz and 16 MHz only)
//        0 = PLL disabled
    OSCTUNEbits.PLLEN=0b0;
//    bit 5-0 TUN<5:0>: Frequency Tuning bits
//        011111 = Maximum frequency
//        011110 =
//        ? ? ?
//        000001 =
//        000000 = Oscillator module is running at the factory calibrated frequency.
//        111111 =
//        ? ? ?
//        100000 = Minimum frequency
    OSCTUNEbits.TUN=0b000000;
}


/**
 End of File
*/
