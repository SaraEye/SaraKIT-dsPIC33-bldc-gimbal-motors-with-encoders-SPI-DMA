/**
  SCCP2 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp2.h

  @Summary
    This is the generated header file for the SCCP2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP2. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK32MP503
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
*/
/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _SCCP2_CAPTURE_H
#define _SCCP2_CAPTURE_H

/**
  Section: Included Files
*/

#include <xc.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes MCCP/SCCP instance : 2

  @Description
    This routine initializes the MCCP/SCCP driver for instance : 2
    index, making it ready for clients to open and use it. It also initializes any
    internal data structures.

  @Param
    None.

  @Returns
    None.
  
  @Comment
   
*/
void SCCP2_CAPTURE_Initialize(void);

/**
  @Summary
    Starts the SCCP2

  @Description
    This routine starts the SCCP2

  @Param
    None.

  @Returns
    None
*/

void SCCP2_CAPTURE_Start( void );
/**
  @Summary
    Stops the SCCP2

  @Description
    This routine stops the SCCP2

  @Param
    None.

  @Returns
    None
*/

void SCCP2_CAPTURE_Stop( void );

/**
  @Summary
    Callback for SCCP2 CAPTURE.

  @Description
    This routine is callback for SCCP2 CAPTURE

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP2_Initialize(); for an example
*/
void SCCP2_CAPTURE_CallBack(void);

/**
*/


/**
  @Summary
    Callback for SCCP2 CAPTURE Timer.

  @Description
    This routine is callback for SCCP2 CAPTURE Timer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP2_Initialize(); for an example
*/
void SCCP2_CAPTURE_TimerCallBack(void);


/**
  @Summary
    Reads the 16 bit capture value. 

  @Description
    This routine reads the 16 bit capture value. 

  @Param
    None.

  @Returns
    Returns 16 bit captured value
*/

uint16_t SCCP2_CAPTURE_Data16Read( void );

/**
  @Summary
    Gets the buffer overflow status.

  @Description
    This routine gets the buffer overflow status.

  @Param
    None.

  @Returns
    Returns true if the input capture buffer has overflowed. 
    Returns false if the input capture buffer has not overflowed. 
*/

bool SCCP2_CAPTURE_HasBufferOverflowed( void );
/**
  @Summary
    Gets the buffer empty status.

  @Description
    This routine gets the buffer empty status.

  @Param
    None.

  @Returns
    Returns true if the input capture buffer is empty . 
    Returns false if the input capture buffer is not empty. 
*/

bool SCCP2_CAPTURE_IsBufferEmpty( void );
/**
  @Summary
    Resets the buffer overflow status flag.

  @Description
    This routine resets the buffer overflow status flag.

  @Param
    None.

  @Returns
    None. 
*/

void SCCP2_CAPTURE_OverflowFlagReset( void );
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_SCCP2_H
/**
 End of File
*/