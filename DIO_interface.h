/*
 * DIO_interface.h
 *
 * Created: 9/22/2023 8:08:25 PM
 *  Author: George
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "DIO_ATMEGA32.h"
#include "BIT_MATH.h"

#define DIO_REGA_ID 0
#define DIO_REGB_ID 1
#define DIO_REGC_ID 2
#define DIO_REGD_ID 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define INPUT         0
#define OUTPUT        1
#define INPUT_PULLUP  2

#define LOW  0
#define HIGH 1
							/************************* APIS PROTO TYPES *************************/

// My Standard functions for "Pins"
void pinModeDIO(u8* DDRX, u8 pinNum, u8 mode);
u8 DIO_digitalRead(u8 regId, u8 pinId);

// My Standard functions for "Registers"
u8 DIO_readRegisterValue(u8 regId);

// Standard functions for "Pins"
void DIO_setPinMode(u8 regId, u8 pinId, u8 pinDir);
void DIO_digitalWrite(u8 regId, u8 pinId, u8 pinValue);
void DIO_voidDigitalRead(u8 regId, u8 pinId, u8* pinValue);
void DIO_togglePin(u8 regId, u8 pinId);

// Standard functions for "Registers"
void DIO_setRegisterMode(u8 PortId, u8 PortDirection);
void DIO_setPortValue(u8 PortId, u8 PortValue);
void DIO_readRegisterValueVoid(u8 regId, u8* regValue);
void DIO_togglePortValue(u8 PortId);

#endif /* DIO_INTERFACE_H_ */