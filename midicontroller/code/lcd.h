////////////////////////////////////////////////////////////////////////////
////                             LCD.C                                  ////
////                 Driver for common LCD modules                      ////
////                                                                    ////
////  lcd_init()   Must be called before any other function.            ////
////                                                                    ////
////  lcd_putc(c)  Will display c on the next position of the LCD.      ////
////                     The following have special meaning:            ////
////                      \f  Clear display                             ////
////                      \n  Go to start of second line                ////
////                      \b  Move back one position                    ////
////                                                                    ////
////  lcd_gotoxy(x,y) Set write position on LCD (upper left is 1,1)     ////
////                                                                    ////
////  lcd_getc(x,y)   Returns character at position x,y on LCD          ////
////                                                                    ////
////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,1997 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////

// This code Modified by Angelo Fraietta for use as a 3 wire interface
// using a 16 x 2 LCD

// The following Pins must be defined
// LCD_CLK
// LCD_DATA
// LCD_ENABLE


#define lcd_type 2           // 0=5x7, 1=5x10, 2=2 lines
#define lcd_line_two 0x40    // LCD RAM address for the second line

const byte LCD_INIT_STRING [] = {0x38, 0x01, 0x0C}; 
                             // These bytes need to be sent to the LCD
                             // to start it up.


                             // The following are used for setting
                             // the I/O port direction register.


// sends data to LCD. If data_type is True, then is a data byte, otherwise is a command byte
void lcd_send_byte(byte out_byte, short data_type) 
{
	int byte_num;
	// prepare clock and enable
	output_low (LCD_CLK);
	output_high (LCD_ENABLE);
  
	for (byte_num = 0; byte_num < 8; byte_num++)
		{	
			// write the high bit
			output_bit (LCD_DATA, bit_test (out_byte, 7));
			out_byte<<=1;

			// now clock register
			output_high (LCD_CLK);
			output_low (LCD_CLK);
		}

	// now output the RS bit (do not clock)
	output_bit (LCD_DATA,data_type);
  	
  output_low (LCD_ENABLE);
}


void lcd_init() 
{
	byte i;
  byte j;

	delay_ms(25);
  
  for (j = 0; j < 3; j++)
    {
    lcd_send_byte(0x38, false);
    delay_ms(2);
    }

	for(i = 0; i< sizeof(LCD_INIT_STRING); i++)
		{
			lcd_send_byte(LCD_INIT_STRING[i], false);
      delay_ms(2);
		}
}


void lcd_gotoxy( byte x, byte y) {
   byte address;

   if(y!=1)
     address=lcd_line_two;
   else
     address=0;
   address+=x-1;
   lcd_send_byte(0x80|address, false);
}

void lcd_putc( char c) {
   switch (c) 
		 {
		 case '\f': 
			 lcd_send_byte(1, false);
			 delay_ms(2);
			 break;
			 
		 case '\n': 
			 lcd_gotoxy(1,2);        
			 break;

     case '\b': 
			 lcd_send_byte(0x10, false);  
			 break;

     default: 
			 lcd_send_byte(c, true);     
			 break;
   }
}


