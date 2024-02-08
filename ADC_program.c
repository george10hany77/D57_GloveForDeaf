/*
 * ADC_program.c
 *
 * Created: 10/19/2023 12:57:13 PM
 *  Author: George
 */ 

#include "ADC_interface.h"

void ADC_init(u8 referenceVoltage){
	switch(referenceVoltage){
		// select vRef = AVCC
		case ADC_AVCC:
		SET_BIT(ADMUX, REFS0);
		CLEAR_BIT(ADMUX, REFS1);
		break;
		
		// select vRef = AREF
		case ADC_AREF:
		CLEAR_BIT(ADMUX, REFS0);
		CLEAR_BIT(ADMUX, REFS1);
		break;
		
		// select vRef = 2.56v
		default:
		case ADC_INTERNAL:
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
		break;
	}	
	// Right adjustment, to make if left you set this bit to high
	CLEAR_BIT(ADMUX, ADLAR);
	
	// Single conversion mode "turning of AUTO trigger"
	CLEAR_BIT(ADCSRA, ADATE);
	
	// Prescaler Frequency "From 16 MHZ to 125 KHZ"
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	
	// We will not use Interrupt
	CLEAR_BIT(ADCSRA, ADIE);
	
	// To Enable the ACD
	SET_BIT(ADCSRA, ADEN);
}

void ADC_analogReadVoid(u8 channelNum, u16* readedVal){
	if (channelNum < 32 && readedVal != NULL)
	{
		// ADC select channel
		// This process is not generic but it will work as for each ADC id we should set "number of bits" the same with as id number 
		// we start with 111 to not to interact with the first three bits, because they are used in other situiations
		ADMUX &= 0b11100000;
		ADMUX = ADMUX | channelNum;
		
		// Start Conversion
		SET_BIT(ADCSRA, ADSC);
		
		//Blocking
		while(READ_BIT(ADCSRA, ADIF) == 0);
		
		// Because we are not using interrupts we need to manually turn of the flag "Any flag: Write 1 to clear"
		SET_BIT(ADCSRA, ADIF);
		
		// Return readed value from ADC data register
		*readedVal = ADC_U16;
		
	}else{}
	
}

u16 ADC_analogRead(u8 channelNum){
	if (channelNum < 32)
	{
		// ADC select channel
		// This process is not generic but it will work as for each ADC id we should set "number of bits" the same with as id number
		// we start with 111 to not to interact with the first three bits, because they are used in other situiations
		ADMUX &= 0b11100000;
		ADMUX = ADMUX | channelNum;
		
		// Start Conversion
		SET_BIT(ADCSRA, ADSC);
		
		//Blocking
		while(READ_BIT(ADCSRA, ADIF) == 0);
		
		// Because we are not using interrupts we need to manually turn of the flag "Any flag: Write 1 to clear"
		SET_BIT(ADCSRA, ADIF);
		
		// Return readed value from ADC data register
		return ADC_U16;
		
	}else{}
		
}