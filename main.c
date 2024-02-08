/*
 * GloveForDeaf.c
 *
 * Created: 2/7/2024 1:42:44 PM
 * Author : George and Abdelrahman
 */ 

#include "ADC_interface.h"
#include "LCD_interface.h"

int main(void)
{
	LCD_init();
	ADC_init(ADC_AVCC);
	
	u16 values[5];
	u8 mask0 = 1, mask1 = 1, mask2 = 1, mask3 = 1, mask4 = 1, mask5 = 1, mask6 = 1, mask7 = 1;
    while (1) 
    {
		for (u8 i = 0; i < 5; i++)
		{
			values[i] = ADC_analogRead(i);
		}
		
		// for calibration
		/*LCD_clear();
		LCD_setCursor(0,0);
		lcd_print_number(values[0]);
		LCD_setCursor(0,5);
		lcd_print_number(values[1]);
		LCD_setCursor(0,10);
		lcd_print_number(values[2]);
		LCD_setCursor(1,0);
		lcd_print_number(values[3]);
		LCD_setCursor(1,5);
		lcd_print_number(values[4]);*/
		
		if(values[0] < 200 && values[1] < 200 && values[2] < 200 && values[3] > 800 && values[4] < 200 && mask0 == 1){
			LCD_clear();
			LCD_sendString("*** YOU ***");
			mask0 = 0;
			mask1 = 1;
			mask2 = 1;
			mask3 = 1;
			mask4 = 1;
			mask5 = 1;
			mask6 = 1;
			mask7 = 1;
		}
		if(values[0] < 200 && values[1] < 200 && values[2] > 800 && values[3] > 800 && values[4] < 200 && mask1 == 1){
			LCD_clear();
			LCD_sendString("I'm Watching You");
			mask0 =	1;
			mask1 = 0;
			mask2 = 1;
			mask3 = 1;
			mask4 = 1;
			mask5 = 1;
			mask6 = 1;
			mask7 = 1;	
		}		
		if(values[0] > 800 && values[1] < 200 && values[2] > 800 && values[3] > 800 && values[4] > 800 && mask2 == 1){
			LCD_clear();
			LCD_sendString("Really Love You");
			mask0 = 1;
			mask1 = 1;
			mask2 = 0;
			mask3 = 1;
			mask4 = 1;
			mask5 = 1;
			mask6 = 1;
			mask7 = 1;
		}		
		if(values[0] > 800 && values[1] < 200 && values[2] < 200 && values[3] > 800 && values[4] > 800 && mask3 == 1){
			LCD_clear();
			LCD_sendString("I Love You");
			mask0 = 1;
			mask1 = 1;
			mask2 = 1;
			mask3 = 0;
			mask4 = 1;
			mask5 = 1;
			mask6 = 1;
			mask7 = 1;
		}	
		if(values[0] > 800 && values[1] < 200 && values[2] < 200 && values[3] > 800 && values[4] < 200 && mask4 == 1){
			LCD_clear();
			LCD_sendString("*** WOW ***");
			mask0 = 1;
			mask1 = 1;
			mask2 = 1;
			mask3 = 1;
			mask4 = 0;
			mask5 = 1;
			mask6 = 1;
			mask7 = 1;
		}	
		if(values[0] > 800 && values[1] > 800 && values[2] > 800 && values[3] > 800 && values[4] > 800 && mask5 == 1){
			LCD_clear();
			LCD_sendString("Have a Good");
			LCD_setCursor(1,0);
			LCD_sendString("Life");
			mask0 = 1;
			mask1 = 1;
			mask2 = 1;
			mask3 = 1;
			mask4 = 1;
			mask5 = 0;
			mask6 = 1;
			mask7 = 1;
		}
		if(values[0] < 200 && values[1] < 200 && values[2] < 200 && values[3] <200 && values[4] > 800 && mask6 == 1){
			LCD_clear();
			LCD_sendString("Good Job");
			mask0 = 1;
			mask1 = 1;
			mask2 = 1;
			mask3 = 1;
			mask4 = 1;
			mask5 = 1;
			mask6 = 0;
			mask7 = 1;
		}
		if(values[0] < 200 && values[1] < 200 && values[2] < 200 && values[3] <200 && values[4] < 200 && mask7 == 1){
			LCD_clear();
			LCD_sendString("Silence!");
			mask0 = 1;
			mask1 = 1;
			mask2 = 1;
			mask3 = 1;
			mask4 = 1;
			mask5 = 1;
			mask6 = 1;
			mask7 = 0;
		}
		
    }
}

