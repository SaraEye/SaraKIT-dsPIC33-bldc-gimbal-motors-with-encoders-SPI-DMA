/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma.c

  @Summary
    This is the generated driver implementation file for the DMA driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for DMA.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK32MP503
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
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
  Section: Included Files
*/

#include "dma.h"
#include "delay.h"

//uint16_t __attribute__((coherent)) DMA_TxBuffer[32];
//uint16_t __attribute__((coherent)) DMA_RxBuffer[32];
volatile uint16_t DMA_TxBuffer[16];
volatile uint16_t DMA_RxBuffer[16];


/**
  Prototype:        void DMA_Initialize(void)
  Input:            none
  Output:           none
  Description:      DMA_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            DMA_Initialize();
 */
void DMA_Initialize(void) 
{ 
    for (int i=0; i<16; i++) {
        DMA_TxBuffer[i]=0; 
        DMA_RxBuffer[i]=0;
    }

    // DMAEN enabled; PRSSEL Fixed priority; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later
    // LADDR 4096; 
    DMAL= 0x1000;
    // HADDR 20479; 
    DMAH= 0x47FF;

    // CHEN enabled; DAMODE Incremented; TRMODE Repeated One-Shot; CHREQ disabled; RELOAD enabled; SIZE 16 bit; NULLW disabled; SAMODE Peripheral indirect addressing; 
    DMACH0 = 0x2D5 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF enabled; LOWIF disabled; HALFEN disabled; DONEIF enabled; OVRUNIF disabled; CHSEL SPI1 RX; HIGHIF disabled; 
    DMAINT0= 0x230;
    // SADDR 0; 
    DMASRC0= 0x00;
    // DADDR 0; 
    DMADST0= 0x00;
    // CNT 8; 
    DMACNT0= 0x08;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = false;
    // Enabling Channel 0 Interrupt
    IEC0bits.DMA0IE = true;

    // CHEN enabled; SAMODE Incremented; SIZE 16 bit; DAMODE Peripheral indirect addressing; CHREQ disabled; RELOAD enabled; TRMODE Repeated One-Shot; NULLW disabled; 
    DMACH1 = 0x275 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL SPI1 RX; 
    DMAINT1= 0x200;
    //DMAINT1= 0x5000; odpala DMA1?
    // SADDR 0; 
    DMASRC1= 0x00;
    // DADDR 0; 
    DMADST1= 0x00;
    // CNT 8; 
    DMACNT1= 0x08;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = false;
    // Enabling Channel 1 Interrupt
    IEC0bits.DMA1IE = true;

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; CHREQ disabled; RELOAD disabled; NULLW disabled; TRMODE One-Shot; 
    DMACH2 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL INT0; 
    DMAINT2= 0x00;
    // SADDR 0; 
    DMASRC2= 0x00;
    // DADDR 0; 
    DMADST2= 0x00;
    // CNT 0; 
    DMACNT2= 0x00;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = false;

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; TRMODE One-Shot; NULLW disabled; CHREQ disabled; RELOAD enabled; 
    DMACH3 = 0x200 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL INT0; HIGHIF disabled; 
    DMAINT3= 0x00;
    // SADDR 0; 
    DMASRC3= 0x00;
    // DADDR 0; 
    DMADST3= 0x00;
    // CNT 0; 
    DMACNT3= 0x00;
    // Clearing Channel 3 Interrupt Flag;
    IFS1bits.DMA3IF = false;
    
    //Enable DMA
    DMACONbits.DMAEN = 1; 
    
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) &DMA_RxBuffer[0]);
    DMA_SourceAddressSet(DMA_CHANNEL_0,(uint16_t) &SPI1BUFL);
    DMA_DestinationAddressSet(DMA_CHANNEL_1,(uint16_t) &SPI1BUFL);
    DMA_SourceAddressSet(DMA_CHANNEL_1, (uint16_t) &DMA_TxBuffer[0]);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    DMA_ChannelEnable(DMA_CHANNEL_1); 
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA0Interrupt( void )
{
	// DMA Channel0 callback function 
	DMA_Channel0_CallBack(); 
    IFS0bits.DMA0IF = 0;
}

void __attribute__ ((weak)) DMA_Channel1_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA1Interrupt( void )
{
	// DMA Channel1 callback function 
    DMA_SourceAddressSet(DMA_CHANNEL_1, (uint16_t) &DMA_TxBuffer[0]);
	DMA_Channel1_CallBack();
    IFS0bits.DMA1IF = 0;
    for (int i=0; i<16; i++) {
        DMA_TxBuffer[i]=0; 
    }    
}
void __attribute__ ((weak)) DMA_Channel2_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel2_Tasks( void )
{
	if(IFS1bits.DMA2IF)
	{
		// DMA Channel2 callback function 
		DMA_Channel2_CallBack();
		
		IFS1bits.DMA2IF = 0;
	}
}
void __attribute__ ((weak)) DMA_Channel3_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel3_Tasks( void )
{
	if(IFS1bits.DMA3IF)
	{
		// DMA Channel3 callback function 
		DMA_Channel3_CallBack();
		
		IFS1bits.DMA3IF = 0;
	}
}

void DMA_ChannelEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_1:
                DMACH1bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_2:
                DMACH2bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_3:
                DMACH3bits.CHEN = 1;
                break; 
        default: break;
    }
}
void DMA_ChannelDisable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_1:
                DMACH1bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_2:
                DMACH2bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_3:
                DMACH3bits.CHEN = 0;
                break;    
        default: break;
    }
}
void DMA_TransferCountSet(DMA_CHANNEL channel, uint16_t transferCount)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACNT0 = transferCount;
                break;
        case DMA_CHANNEL_1:
                DMACNT1 = transferCount;
                break;
        case DMA_CHANNEL_2:
                DMACNT2 = transferCount;
                break;
        case DMA_CHANNEL_3:
                DMACNT3 = transferCount;
                break;
        default: break;
    }
}
uint16_t DMA_TransferCountGet(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return (DMACNT0);
        case DMA_CHANNEL_1:
                return (DMACNT1);
        case DMA_CHANNEL_2:
                return (DMACNT2);
        case DMA_CHANNEL_3:
                return (DMACNT3);
        default: return 0;
    }
}
void DMA_SoftwareTriggerEnable(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_1:
                DMACH1bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_2:
                DMACH2bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_3:
                DMACH3bits.CHREQ = 1;
                break;
        default: break;
    }
}

void DMA_SourceAddressSet(DMA_CHANNEL  channel, uint16_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                DMASRC0 = address;
                break;
        case DMA_CHANNEL_1:
                DMASRC1 = address;
                break;
        case DMA_CHANNEL_2:
                DMASRC2 = address;
                break;
        case DMA_CHANNEL_3:
                DMASRC3 = address;
                break;
        default: break;
    }    
}

void DMA_DestinationAddressSet(DMA_CHANNEL  channel, uint16_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                DMADST0 = address;
                break;
        case DMA_CHANNEL_1:
                DMADST1 = address;
                break;
        case DMA_CHANNEL_2:
                DMADST2 = address;
                break;
        case DMA_CHANNEL_3:
                DMADST3 = address;
                break;
        default: break;
    }    
}

bool DMA_IsSoftwareRequestPending(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMACH0bits.CHREQ);
        case DMA_CHANNEL_1:
                return(DMACH1bits.CHREQ);
        case DMA_CHANNEL_2:
                return(DMACH2bits.CHREQ);
        case DMA_CHANNEL_3:
                return(DMACH3bits.CHREQ);
        default: return 0;
    }
}

bool DMA_IsBufferedWriteComplete(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.DBUFWF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.DBUFWF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.DBUFWF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.DBUFWF);
        default: return 0;
    }
}

bool DMA_IsHighAddressLimitFlagSet(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.HIGHIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.HIGHIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.HIGHIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.HIGHIF);
        default: return 0;
    }
}

bool DMA_IsLowAddressLimitFlagSet(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.LOWIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.LOWIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.LOWIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.LOWIF);
        default: return 0;
    }
}

bool DMA_IsOperationDone(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.DONEIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.DONEIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.DONEIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.DONEIF);
        default: return 0;
    }
}

bool DMA_IsOverrunFlagSet(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.OVRUNIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.OVRUNIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.OVRUNIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.OVRUNIF);
        default: return 0;
    }
}

bool DMA_IsOperationHalfComplete(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.HALFIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.HALFIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.HALFIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.HALFIF);
        default: return 0;
    }
}
