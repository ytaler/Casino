/******************************************************************************/
/* Ver explicacion en                                                         */
/* file:///opt/microchip/xc8/v2.00/docs/chips/18f45k20.html                   */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

//******************************************************************************
//    CONFIG1H: CONFIGURATION REGISTER 1 HIGH
//    bit 7 IESO: Internal/External Oscillator Switchover bit
//        1 = Oscillator Switchover mode enabled
//        0 = Oscillator Switchover mode disabled
//    bit 6 FCMEN: Fail-Safe Clock Monitor Enable bit
//        1 = Fail-Safe Clock Monitor enabled
//        0 = Fail-Safe Clock Monitor disabled
//    bit 5-4 Unimplemented: Read as ?0?
//    bit 3-0 FOSC<3:0>: Oscillator Selection bits
//        11xx = External RC oscillator, CLKOUT function on RA6
//        101x = External RC oscillator, CLKOUT function on RA6
//        1001 = Internal oscillator block, CLKOUT function on RA6, port function on RA7
//        1000 = Internal oscillator block, port function on RA6 and RA7
//        0111 = External RC oscillator, port function on RA6
//        0110 = HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
//        0101 = EC oscillator, port function on RA6
//        0100 = EC oscillator, CLKOUT function on RA6
//        0011 = External RC oscillator, CLKOUT function on RA6
//        0010 = HS oscillator
//        0001 = XT oscillator
//        0000 = LP oscillator

#pragma config IESO = OFF // OFF es 0
#pragma config FCMEN = OFF // OFF es 0
#pragma config FOSC = INTIO67 // INTIO67 es 1000 = Internal oscillator block, port function on RA6 and RA7

//******************************************************************************
//    CONFIG2L: CONFIGURATION REGISTER 2 LOW
//    bit 7-5 Unimplemented: Read as ?0?
//    bit 4-3 BORV<1:0>: Brown-out Reset Voltage bits
//        11 = V BOR set to 1.8V nominal
//        10 = V BOR set to 2.2V nominal
//        01 = V BOR set to 2.7V nominal
//        00 = V BOR set to 3.0V nominal
//    bit 2-1 BOREN<1:0>: Brown-out Reset Enable bits
//        11 = Brown-out Reset enabled in hardware only (SBOREN is disabled)
//        10 = Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
//        01 = Brown-out Reset enabled and controlled by software (SBOREN is enabled)
//        00 = Brown-out Reset disabled in hardware and software
//    bit 0 nPWRTEN: Power-up Timer Enable bit
//        1 = PWRT disabled
//        0 = PWRT enabled

#pragma config BORV = 30 // 30	VBOR set to 3.0 V nominal
#pragma config BOREN = SBORDIS // SBORDIS es 11
#pragma config PWRT = ON // ON es 0

//******************************************************************************
//    CONFIG2H: CONFIGURATION REGISTER 2 HIGH
//    bit 7-5 Unimplemented: Read as ?0?
//    bit 4-1 WDTPS<3:0>: Watchdog Timer Postscale Select bits
//        1111 = 1:32,768
//        1110 = 1:16,384
//        1101 = 1:8,192
//        1100 = 1:4,096
//        1011 = 1:2,048
//        1010 = 1:1,024
//        1001 = 1:512
//        1000 = 1:256
//        0111 = 1:128
//        0110 = 1:64
//        0101 = 1:32
//        0100 = 1:16
//        0011 = 1:8
//        0010 = 1:4
//        0001 = 1:2
//        0000 = 1:1
//    bit 0 WDTEN: Watchdog Timer Enable bit
//        1 = WDT is always enabled. SWDTEN bit has no effect
//        0 = WDT is controlled by SWDTEN bit of the WDTCON registe

#pragma config WDTPS = 32768
#pragma config WDTEN = OFF // OFF es 0

//******************************************************************************
//    CONFIG3H: CONFIGURATION REGISTER 3 HIGH
//    bit 7 MCLRE: MCLR Pin Enable bit
//        1 = MCLR pin enabled; RE3 input pin disabled
//        0 = RE3 input pin enabled; MCLR disabled
//    bit 6-4 Unimplemented: Read as ?0?
//    bit 3 HFOFST: HFINTOSC Fast Start-up
//        1 = HFINTOSC starts clocking the CPU without waiting for the oscillator to stabilize.
//        0 = The system clock is held off until the HFINTOSC is stable.
//    bit 2 LPT1OSC: Low-Power Timer1 Oscillator Enable bit
//        1 = Timer1 configured for low-power operation
//        0 = Timer1 configured for higher power operation
//    bit 1 PBADEN: PORTB A/D Enable bit
//        (Affects ANSELH Reset state. ANSELH controls PORTB<4:0> pin configuration.)
//        1 = PORTB<4:0> pins are configured as analog input channels on Reset
//        0 = PORTB<4:0> pins are configured as digital I/O on Reset
//    bit 0 CCP2MX: CCP2 MUX bit
//        1 = CCP2 input/output is multiplexed with RC1
//        0 = CCP2 input/output is multiplexed with RB3

#pragma config MCLRE = ON // ON es 1
#pragma config HFOFST = OFF // OFF es 0
#pragma config LPT1OSC = OFF // OFF es 0
#pragma config PBADEN = OFF // OFF es 0
#pragma config CCP2MX = PORTBE // CCP2 input/output is multiplexed with RC1

//******************************************************************************
//    CONFIG4L: CONFIGURATION REGISTER 4 LOW
//    bit 7 DEBUG: Background Debugger Enable bit
//        1 = Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
//        0 = Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
//    bit 6 XINST: Extended Instruction Set Enable bit
//        1 = Instruction set extension and Indexed Addressing mode enabled
//        0 = Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
//    bit 5-3 Unimplemented: Read as ?0?
//    bit 2 LVP: Single-Supply ICSP Enable bit
//        1 = Single-Supply ICSP enabled
//        0 = Single-Supply ICSP disabled
//    bit 1 Unimplemented: Read as ?0?
//    bit 0 STVREN: Stack Full/Underflow Reset Enable bit
//        1 = Stack full/underflow will cause Reset
//        0 = Stack full/underflow will not cause Reset
        
#pragma config DEBUG = OFF // OFF es 1
#pragma config XINST = OFF // OFF es 0
#pragma config LVP = OFF // OFF es 0
#pragma config STVREN = ON // ON es 1

//******************************************************************************
//    CONFIG5L: CONFIGURATION REGISTER 5 LOW
//    bit 7-4 Unimplemented: Read as ?0?
//    bit 3 CP3: Code Protection bit - Block 3 (006000-007FFFh)
//        1 = Block 3 not code-protected
//        0 = Block 3 code-protected
//    bit 2 CP2: Code Protection bit - Block 2 (004000-005FFFh)
//        1 = Block 2 not code-protected
//        0 = Block 2 code-protected
//    bit 1 CP1: Code Protection bit
//        1 = Block 1 not code-protected - Block 1 (002000-003FFFh)
//        0 = Block 1 code-protected
//    bit 0 CP0: Code Protection bit
//        1 = Block 0 not code-protected - Block 0 (000800-001FFFh)
//        0 = Block 0 code-protected

#pragma config CP3 = OFF // Off es 1
#pragma config CP2 = OFF // Off es 1
#pragma config CP1 = OFF // Off es 1
#pragma config CP0 = OFF // Off es 1

//******************************************************************************
//    CONFIG5H: CONFIGURATION REGISTER 5 HIGH
//    bit 7 CPD: Data EEPROM Code Protection bit
//        1 = Data EEPROM not code-protected
//        0 = Data EEPROM code-protected
//    bit 6 CPB: Boot Block Code Protection bit - Block 0 (000000-0007FFh)
//        1 = Boot Block not code-protected
//        0 = Boot Block code-protected
//    bit 5-0 Unimplemented: Read as ?0?

#pragma config CPD = OFF // Off es 1
#pragma config CPB = OFF // Off es 1

//******************************************************************************
//    CONFIG6L: CONFIGURATION REGISTER 6 LOW
//    bit 7-4 Unimplemented: Read as ?0?
//    bit 3 WRT3: Write Protection bit - Block 3 (006000-007FFFh)
//        1 = Block 3 not write-protected
//        0 = Block 3 write-protected
//    bit 2 WRT2: Write Protection bit - Block 2 (004000-005FFFh)
//        1 = Block 2 not write-protected
//        0 = Block 2 write-protected
//    bit 1 WRT1: Write Protection bit - Block 1 (002000-003FFFh)
//        1 = Block 1 not write-protected
//        0 = Block 1 write-protected
//    bit 0 WRT0: Write Protection bit - Block 0 (000800-001FFFh)
//        1 = Block 0 not write-protected
//        0 = Block 0 write-protected

#pragma config WRT3 = OFF // Off es 1
#pragma config WRT2 = OFF // Off es 1
#pragma config WRT1 = OFF // Off es 1
#pragma config WRT0 = OFF // Off es 1

//******************************************************************************
//    CONFIG6H: CONFIGURATION REGISTER 6 HIGH
//    bit 7 WRTD: Data EEPROM Write Protection bit
//        1 = Data EEPROM not write-protected
//        0 = Data EEPROM write-protected
//    bit 6 WRTB: Boot Block Write Protection bit (000000-0007FFh)
//        1 = Boot Block not write-protected
//        0 = Boot Block write-protected
//    bit 5 WRTC: Configuration Register Write Protection bit (300000-3000FFh)
//        1 = Configuration registers not write-protected
//        0 = Configuration registers write-protected
//    bit 4-0 Unimplemented: Read as ?0?

#pragma config WRTD = OFF // Off es 1
#pragma config WRTB = OFF // Off es 1
#pragma config WRTC = OFF // Off es 1

//******************************************************************************
//    CONFIG7L: CONFIGURATION REGISTER 7 LOW
//    bit 7-4 Unimplemented: Read as ?0?
//    bit 3 EBTR3: Table Read Protection bit - Block 3 (006000-007FFFh)
//        1 = Block 3 not protected from table reads executed in other blocks
//        0 = Block 3 protected from table reads executed in other blocks
//    bit 2 EBTR2: Table Read Protection bit - Block 2 (004000-005FFFh)
//        1 = Block 2 not protected from table reads executed in other blocks
//        0 = Block 2 protected from table reads executed in other blocks
//    bit 1 EBTR1: Table Read Protection bit - Block 1 (002000-003FFFh)
//        1 = Block 1 not protected from table reads executed in other blocks
//        0 = Block 1 protected from table reads executed in other blocks
//    bit 0 EBTR0: Table Read Protection bit - Block 0 (000800-001FFFh)
//        1 = Block 0 not protected from table reads executed in other blocks
//        0 = Block 0 protected from table reads executed in other blocks

#pragma config EBTR3 = OFF // Off es 1
#pragma config EBTR2 = OFF // Off es 1
#pragma config EBTR1 = OFF // Off es 1
#pragma config EBTR0 = OFF // Off es 1

//******************************************************************************
//    CONFIG7H: CONFIGURATION REGISTER 7 HIGH
//    bit 7 Unimplemented: Read as ?0?
//    bit 6 EBTRB: Boot Block Table Read Protection bit - Boot Block (000000-0007FFh)
//        1 = Boot Block not protected from table reads executed in other blocks
//        0 = Boot Block protected from table reads executed in other blocks
//    bit 5-0 Unimplemented: Read as ?0?

#pragma config EBTRB = OFF // Off es 1