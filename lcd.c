/*
 * lcd.c
 *
 *  Created on: 15/11/2012
 *      Author: ytaler
 */

#include "lcd.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"

/*--------------------------------------------------------------------------*/
/*	Enable and disable E signal (strobe)										*/
/*--------------------------------------------------------------------------*/
void lcd_strobe(void){
    // debe tener un minimo total de 280 ns, 140 ns cada pulso.
    // A 16 Mhz, deberiamos tener un pulso a 250 ns + los 3 NOP de 250 ns hacen
    // un total de 1 us, para cada pulso.
	LCD_E_SetHigh();
	;
	;
	;
	LCD_E_SetLow();
	;
	;
	;
}
/*--------------------------------------------------------------------------*/
/*	Escribir datos de 4 bits												*/
/*--------------------------------------------------------------------------*/
void lcd_write(unsigned char c){
	unsigned char lsn; //Less significant nibble
	unsigned char msn; //Most significant nibble
	__delay_us(LCD_ETIME_2);	// Retardo de 42 us que demora en completar una instruccion
	msn = ( ( c >> 4 ) & 0x0F );
	lsn = ( c & 0x0F );
    LCD_PORT = ((LCD_PORT & 0xF0) | (msn));
	lcd_strobe();
    LCD_PORT = ((LCD_PORT & 0xF0) | (lsn));
	lcd_strobe();
}
/*--------------------------------------------------------------------------*/
/*	Escribir comandos de 8 bits												*/
/*--------------------------------------------------------------------------*/
void lcd_command_8bit (unsigned const char c){
	LCD_RS_SetLow();			// Pongo en cero RS
	LCD_RW_SetLow();			// Pongo en cero RW
	lcd_write(c);
	if((c==LCD_CLEAR_DISPLAY)||(c==LCD_RETURN_HOME))
		__delay_us(LCD_ETIME_1);
}
/*--------------------------------------------------------------------------*/
/*	Escribir un caracter													*/
/*--------------------------------------------------------------------------*/
void lcd_putc(unsigned char c) {
	LCD_RS_SetHigh();			// Pongo en uno RS
	LCD_RW_SetLow();			// Pongo en cero RW
	lcd_write(c);
}
/*--------------------------------------------------------------------------*/
/*	Escribir un string													*/
/*--------------------------------------------------------------------------*/
void lcd_puts(const char * s) {
	LCD_RS_SetHigh();			// Pongo en uno RS
	LCD_RW_SetLow();			// Pongo en cero RW
	while (*s)
        lcd_write(*s++);
}
/*--------------------------------------------------------------------------*/
/*	Inicializar Modulo LCD para interfaz de 4 bits							*/
/*--------------------------------------------------------------------------*/
void lcd_init(void) {
    LCD_RW_SetLow();
	__delay_ms(16); // Must wait at least 15ms because power supply stabilization and other things.
    LCD_PORT = ((LCD_PORT & 0xF0) | (0x03)); // Le escribo el valor 0011 --> Datos primer envio
	lcd_strobe(); // Do strobe with "E" signal
	__delay_ms(5); // Debo esperar un tiempo superior a 4.1 ms
	lcd_strobe(); // Do strobe with "E" signal
	__delay_us(200); // Debo esperar un tiempo superior a 100 us
	lcd_strobe(); // Do strobe with "E" signal
    LCD_PORT = ((LCD_PORT & 0xF0) | (0x02)); // Le escribo el valor 0010
	lcd_strobe(); // Do strobe with "E" signal
	lcd_write(LCD_INTERFACE_4|LCD_2_LINE|LCD_5x8); // Function set: le escribo el valor 0010 1000 (4-bits, 2 lineas, 5x8) --> 0x28
	lcd_write(LCD_DISPLAY_ON); // Display on/off: le escribo el valor 0000 1000 (display on, cursor y blink off) --> 0x0C
	lcd_write(LCD_CLEAR_DISPLAY); // Le escribo el valor 0000 0001 (Display clear) --> 0x01
	__delay_us(LCD_ETIME_1); // Espero un tiempo de 1500 us que es lo que demora un clear display
	lcd_write(LCD_CURSOR_RIGHT); // Muevo una posicion a la derecha el cursor 0000 0110 --> 0x06
}

/*--------------------------------------------------------------------------*/
/*	Escribes las dos lineas en una sola llamada                             */
/*--------------------------------------------------------------------------*/
void lcd_write2lines(const char * l1, const char * l2){
    lcd_command_8bit(LCD_CLEAR_DISPLAY);
    lcd_command_8bit(LCD_RETURN_HOME);
    lcd_puts(l1);
    lcd_command_8bit(LCD_SEGUNDA_LINEA);
    lcd_puts(l2);   
}