/*
 * LCD_config.h
 *
 * Created: 9/29/2023 6:27:45 PM
 *  Author: George
 */ 

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "DIO_interface.h"

// Control Registers and Pins.
#define LCD_RW_REG	 DIO_REGB_ID
#define LCD_RW_PIN	 DIO_PIN1

#define LCD_RS_REG	 DIO_REGB_ID
#define LCD_RS_PIN	 DIO_PIN0

#define LCD_EN_REG	 DIO_REGB_ID
#define LCD_EN_PIN	 DIO_PIN2

// Data Pins
#define LCD_D4_REG	 DIO_REGB_ID
#define LCD_D4_PIN	 DIO_PIN3

#define LCD_D5_REG	 DIO_REGB_ID
#define LCD_D5_PIN	 DIO_PIN4

#define LCD_D6_REG	 DIO_REGB_ID
#define LCD_D6_PIN	 DIO_PIN5

#define LCD_D7_REG	 DIO_REGB_ID
#define LCD_D7_PIN	 DIO_PIN6

#endif /* LCD_CONFIG_H_ */