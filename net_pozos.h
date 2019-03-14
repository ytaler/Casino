/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <ctype.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  @Summary
    Verifica si hay mas de un boton pulsado anulando esa opcion, sino devuelve
    el valor del boton pulsado
 
  @Description
    Esta funcion....... TODO

  @Preconditions
    None

  @Param
    Valor de los botones leidos desde el shiftregister

  @Returns
    Valor del boton normalizado, evitando multiples pulsaciones

  @Comment
    
	
  @Example
    <code>
 *  TODO
    </code>
*/
uint8_t verificarBotonesPlayer(uint8_t);
uint8_t verificarSeleccionPlayer(uint8_t *);
uint8_t verificarPagoDealer(uint8_t *);
uint8_t verificarPagoPlayer(uint8_t *);
uint8_t chequeo8Bits(uint8_t *, uint8_t);
uint8_t verificarTecladoNumerico(uint8_t datos1, uint8_t *datos2);

#define PREMIO_MAX UINT32_MAX/10

const char tablaApuestaPlayer[][5] = {{'_','D','D','P','P'},{'_','+','-','+','-'}}; // compensa diferencia de indices con un guion bajo

const char premios[][16] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'E','s','c','a','l','e','r','a',' ','R','e','a','l'},
    {'E','s','c','a','l','e','r','a',' ','C','o','l','o','r'},
    {'P','o','k','e','r'},
    {'F','u','l','l'},
    {'C','o','l','o','r'},
    {'L','u','c','k','y',' ','P','l','a','y','e','r'},
    {'M','a','g','i','c',' ','C','a','r','d'},
};

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

