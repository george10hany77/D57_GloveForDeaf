/*
 * DIO_program.c
 *
 * Created: 9/22/2023 8:07:49 PM
 *  Author: George
 */ 

#include "DIO_interface.h"

void pinModeDIO(u8* DDRX, u8 pinNum, u8 mode){
	if (mode == 1) // OUTPUT
	{
		SET_BIT(*DDRX, pinNum);
	}
	else if (mode == 0) // INPUT
	{
		CLEAR_BIT(*DDRX, pinNum);
	}
	else if (mode == 2) // INPUT_PULLUP
	{
		CLEAR_BIT(*DDRX, pinNum);
		SET_BIT(*(DDRX+1), pinNum);	// to access the PORTX address and output high to make the pull-up setting.
	}
}

void DIO_setPinMode(u8 regId, u8 pinId, u8 pinDir){
	switch (regId){
		case DIO_REGA_ID:
		switch (pinDir){
			case INPUT:
			CLEAR_BIT(DDRA, pinId);
			break;
			
			case OUTPUT:
			SET_BIT(DDRA, pinId);
			break;
			
			case INPUT_PULLUP:
			CLEAR_BIT(DDRA, pinId);
			SET_BIT(PORTA, pinId);
			break;
		}
		break;
		
		case DIO_REGB_ID:
		switch (pinDir){
			case INPUT:
			CLEAR_BIT(DDRB, pinId);
			break;
			
			case OUTPUT:
			SET_BIT(DDRB, pinId);
			break;
			
			case INPUT_PULLUP:
			CLEAR_BIT(DDRB, pinId);
			SET_BIT(PORTB, pinId);
			break;
		}
		break;
		
		case DIO_REGC_ID:
		switch (pinDir){
			case INPUT:
			CLEAR_BIT(DDRC, pinId);
			break;
			case OUTPUT:
			SET_BIT(DDRC, pinId);
			break;
			case INPUT_PULLUP:
			CLEAR_BIT(DDRC, pinId);
			SET_BIT(PORTC, pinId);
			break;
		}
		break;
		
		case DIO_REGD_ID:
		switch (pinDir){
			case INPUT:
			CLEAR_BIT(DDRD, pinId);
			break;
			case OUTPUT:
			SET_BIT(DDRD, pinId);
			break;
			case INPUT_PULLUP:
			CLEAR_BIT(DDRD, pinId);
			SET_BIT(PORTD, pinId);
			break;
		}
		break;
	}
}

void DIO_digitalWrite(u8 regId, u8 pinId, u8 pinValue){
	switch(regId){
		case DIO_REGA_ID:
		switch(pinValue){
			case LOW:
			CLEAR_BIT(PORTA, pinId);
			break;
			case HIGH:
			SET_BIT(PORTA, pinId);
			break;
		}
		break;
		
		case DIO_REGB_ID:
		switch(pinValue){
			case LOW:
			CLEAR_BIT(PORTB, pinId);
			break;
			case HIGH:
			SET_BIT(PORTB, pinId);
			break;
		}
		break;
		
		case DIO_REGC_ID:
		switch(pinValue){
			case LOW:
			CLEAR_BIT(PORTC, pinId);
			break;
			case HIGH:
			SET_BIT(PORTC, pinId);
			break;
		}
		break;
		
		case DIO_REGD_ID:
		switch(pinValue){
			case LOW:
			CLEAR_BIT(PORTD, pinId);
			break;
			case HIGH:
			SET_BIT(PORTD, pinId);
			break;
		}
		break;
	}
}

void DIO_voidDigitalRead(u8 regId, u8 pinId, u8* pinValue){
	switch (regId){
		case DIO_REGA_ID:
		*pinValue = (READ_BIT(PINA, pinId) > 0);
		break;
		
		case DIO_REGB_ID:
		*pinValue = (READ_BIT(PINB, pinId) > 0);
		break;		
		
		case DIO_REGC_ID:
		*pinValue = (READ_BIT(PINC, pinId) > 0);
		break;
		
		case DIO_REGD_ID:
		*pinValue = (READ_BIT(PIND, pinId) > 0);
		break;
	}
}

u8 DIO_digitalRead(u8 regId, u8 pinId){
	switch (regId){
		case DIO_REGA_ID:
		return (READ_BIT(PINA, pinId) > 0);
		
		case DIO_REGB_ID:
		return (READ_BIT(PINB, pinId) > 0);
		
		case DIO_REGC_ID:
		return (READ_BIT(PINC, pinId) > 0);
		
		case DIO_REGD_ID:
		return (READ_BIT(PIND, pinId) > 0);
	}
	return 0;//final unreachable statement
}

void DIO_togglePin(u8 regId, u8 pinId){
	switch(regId){
		case DIO_REGA_ID:
		TOGGLE_BIT(PORTA, pinId);
		break;	
		
		case DIO_REGB_ID:
		TOGGLE_BIT(PORTB, pinId);
		break;
		
		case DIO_REGC_ID:
		TOGGLE_BIT(PORTC, pinId);
		break;
				
		case DIO_REGD_ID:
		TOGGLE_BIT(PORTD, pinId);
		break;
	}
}

void DIO_setRegisterMode(u8 PortId, u8 PortDirection){
		if((PortId<=3) && ((PortDirection == OUTPUT) || (PortDirection == INPUT) || (PortDirection == INPUT_PULLUP)))
		{
			switch(PortId)
			{
				case DIO_REGA_ID:
				switch(PortDirection)
				{
					case OUTPUT:
					DDRA = 0xff; //0b11111111
					break;
					
					case INPUT:
					DDRA = 0x00;
					break;
					
					case INPUT_PULLUP:
					DDRA = 0x00;
					PORTA = 0xff; //0b11111111
					break;
				}
				break;
				
				case DIO_REGB_ID:
				switch(PortDirection)
				{
					case OUTPUT:
					DDRB = 0xff; //0b11111111
					break;
					
					case INPUT:
					DDRB = 0x00;
					break;
					
					case INPUT_PULLUP:
					DDRB = 0x00;
					PORTB = 0xff; //0b11111111
					break;
				}
				break;
				
				case DIO_REGC_ID:
				switch(PortDirection)
				{
					case OUTPUT:
					DDRC = 0xff; //0b11111111
					break;
					
					case INPUT:
					DDRC = 0x00;
					break;
					
					case INPUT_PULLUP:
					DDRC = 0x00;
					PORTC = 0xff; //0b11111111
					break;
				}
				break;
				
				case DIO_REGD_ID:
				switch(PortDirection)
				{
					case OUTPUT:
					DDRD = 0xff; //0b11111111
					break;
					
					case INPUT:
					DDRD = 0x00;
					break;
					
					case INPUT_PULLUP:
					DDRD = 0x00;
					PORTD = 0xff; //0b11111111
					break;					
				}
				break;
			}
		}
		else
		{
			// Do Nothing
		}
}

void DIO_setPortValue (u8 PortId, u8 PortValue){
	switch(PortId)
	{
		case DIO_REGA_ID:
		switch(PortValue)
		{
			case HIGH:
			PORTA = 0xff; //0b11111111
			break;
			
			case LOW:
			PORTA = 0x00;
			break;
		}
		break;
		
		case DIO_REGB_ID:
		switch(PortValue)
		{
			case HIGH:
			PORTB = 0xff; //0b11111111
			break;
			
			case LOW:
			PORTB = 0x00;
			break;
		}
		break;
		
		case DIO_REGC_ID:
		switch(PortValue)
		{
			case HIGH:
			PORTC = 0xff; //0b11111111
			break;
			
			case LOW:
			PORTC = 0x00;
			break;
		}
		break;
		
		case DIO_REGD_ID:
		switch(PortValue)
		{
			case HIGH:
			PORTD = 0xff; //0b11111111
			break;
			
			case LOW:
			PORTD = 0x00;
			break;
		}
		break;
	}
}

void DIO_togglePortValue(u8 PortId){
	switch(PortId){
		case DIO_REGA_ID:
		PORTA = (PORTA == 0x00) ? 0xff : 0x00;
		break;
		
		case DIO_REGB_ID:
		PORTB = (PORTB == 0x00) ? 0xff : 0x00;
		break;
		
		case DIO_REGC_ID:
		PORTC = (PORTC == 0x00) ? 0xff : 0x00;
		break;
		
		case DIO_REGD_ID:
		PORTD = (PORTD == 0x00) ? 0xff : 0x00;
		break;
	}
}

void DIO_readRegisterValueVoid(u8 regId, u8* regValue){
	switch(regId){
		case DIO_REGA_ID:
		*regValue = (PORTA == 0x00) ? 0 : 1;
		break;
		
		case DIO_REGB_ID:
		*regValue = (PORTB == 0x00) ? 0 : 1;
		break;
		
		case DIO_REGC_ID:
		*regValue = (PORTC == 0x00) ? 0 : 1;
		break;
		
		case DIO_REGD_ID:
		*regValue = (PORTD == 0x00) ? 0 : 1;
		break;
	}
}

u8 DIO_readRegisterValue(u8 regId){
	switch(regId){
		case DIO_REGA_ID:
		return (PORTA == 0x00) ? 0 : 1;
		
		case DIO_REGB_ID:
		return (PORTB == 0x00) ? 0 : 1;
		
		case DIO_REGC_ID:
		return (PORTC == 0x00) ? 0 : 1;
		
		case DIO_REGD_ID:
		return (PORTD == 0x00) ? 0 : 1;
	}
	return 0;// non reachable statement.
}