/*
 * ADC_interface.h
 *
 * Created: 10/19/2023 12:56:57 PM
 *  Author: George
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "ADC_private.h"

// NonMaping macros for the ADC's channels
#define ADC_CHANNEL0   0
#define ADC_CHANNEL1   1
#define ADC_CHANNEL2   2
#define ADC_CHANNEL3   3
#define ADC_CHANNEL4   4
#define ADC_CHANNEL5   5
#define ADC_CHANNEL6   6
#define ADC_CHANNEL7   7


// Maping macros for the reference voltage
#define ADC_AVCC      1
#define ADC_AREF      2
#define ADC_INTERNAL  3

void ADC_init(u8 referenceVoltage);
void ADC_analogReadVoid(u8 channelNum, u16* readedVal);
u16 ADC_analogRead(u8 channelNum);

#endif /* ADC_INTERFACE_H_ */