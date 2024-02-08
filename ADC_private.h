/*
 * ADC_private.h
 *
 * Created: 10/19/2023 12:57:55 PM
 *  Author: George
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define ADMUX (* (volatile u8 *) 0x27)
#define REFS1         7
#define REFS0         6
#define ADLAR         5
#define MUX4          4
#define MUX3          3
#define MUX2          2
#define MUX1          1
#define MUX0          0

#define ADCSRA (* (volatile u8 *) 0x26)
#define ADEN          7
#define ADSC          6
#define ADATE         5
#define ADIF          4
#define ADIE          3
#define ADPS2         2
#define ADPS1         1
#define ADPS0		  0

#define ADC_U16 (* (volatile u16 *) 0x24) // as the two registers consecutive in memory. If not, we will do this : u16 adc_u16 = (ADCH << 8)|ADCL; "generic solution"

#define SFIOR (* (volatile u8 *) 0x50)
#define ADTS2         7
#define ADTS1         6
#define ADTS0         5

#endif /* ADC_PRIVATE_H_ */