/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F45K20
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

#define GAME_Clear_Players()        do { PORTA = (uint8_t)(PORTA & 0x80); } while (0)
#define GAME_Set_Player()           do { PORTA = (uint8_t) ((uint8_t)(PORTA & 0x80) | (uint8_t)( 0x01 << (playerAPagar-1))); } while (0)
#define GAME_Set_Players()           do { PORTA = (uint8_t) ((uint8_t)(PORTA & 0x80) | (uint8_t) tablaLedPlayers ); } while (0)

// ****************************************************************************
// ********************               PORT A               ********************
// ****************************************************************************

// get/set LED_PLAYER_1_OUT aliases
#define LED_PLAYER_1_OUT_TRIS                 TRISAbits.TRISA0
#define LED_PLAYER_1_OUT_LAT                  LATAbits.LATA0
#define LED_PLAYER_1_OUT_PORT                 PORTAbits.RA0
#define LED_PLAYER_1_OUT_ANS                  ANSELbits.ANS0
#define LED_PLAYER_1_OUT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_PLAYER_1_OUT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_PLAYER_1_OUT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_PLAYER_1_OUT_GetValue()           PORTAbits.RA0
#define LED_PLAYER_1_OUT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_PLAYER_1_OUT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_PLAYER_1_OUT_SetAnalogMode()      do { ANSELbits.ANS0 = 1; } while(0)
#define LED_PLAYER_1_OUT_SetDigitalMode()     do { ANSELbits.ANS0 = 0; } while(0)

// get/set LED_PLAYER_2_OUT aliases
#define LED_PLAYER_2_OUT_TRIS                 TRISAbits.TRISA1
#define LED_PLAYER_2_OUT_LAT                  LATAbits.LATA1
#define LED_PLAYER_2_OUT_PORT                 PORTAbits.RA1
#define LED_PLAYER_2_OUT_ANS                  ANSELbits.ANS1
#define LED_PLAYER_2_OUT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_PLAYER_2_OUT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_PLAYER_2_OUT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_PLAYER_2_OUT_GetValue()           PORTAbits.RA1
#define LED_PLAYER_2_OUT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_PLAYER_2_OUT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_PLAYER_2_OUT_SetAnalogMode()      do { ANSELbits.ANS1 = 1; } while(0)
#define LED_PLAYER_2_OUT_SetDigitalMode()     do { ANSELbits.ANS1 = 0; } while(0)

// get/set LED_PLAYER_3_OUT aliases
#define LED_PLAYER_3_OUT_TRIS                 TRISAbits.TRISA2
#define LED_PLAYER_3_OUT_LAT                  LATAbits.LATA2
#define LED_PLAYER_3_OUT_PORT                 PORTAbits.RA2
#define LED_PLAYER_3_OUT_ANS                  ANSELbits.ANS2
#define LED_PLAYER_3_OUT_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_PLAYER_3_OUT_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_PLAYER_3_OUT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_PLAYER_3_OUT_GetValue()           PORTAbits.RA2
#define LED_PLAYER_3_OUT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_PLAYER_3_OUT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_PLAYER_3_OUT_SetAnalogMode()      do { ANSELbits.ANS2 = 1; } while(0)
#define LED_PLAYER_3_OUT_SetDigitalMode()     do { ANSELbits.ANS2 = 0; } while(0)

// get/set LED_PLAYER_4_OUT aliases
#define LED_PLAYER_4_OUT_TRIS                 TRISAbits.TRISA3
#define LED_PLAYER_4_OUT_LAT                  LATAbits.LATA3
#define LED_PLAYER_4_OUT_PORT                 PORTAbits.RA3
#define LED_PLAYER_4_OUT_ANS                  ANSELbits.ANS3
#define LED_PLAYER_4_OUT_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED_PLAYER_4_OUT_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED_PLAYER_4_OUT_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED_PLAYER_4_OUT_GetValue()           PORTAbits.RA3
#define LED_PLAYER_4_OUT_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED_PLAYER_4_OUT_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED_PLAYER_4_OUT_SetAnalogMode()      do { ANSELbits.ANS3 = 1; } while(0)
#define LED_PLAYER_4_OUT_SetDigitalMode()     do { ANSELbits.ANS3 = 0; } while(0)

// get/set LED_PLAYER_5_OUT aliases
#define LED_PLAYER_5_OUT_TRIS                 TRISAbits.TRISA4
#define LED_PLAYER_5_OUT_LAT                  LATAbits.LATA4
#define LED_PLAYER_5_OUT_PORT                 PORTAbits.RA4
#define LED_PLAYER_5_OUT_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED_PLAYER_5_OUT_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED_PLAYER_5_OUT_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED_PLAYER_5_OUT_GetValue()           PORTAbits.RA4
#define LED_PLAYER_5_OUT_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED_PLAYER_5_OUT_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set LED_PLAYER_6_OUT aliases
#define LED_PLAYER_6_OUT_TRIS                 TRISAbits.TRISA5
#define LED_PLAYER_6_OUT_LAT                  LATAbits.LATA5
#define LED_PLAYER_6_OUT_PORT                 PORTAbits.RA5
#define LED_PLAYER_6_OUT_ANS                  ANSELbits.ANS4
#define LED_PLAYER_6_OUT_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_PLAYER_6_OUT_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_PLAYER_6_OUT_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_PLAYER_6_OUT_GetValue()           PORTAbits.RA5
#define LED_PLAYER_6_OUT_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_PLAYER_6_OUT_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_PLAYER_6_OUT_SetAnalogMode()      do { ANSELbits.ANS4 = 1; } while(0)
#define LED_PLAYER_6_OUT_SetDigitalMode()     do { ANSELbits.ANS4 = 0; } while(0)

// get/set LED_PLAYER_7_OUT aliases
#define LED_PLAYER_7_OUT_TRIS                 TRISAbits.TRISA6
#define LED_PLAYER_7_OUT_LAT                  LATAbits.LATA6
#define LED_PLAYER_7_OUT_PORT                 PORTAbits.RA6
#define LED_PLAYER_7_OUT_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED_PLAYER_7_OUT_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED_PLAYER_7_OUT_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED_PLAYER_7_OUT_GetValue()           PORTAbits.RA6
#define LED_PLAYER_7_OUT_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED_PLAYER_7_OUT_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; }

// get/set IO_RA7 aliases
#define IO_RA7_TRIS                 TRISAbits.TRISA7
#define IO_RA7_LAT                  LATAbits.LATA7
#define IO_RA7_PORT                 PORTAbits.RA7
#define IO_RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define IO_RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define IO_RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define IO_RA7_GetValue()           PORTAbits.RA7
#define IO_RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define IO_RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
// Porta Bit7 = Salida Led Bet (verde) / Hold (rojo)
#define GAME_Status                 PORTAbits.RA7 // Alias del pin
#define GAME_Status_SetBet()        IO_RA7_SetLow()
#define GAME_Status_SetHold()       IO_RA7_SetHigh()
#define GAME_Status_Toggle()        IO_RA7_Toggle()

// ****************************************************************************
// ********************               PORT B               ********************
// ****************************************************************************

// get/set IO_RB0 aliases
#define IO_RB0_TRIS                 TRISBbits.TRISB0
#define IO_RB0_LAT                  LATBbits.LATB0
#define IO_RB0_PORT                 PORTBbits.RB0
#define IO_RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_RB0_GetValue()           PORTBbits.RB0
#define IO_RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
// PORTB Bit0 = Boton de Seguridad Pago Dealer
#define botonPagoDealer             PORTBbits.RB0 // Alias del pin

// get/set IO_RB1 aliases
#define IO_RB1_TRIS                 TRISBbits.TRISB1
#define IO_RB1_LAT                  LATBbits.LATB1
#define IO_RB1_PORT                 PORTBbits.RB1
#define IO_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_RB1_GetValue()           PORTBbits.RB1
#define IO_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
// PORTB Bit1 = Boton de Seguridad Pago Player
#define botonPagoPlayer             PORTBbits.RB1 // Alias del pin

// get/set RB3 procedures --> PWM para tension negativa fuente lcd
#define RB3_SetHigh()               do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()                do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()                do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()       do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()      do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELHbits.ANS9 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELHbits.ANS9 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
// PORTB Bit4 = Entrada boton Bet
#define BotonBet                    PORTBbits.RB4 // Alias del pin

// get/set IO_RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
// PORTB Bit5 = Entrada boton Bet
#define BotonHold                    PORTBbits.RB5 // Alias del pin

// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
// PORTB Bit6 = Entrada boton CashOut
#define BotonCashOut                 PORTBbits.RB6 // Alias del pin

// get/set IO_RB7 aliases
#define IO_RB7_TRIS                 TRISBbits.TRISB7
#define IO_RB7_LAT                  LATBbits.LATB7
#define IO_RB7_PORT                 PORTBbits.RB7
#define IO_RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IO_RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IO_RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define IO_RB7_GetValue()           PORTBbits.RB7
#define IO_RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IO_RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
// PORTB Bit7 = Entrada boton Clear
#define BotonClear                 PORTBbits.RB7 // Alias del pin

// ****************************************************************************
// ********************               PORT C               ********************
// ****************************************************************************

// get/set IO_RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
// PortC Bit0 = Salida CLK serie CD4014
#define CLK_CD4014                  PORTCbits.RC0 // Alias del pin CLK para CD4014
#define CLK_CD4014_SetHigh()        IO_RC0_SetHigh()
#define CLK_CD4014_SetLow()         IO_RC0_SetLow()
#define CLK_CD4014_Toggle()         IO_RC0_Toggle()

// get/set IO_RC1 aliases
#define IO_RC1_TRIS                 TRISCbits.TRISC1
#define IO_RC1_LAT                  LATCbits.LATC1
#define IO_RC1_PORT                 PORTCbits.RC1
#define IO_RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_RC1_GetValue()           PORTCbits.RC1
#define IO_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
// PortC Bit1 = Entrada datos serie
#define DATA_CD4014                 PORTCbits.RC1 // Alias del pin DATA para CD4014
#define DATA_CD4014_GetValue()      IO_RC1_GetValue()

// get/set IO_RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
// PortC Bit2 = Salida LOAD serie entradas
#define LOAD_CD4014                 PORTCbits.RC2 // Alias del pin CLK para CD4014
#define LOAD_CD4014_SetHigh()       IO_RC2_SetHigh()
#define LOAD_CD4014_SetLow()        IO_RC2_SetLow()
#define LOAD_CD4014_Toggle()        IO_RC2_Toggle()

// get/set SCK aliases
#define SCK_TRIS                 TRISCbits.TRISC3
#define SCK_LAT                  LATCbits.LATC3
#define SCK_PORT                 PORTCbits.RC3
#define SCK_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCK_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCK_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCK_GetValue()           PORTCbits.RC3
#define SCK_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set SDI aliases
#define SDI_TRIS                 TRISCbits.TRISC4
#define SDI_LAT                  LATCbits.LATC4
#define SDI_PORT                 PORTCbits.RC4
#define SDI_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDI_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDI_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDI_GetValue()           PORTCbits.RC4
#define SDI_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set SDO aliases
#define SDO_TRIS                 TRISCbits.TRISC5
#define SDO_LAT                  LATCbits.LATC5
#define SDO_PORT                 PORTCbits.RC5
#define SDO_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDO_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDO_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDO_GetValue()           PORTCbits.RC5
#define SDO_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

// get/set TX aliases
#define TX_TRIS                 TRISCbits.TRISC6
#define TX_LAT                  LATCbits.LATC6
#define TX_PORT                 PORTCbits.RC6
#define TX_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define TX_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define TX_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define TX_GetValue()           PORTCbits.RC6
#define TX_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

// get/set RX aliases
#define RX_TRIS                 TRISCbits.TRISC7
#define RX_LAT                  LATCbits.LATC7
#define RX_PORT                 PORTCbits.RC7
#define RX_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RX_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RX_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RX_GetValue()           PORTCbits.RC7
#define RX_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)

// ****************************************************************************
// ********************               PORT D               ********************
// ****************************************************************************
#define LCD_PORT                    PORTD

// get/set IO_RD0 aliases
#define IO_RD0_TRIS                 TRISDbits.TRISD0
#define IO_RD0_LAT                  LATDbits.LATD0
#define IO_RD0_PORT                 PORTDbits.RD0
#define IO_RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define IO_RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define IO_RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define IO_RD0_GetValue()           PORTDbits.RD0
#define IO_RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define IO_RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set IO_RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set IO_RD2 aliases
#define IO_RD2_TRIS                 TRISDbits.TRISD2
#define IO_RD2_LAT                  LATDbits.LATD2
#define IO_RD2_PORT                 PORTDbits.RD2
#define IO_RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define IO_RD2_GetValue()           PORTDbits.RD2
#define IO_RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define IO_RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set IO_RD3 aliases
#define IO_RD3_TRIS                 TRISDbits.TRISD3
#define IO_RD3_LAT                  LATDbits.LATD3
#define IO_RD3_PORT                 PORTDbits.RD3
#define IO_RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define IO_RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define IO_RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define IO_RD3_GetValue()           PORTDbits.RD3
#define IO_RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define IO_RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

// get/set IO_RD4 aliases
#define IO_RD4_TRIS                 TRISDbits.TRISD4
#define IO_RD4_LAT                  LATDbits.LATD4
#define IO_RD4_PORT                 PORTDbits.RD4
#define IO_RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IO_RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define IO_RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define IO_RD4_GetValue()           PORTDbits.RD4
#define IO_RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define IO_RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
// PortD Bit4 = Salida E (Enable) para LCD
#define LCD_E_SetHigh()             IO_RD4_SetHigh()
#define	LCD_E_SetLow()              IO_RD4_SetLow()

// get/set IO_RD5 aliases
#define IO_RD5_TRIS                 TRISDbits.TRISD5
#define IO_RD5_LAT                  LATDbits.LATD5
#define IO_RD5_PORT                 PORTDbits.RD5
#define IO_RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define IO_RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define IO_RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define IO_RD5_GetValue()           PORTDbits.RD5
#define IO_RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define IO_RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
// PortD Bit5 = Salida RS (RegisterSelect) para LCD
#define	LCD_RS_SetHigh()            IO_RD5_SetHigh()
#define	LCD_RS_SetLow()             IO_RD5_SetLow()

// get/set IO_RD6 aliases
#define IO_RD6_TRIS                 TRISDbits.TRISD6
#define IO_RD6_LAT                  LATDbits.LATD6
#define IO_RD6_PORT                 PORTDbits.RD6
#define IO_RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define IO_RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define IO_RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define IO_RD6_GetValue()           PORTDbits.RD6
#define IO_RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define IO_RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
// PortD Bit6 = Salida RW (ReadWrite) para LCD
#define	LCD_RW_SetHigh()            IO_RD6_SetHigh()
#define	LCD_RW_SetLow()             IO_RD6_SetLow()

// get/set IO_RD7 aliases
#define IO_RD7_TRIS                 TRISDbits.TRISD7
#define IO_RD7_LAT                  LATDbits.LATD7
#define IO_RD7_PORT                 PORTDbits.RD7
#define IO_RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define IO_RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define IO_RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define IO_RD7_GetValue()           PORTDbits.RD7
#define IO_RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define IO_RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
// PortD Bit7 = Salida control rele para VGND
#define	SYSTEM_Power_On()           IO_RD7_SetHigh()
#define	SYSTEM_Power_Off()          IO_RD7_SetLow()

// ****************************************************************************
// ********************               PORT E               ********************
// ****************************************************************************

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */

#endif // PIN_MANAGER_H
/**
 End of File
*/