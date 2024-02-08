/*
 * config.c
 *
 * Created: 9/29/2023 6:26:08 PM
 *  Author: George
 */ 

#include "LCD_interface.h"

void LCD_sendCommand(u8 command){
	
	// RS -> 0 to write command
	DIO_digitalWrite(LCD_RS_REG, LCD_RS_PIN, LOW);

	// R/W -> 0 to write data
	DIO_digitalWrite(LCD_RW_REG, LCD_RW_PIN, LOW);
	
	// Send the high 4 bits
	//PORTA = (PORTA & 0x0F) | (command & 0xF0);
	private_WriteHalfREG(command >> 4);
	
	// enable
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, HIGH);
	_delay_ms(1);
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, LOW);
	
	// Send the low 4 bits
	//PORTA = (PORTA & 0x0F) | ((command << 4) & 0xF0);
	private_WriteHalfREG(command);
	
	// enable
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, HIGH);
	_delay_ms(1);
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, LOW);
	
	_delay_ms(2);
}

static void private_WriteHalfREG(u8 value){
	DIO_digitalWrite(LCD_D4_REG, LCD_D4_PIN, READ_BIT(value, 0));
	DIO_digitalWrite(LCD_D5_REG, LCD_D5_PIN, READ_BIT(value, 1));
	DIO_digitalWrite(LCD_D6_REG, LCD_D6_PIN, READ_BIT(value, 2));
	DIO_digitalWrite(LCD_D7_REG, LCD_D7_PIN, READ_BIT(value, 3));		
}

void LCD_init(){
	// Configure LCD control pins and data pins as outputs
	DIO_setPinMode(LCD_RS_REG, LCD_RS_PIN, OUTPUT);
	DIO_setPinMode(LCD_RW_REG, LCD_RW_PIN, OUTPUT);
	DIO_setPinMode(LCD_EN_REG, LCD_EN_PIN, OUTPUT);
		
	DIO_setPinMode(LCD_D4_REG, LCD_D4_PIN, OUTPUT);
	DIO_setPinMode(LCD_D5_REG, LCD_D5_PIN, OUTPUT);
	DIO_setPinMode(LCD_D6_REG, LCD_D6_PIN, OUTPUT);
	DIO_setPinMode(LCD_D7_REG, LCD_D7_PIN, OUTPUT);
		
	_delay_ms(50);// Wait for the LCD to power up
	
	// to set 2*16 4-bit mode
	// RS -> 0 to write command
	DIO_digitalWrite(LCD_RS_REG, LCD_RS_PIN, LOW);
	// R/W -> 0 to write data
	DIO_digitalWrite(LCD_RW_REG, LCD_RW_PIN, LOW);
	private_WriteHalfREG(0b0010);
	// enable
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, HIGH);
	_delay_ms(1);
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, LOW);
	LCD_sendCommand(0b00101000);
	
	//Display-Cursor-Blink DCB
	_delay_us(40);
	LCD_sendCommand(0b00001111);
	
	_delay_us(40);
	LCD_sendCommand(0b00000001); // clear
	
	_delay_us(2);
	LCD_sendCommand(0b00000110); // Increment mode

}

void LCD_clear(){
	LCD_sendCommand(0x01);
	_delay_ms(2);
}

void LCD_sendChar(u8 data){
	// RS -> 1 to be on "write 'data' mode"
	DIO_digitalWrite(LCD_RS_REG, LCD_RS_PIN, HIGH);
	
	// R/W -> 0 to write data
	DIO_digitalWrite(LCD_RW_REG, LCD_RW_PIN, LOW);
	
	// Send the high 4 bits
	//PORTA = (PORTA & 0x0F) | (data & 0xF0);
	private_WriteHalfREG(data >> 4);	
	
	// enable
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, HIGH);
	_delay_ms(1);
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, LOW);
	
	// Send the low 4 bits
	//PORTA = (PORTA & 0x0F) | ((data << 4) & 0xF0);
	private_WriteHalfREG(data);
	
	// enable
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, HIGH);
	_delay_ms(1);
	DIO_digitalWrite(LCD_EN_REG, LCD_EN_PIN, LOW);
		
	
	_delay_ms(50); // this delay controls the time of which the next char will be printed in.
}

void LCD_sendString(const u8* ptr){
	while(*ptr != '\0'){
		LCD_sendChar(*ptr);
		ptr++;
	}
}

void LCD_setCursor(u8 line, u8 position){
		// Calculate the DDRAM address based on line and position
	u8 address;
	if (line == 0) {
		// Line 0 addresses: 0x00 to 0x27 || 0 -> 39
		address = position % 0x28; // Ensure position wraps around within the line
		
		} else if (line == 1) {
		// Line 1 addresses: 0x40 to 0x67 || 64 -> 103
		address = 0x40 + (position % 0x28); // Ensure position wraps around within the line
		} else {
		// Invalid line, default to line 0, position 0
		address = 0;
	}

	// Set the cursor address command
	LCD_sendCommand(0x80 | address);
}

void LCD_shift(u8 shiftDir){
	if (shiftDir == 0) {
	    // Shift left
	    LCD_sendCommand(0x10);
	    } else {
	    // Shift right
	    LCD_sendCommand(0x14);
	}
}

void LCD_shiftBy(u8 shiftDir, u8 steps){	
	while (steps > 0)
	{
		LCD_shift(shiftDir);
		steps--;
	}
}

static u8 u8Size(u8 num){
	if(num == 0)
	return 1;
	u8 counter = 0;
	while(num > 0){
		num /= 10;
		counter++;
	}
	return counter;
}

void LCD_sendNumber(u32 num){//convert int to string
	u8 string[12];
	u8 numSize = u8Size(num);
	for (u8 i = numSize-1; i != 255; --i) //255 because we are storing i in u8. If it was 0 and --i it will be 255 as u8 is unsigned char.
	{
		string[i] = '0' + (num % 10); // to convert the number into a character
		num /= 10;
	}
	string[numSize] = '\0';
	LCD_sendString(string);
}

// Function to print a number on the LCD
void lcd_print_number(u16 num) {
	char buffer[6]; // Assuming max 5 digits for the number

	// Convert the number to a string
	itoa(num, buffer, 10);

	// Print the string on the LCD
	LCD_sendString(buffer);
}