/**
  EUSART Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.h

  @Summary
    This is the generated header file for the EUSART driver using MPLAB� Code Configurator

  @Description
    This header file provides APIs for driver for EUSART.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
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

#ifndef _EUSART_H
#define _EUSART_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif


    /**
      Section: Macro Declarations
     */

#define EUSART_DataReady  (EUSART_is_rx_ready())

    /**
      Section: EUSART APIs
     */

    /**
      @Summary
        Initialization routine that takes inputs from the EUSART GUI.

      @Description
        This routine initializes the EUSART driver.
        This routine must be called before any other EUSART routine is called.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment
    
     */
    void EUSART_Initialize(void);

/**
  @Summary
    Checks if the EUSART transmitter is ready to transmit data

  @Description
    This routine checks if EUSART transmitter is ready 
    to accept and transmit data byte

  @Preconditions
    EUSART_Initialize() function should have been called
    before calling this function.
    EUSART transmitter should be enabled before calling 
    this function

  @Param
    None

  @Returns
    Status of EUSART transmitter
    TRUE: EUSART transmitter is ready
    FALSE: EUSART transmitter is not ready
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART_is_rx_ready())
            {
                rxData = UART1_Read();
                if(EUSART_is_tx_ready())
                {
                    EUSARTWrite(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART_is_tx_ready(void);    
  
/**
  @Summary
    Checks if the EUSART receiver ready for reading

  @Description
    This routine checks if EUSART receiver has received data 
    and ready to be read

  @Preconditions
    EUSART_Initialize() function should be called
    before calling this function
    EUSART receiver should be enabled before calling this 
    function

  @Param
    None

  @Returns
    Status of EUSART receiver
    TRUE: EUSART receiver is ready for reading
    FALSE: EUSART receiver is not ready for reading
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART_is_rx_ready())
            {
                rxData = UART1_Read();
                if(EUSART_is_tx_ready())
                {
                    EUSART_Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART_is_rx_ready(void);

/**
  @Summary
    Checks if EUSART data is transmitted

  @Description
    This function return the status of transmit shift register

  @Preconditions
    EUSART_Initialize() function should be called
    before calling this function
    EUSART transmitter should be enabled and EUSART_Write
    should be called before calling this function

  @Param
    None

  @Returns
    Status of EUSART receiver
    TRUE: Data completely shifted out if the USART shift register
    FALSE: Data is not completely shifted out of the shift register
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            if(EUSART_is_tx_ready())
            {
				LED_0_SetHigh();
                EUSARTWrite(rxData);
            }
			if(EUSART_is_tx_done()
            {
                LED_0_SetLow();
            }
        }
    }
    </code>
*/
bool EUSART_is_tx_done(void);
  
    /**
      @Summary
        Read a byte of data from the EUSART.

      @Description
        This routine reads a byte of data from the EUSART.

      @Preconditions
        EUSART_Initialize() function should have been called
        before calling this function. The transfer status should be checked to see
        if the receiver is not empty before calling this function.

      @Param
        None

      @Returns
        A data byte received by the driver.
     */

    uint8_t EUSART_Read(void);

    /**
     @Summary
       Writes a byte of data to the EUSART.

     @Description
       This routine writes a byte of data to the EUSART.

     @Preconditions
       EUSART_Initialize() function should have been called
       before calling this function. The transfer status should be checked to see
       if transmitter is not busy before calling this function.

     @Param
       txData  - Data byte to write to the EUSART

     @Returns
       None
     */
    void EUSART_Write(uint8_t txData);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // _EUSART_H
/**
 End of File
 */