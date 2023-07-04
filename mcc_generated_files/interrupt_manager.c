/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
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

/**
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    CCPI: CCP2 Capture/Compare Event
    //    Priority: 4
        IPC5bits.CCP2IP = 4;
    //    CCTI: CCP2 Timer Event
    //    Priority: 4
        IPC6bits.CCT2IP = 4;
    //    CCPI: CCP3 Capture/Compare Event
    //    Priority: 4
        IPC8bits.CCP3IP = 4;
    //    CCTI: CCP3 Timer Event
    //    Priority: 4
        IPC9bits.CCT3IP = 4;
    //    ADCAN24: ADC AN24 Convert Done
    //    Priority: 1
        IPC48bits.ADCAN24IP = 1;
    //    ADCAN25: ADC AN25 Convert Done
    //    Priority: 1
        IPC48bits.ADCAN25IP = 1;
    //    MICI: I2C1 Master Event
    //    Priority: 3
        IPC4bits.MI2C1IP = 3;
    //    SICI: I2C1 Slave Event
    //    Priority: 3
        IPC4bits.SI2C1IP = 3;
    //    DMA1I: DMA Channel 1
    //    Priority: 2
        IPC2bits.DMA1IP = 2;
    //    DMA0I: DMA Channel 0
    //    Priority: 1
        IPC1bits.DMA0IP = 1;
}
