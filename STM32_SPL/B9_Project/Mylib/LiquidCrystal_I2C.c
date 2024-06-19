

#include "LiquidCrystal_I2C.h"

/************************ Low Level Function ***************************************************************/

/*
 * Function: lcdDelay
 * Description: Delays for a specified time in milliseconds.
 * Input:
 *   - uint16_t Time: Time in milliseconds to delay.
 * Output: None
 */
static void lcdDelay (uint16_t Time)
{
	Delay_Ms(Time);
}

/*
 * Function: lcd_send_cmd
 * Description: Sends a command to the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Command: The command to send.
 * Output: None
 * 
 * This function sends a command to the LCD by splitting the command into two 4-bit values.
 * It then sends these values to the LCD, setting the enable (EN) pin high and low to latch the data.
 */
static void lcd_send_cmd (LiquidCrystal_I2C *Lcd, uint8_t Command)
{
	char Data_H;
	char Data_L;
	uint8_t Buff[4];
	Data_H = Command&0xF0;
	Data_L = (Command<<4)&0xF0;
	Buff[0] = Data_H|(Lcd->Backlightval|LCD_RS_CLEAR|LCD_EN_SET); 		//0xXXXX.1100  en=1, rs=0
	Buff[1] = Data_H|(Lcd->Backlightval|LCD_RS_CLEAR|LCD_EN_CLEAR);	//0xXXXX.1000  en=0, rs=0
	Buff[2] = Data_L|(Lcd->Backlightval|LCD_RS_CLEAR|LCD_EN_SET); 		//0xXXXX.1100  en=1, rs=0
	Buff[3] = Data_L|(Lcd->Backlightval|LCD_RS_CLEAR|LCD_EN_CLEAR); 	//0xXXXX.1000  en=0, rs=0

	I2C_Write_No_Reg(Lcd->Addr, Buff[0] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[1] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[2] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[3] );
}

/*
 * Function: lcd_send_data
 * Description: Sends data to the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Data: The data to send.
 * Output: None
 * 
 * This function sends data to the LCD by splitting the data into two 4-bit values.
 * It then sends these values to the LCD, setting the RS (Register Select) pin high and low to specify data mode.
 */
 void lcd_send_data(LiquidCrystal_I2C *Lcd,uint8_t Data)
{
	uint8_t Data_H, Data_L;
	uint8_t Buff[4];
	Data_H = (Data&0xf0);
	Data_L = ((Data<<4)&0xf0);
	Buff[0] = Data_H|(Lcd->Backlightval|LCD_RS_SET|LCD_EN_SET); 		//0xXXXX.1101  en=1, rs=1
	Buff[1] = Data_H|(Lcd->Backlightval|LCD_RS_SET|LCD_EN_CLEAR); 	//0xXXXX.1001  en=0, rs=1
	Buff[2] = Data_L|(Lcd->Backlightval|LCD_RS_SET|LCD_EN_SET); 		//0xXXXX.1101  en=1, rs=1
	Buff[3] = Data_L|(Lcd->Backlightval|LCD_RS_SET|LCD_EN_CLEAR); 	//0xXXXX.1001  en=0, rs=1
	
	I2C_Write_No_Reg(Lcd->Addr, Buff[0] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[1] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[2] );
	I2C_Write_No_Reg(Lcd->Addr, Buff[3] );
}

/*
 * Function: lcd_putchar
 * Description: Sends a character to the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Data: The character to send.
 * Output: None
 */
void lcd_putchar(LiquidCrystal_I2C *Lcd,uint8_t Data)
{
	lcd_send_data(Lcd,Data);
}

/*
 * Function: lcd_clear_display
 * Description: Clears the display of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_clear_display (LiquidCrystal_I2C *Lcd)
{
	lcd_send_cmd (Lcd,LCD_CLEARDISPLAY);
	lcdDelay(1);
}

/*
 * Function: lcd_display_off
 * Description: Turns off the display of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_display_off(LiquidCrystal_I2C *Lcd) 
{
	Lcd->DisplayControl &= ~LCD_DISPLAYON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_display_on
 * Description: Turns on the display of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_display_on(LiquidCrystal_I2C *Lcd) 
{
	Lcd->DisplayControl |= LCD_DISPLAYON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_backlight_on
 * Description: Turns on the backlight of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_backlight_on(LiquidCrystal_I2C *Lcd)
{
	Lcd->Backlightval = LCD_BACKLIGHT;
	I2C_Write_No_Reg(Lcd->Addr, Lcd->Backlightval);
}

/*
 * Function: lcd_backlight_off
 * Description: Turns off the backlight of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_backlight_off(LiquidCrystal_I2C *Lcd)
{
	Lcd->Backlightval = LCD_NOBACKLIGHT;
	I2C_Write_No_Reg(Lcd->Addr, Lcd->Backlightval);
}

/*
 * Function: lcd_set_cursor
 * Description: Sets the cursor position on the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Rows: Row number (starting from 0).
 *   - uint8_t Col: Column number (starting from 0).
 * Output: None
 */
void lcd_set_cursor(LiquidCrystal_I2C *Lcd,uint8_t Rows, uint8_t Col)
{
	uint8_t rowOffsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_send_cmd(Lcd,LCD_SETDDRAMADDR | (Col + rowOffsets[Rows]));
}

/*
 * Function: lcd_set_cursor_on
 * Description: Turns on the cursor of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_set_cursor_on(LiquidCrystal_I2C *Lcd) 
{
	Lcd->DisplayControl |= LCD_CURSORON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_set_cursor_off
 * Description: Turns off the cursor of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_set_cursor_off(LiquidCrystal_I2C *Lcd)
{
	Lcd->DisplayControl &= ~LCD_CURSORON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_set_cursor_blink_on
 * Description: Turns on the blinking cursor of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_set_cursor_blink_on(LiquidCrystal_I2C *Lcd) 
{
	
	Lcd->DisplayControl |= LCD_BLINKON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_set_cursor_blink_off
 * Description: Turns off the blinking cursor of the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 * Output: None
 */
void lcd_set_cursor_blink_off(LiquidCrystal_I2C *Lcd) 
{
	Lcd->DisplayControl &= ~LCD_BLINKON;
	lcd_send_cmd(Lcd,LCD_DISPLAYCONTROL | Lcd->DisplayControl);
}

/*
 * Function: lcd_create_char
 * Description: Creates a custom character on the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Location: Location of the character (0 to 7).
 *   - uint8_t Charmap[]: Array containing the character data.
 * Output: None
 */
void lcd_create_char(LiquidCrystal_I2C *Lcd,uint8_t Location, uint8_t Charmap[]) 
{
	Location &= 0x7; 
	lcd_send_cmd(Lcd,LCD_SETCGRAMADDR | (Location << 3));
	for (int i=0; i<8; i++) {
		lcd_send_data(Lcd,Charmap[i]);
	}
}

/*
 * Function: lcd_write
 * Description: Writes a character to the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Location: Character to write.
 * Output: None
 */
void lcd_write(LiquidCrystal_I2C *Lcd,uint8_t Location)
{
	lcd_send_data(Lcd,Location);
}

/*
 * Function: lcd_printf
 * Description: Prints a formatted string to the LCD.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - const char* str: Format string.
 *   - ...: Additional arguments (if any) to be formatted.
 * Output: None
 */
void lcd_printf(LiquidCrystal_I2C *Lcd, const char* str, ...)
{
	char stringArray[20];
	uint8_t len;
	  va_list args;
	  va_start(args, str);
	  len = vsprintf(stringArray, str, args);
	  va_end(args);
		
	  for(uint8_t i=0;  i< len && i<16; i++)
	  {
		lcd_send_data(Lcd,(uint8_t)stringArray[i]);
	  }
}

/*
 * Function: lcd_init
 * Description: Initializes the LCD display.
 * Input:
 *   - LiquidCrystal_I2C *Lcd: Pointer to the LiquidCrystal_I2C structure.
 *   - uint8_t Addr: I2C address of the LCD display.
 * Output: None
 * 
 * This function initializes the LCD display by configuring its control settings, clearing the display,
 * setting the cursor position, and turning on the backlight.
 */
void lcd_init (LiquidCrystal_I2C *Lcd,uint8_t Addr)
{
	I2C_Config();
	Lcd->Addr = Addr;
	Lcd->DisplayControl |= LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	lcd_send_cmd (Lcd,0x33); 
	lcd_send_cmd (Lcd,0x32);
	lcdDelay(5);
	lcd_send_cmd (Lcd,LCD_CLEARDISPLAY); 
	lcdDelay(5);
	lcd_send_cmd (Lcd,0x0c); 	
	lcdDelay(5);
	lcd_send_cmd (Lcd,LCD_RETURNHOME); 
	lcdDelay(5);
	lcd_send_cmd (Lcd,LCD_SETDDRAMADDR);
	lcd_set_cursor_blink_off(Lcd);
	Lcd->Backlightval = LCD_BACKLIGHT;
}