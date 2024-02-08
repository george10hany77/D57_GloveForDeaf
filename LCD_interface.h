/*
 * LCD_interface.h
 *
 * Created: 9/29/2023 6:28:07 PM
 *  Author: George
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "DIO_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Macros
#define LCD_SHIFT_LEFT  0
#define LCD_SHIFT_RIGHT 1

// my functions
void LCD_clear();
void LCD_sendString(const u8* ptr);
void LCD_shiftBy(u8 shiftDir, u8 steps);
void LCD_setCursor(u8 line, u8 position);
void LCD_shift(u8 shiftDir);
void LCD_sendNumber(u32 num);
void lcd_print_number(u16 num);

void LCD_init();
void LCD_sendCommand(u8 command);
void LCD_sendChar(u8 data);



#endif /* LCD_INTERFACE_H_ */