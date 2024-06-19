#include "ClockHandle.h"



LiquidCrystal_I2C lcd;
Time time;
extern Temp temp;
ClockState Clock_State = NORMAL_STATE;
Servo sv1;




const char* arrDayOfWeek [] = {"SUN", "MON", "TUE", "WED" , "THU", "FRI", "SAT"};


//----------------------------------------------------Utilities -----------------------------------------------------//

/*
* Function: Max_Min_Number
* Description: Adjusts the value of a number within a specified range.
* Input:
*   - int8_t *Number: Pointer to the number to be adjusted.
*   - int8_t Max: Maximum value allowed.
*   - int8_t Min: Minimum value allowed.
*   - int8_t Plus: Flag indicating whether to increment (1) or decrement (0) the number.
* Output: None
*/
void Max_Min_Number(int8_t *Number, int8_t Max, int8_t Min, int8_t Plus )
{
	if(Plus  == 1)
	{
		(*Number) ++;
		if( *Number  > Max )
		{
			*Number  = Min;
		}
	}
	else 
	{
		(*Number)  --;
		if(*Number < Min)
		{
			*Number = Max;
		}
	}
}

/*
* Function: checkleapYear
* Description: Checks if a given year is a leap year.
* Input:
*   - uint8_t Year: Year to be checked.
* Output:
*   - int8_t: Returns 1 if the year is a leap year, otherwise returns 0.
*/
int8_t checkleapYear(uint8_t Year)
{
	if(((Year % 4  == 0) && (Year % 100 != 0)) || (Year % 400 == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
* Function: getMaxDate
* Description: Gets the maximum number of days in a given month and year.
* Input:
*   - int8_t Month: Month for which to determine the maximum number of days.
*   - int8_t Year: Year for which to determine the maximum number of days.
* Output:
*   - int8_t: Maximum number of days in the specified month and year.
*/
int8_t getMaxDate(int8_t Month, int8_t Year)
{
	switch(Month)
	{
		case 1: case  3: case 5: case 7: case 8:
			return 31;
		case 4: case 6: case 9: case 10: case 11: case 12:
			return 30;
		case 2:
			if(checkleapYear( Year))
			{
				return 29;
			}
			else 
			{
				return 28;
			}
	}
}

//--------------------------------------------------adjust time button call back--------------------------------------------//

/*
* Function: adjustTime
* Description: Adjusts the time based on the current clock state.
* Input:
*   - int8_t Plus: Flag indicating whether to increment (1) or decrement (0) the time.
* Output: None
*/
	void adjustTime(int8_t Plus)
{
	switch(Clock_State)
		{
			case SETTING_HOUR_STATE:
			{
				Max_Min_Number(&time.hour, 23, 0, Plus);
				ds3231_setTime(&time);
				break;
			}
			case SETTING_MIN_STATE:
			{
				Max_Min_Number(&time.minute, 59, 0, Plus);
				ds3231_setTime(&time);
				break;
			}
			case SETTING_SEC_STATE:
			{
				Max_Min_Number(&time.second, 59, 0, Plus);
				ds3231_setTime(&time);
				break;
			}
			case SETTING_DATE_STATE:
			{
				int8_t MaxDate = getMaxDate(time.month, time.year);
				Max_Min_Number(&time.date, MaxDate, 1, Plus);
				ds3231_setTime(&time);
				break;
			}
			case SETTING_MONTH_STATE:
			{
				Max_Min_Number(&time.month, 12, 1, Plus);
				int8_t MaxDate = getMaxDate(time.month, time.year);
				if(time.date > MaxDate ) // if 31 > 28
				{
					time.date = MaxDate;
				}
				ds3231_setTime(&time);
				break;
			}
			case SETTING_YEAR_STATE:
			{
				Max_Min_Number(&time.year, 99, 1, Plus);
				ds3231_setTime(&time);
				break;
			}
			case ALARM_HOUR_STATE:
			{
				Max_Min_Number(&time.alarm_hour, 23, 0, Plus);
				ds3231_setTime(&time);
				break;
			}
			
			case ALARM_MIN_STATE:
			{
				Max_Min_Number(&time.alarm_min, 59, 0, Plus);
				ds3231_setTime(&time);
				break;
			}
			
			default  : break;
		}
}

//--------------------update time ----------------------------------------------------------------//


static uint32_t TimeStarPress = 0;

/*
* Function: resetTimeStart
* Description: Resets the time start to the current tick value.
* Input: None
* Output: None
*/
void resetTimeStart(void)
{
	TimeStarPress = getTick();
}

/*
* Function: updateTimeNow
* Description: Updates the current time on the LCD display.
* Input: None
* Output: None
*/
void updateTimeNow(void)
{
	    uint8_t customChar[] = {
        0x07,
        0x05,
        0x07,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    lcd_create_char(&lcd, 0, customChar);
	
	ds3231_getTime(&time);
	ds3231_getTempInterger(&temp);
//	ds3231_getTempFraction(&temp);
	ds3231_getTemp(&temp);
	uint8_t DayOfWeek = ds3231_getDayOfWeek(&time);
	lcd_set_cursor(&lcd, 0, 2);
	lcd_printf(&lcd ,"%02d:%02d:%02d  ", time.hour, time.minute, time.second);
	lcd_set_cursor(&lcd, 2, 3);
	lcd_printf(&lcd, "%s %02d/%02d/20%02d", arrDayOfWeek[DayOfWeek], time.date, time.month, time.year);
	lcd_set_cursor(&lcd, 0, 14);
	lcd_printf(&lcd, "%02d",temp.TempMSB);
	lcd_set_cursor(&lcd, 0, 16);
    lcd_send_data(&lcd, 0); // In ký tự đặc biệt
    lcd_send_data(&lcd, 'C'); // In ký tự 'C'
}

/*
* Function: clockTimeUpdate
* Description: Updates the clock time periodically.
* Input: None
* Output: None
*/
void clockTimeUpdate(void)
{
	static uint32_t Update = 0;
	updateTimeNow();
	if(getTick() - Update == 500)
	{
		updateTimeNow();
		Update = getTick();
	}
}

//----------------------------------------------------Blink time on LCD  -----------------------------------------------------//

/*
* Function: settingTimeBlink
* Description: Blinks the setting time on the LCD display based on the clock state.
* Input: None
* Output: None
*/
void settingTimeBlink()
{
	static uint32_t t_Blink = 0;
	static uint8_t is_Show = 1;
	
	if(getTick() - t_Blink >= 200)
	{
		is_Show =! is_Show;
		ds3231_getTime(&time);
		char Line_0 [16];
		char Line_2[16];
		uint8_t DayOfWeek = ds3231_getDayOfWeek(&time);
		sprintf(Line_0, "%02d:%02d:%02d", time.hour, time.minute, time.second);
		sprintf(Line_2, "%s %02d/%02d/20%02d", arrDayOfWeek[DayOfWeek], time.date, time.month, time.year);
		
		if(is_Show == 1)
		{
			switch(Clock_State)
			{
				case  SETTING_HOUR_STATE:
					Line_0[0] = Line_0[1] = '  ';
					break;
				case  SETTING_MIN_STATE:
					Line_0[3] = Line_0[4] = '  ';
					break;
				case  SETTING_SEC_STATE:
					Line_0[6] = Line_0[7] = '  ';
					break;
				case  SETTING_DATE_STATE:
					Line_2[4] =  Line_2[5] = '  ';
					break;
				case  SETTING_MONTH_STATE:
					Line_2[7] =  Line_2[8] = '  ';
					break;
				case  SETTING_YEAR_STATE:
					Line_2[10] =  Line_2[11] =  Line_2[12] =  Line_2[13] = '  ';
					break;
			}
		}
		lcd_set_cursor(&lcd, 0, 2);
		lcd_printf(&lcd, "%s" , Line_0);
		lcd_set_cursor(&lcd, 2, 3);
		lcd_printf(&lcd, "%s", Line_2);
		t_Blink = getTick();
	}
}


//--------------------------------------------------- alarm  -----------------------------------------------------//
static uint32_t TimeOn = 0;
ServoState Servo_State = SERVO_STOPPED;
static uint32_t ServoStartTime = 0;

/*
* Function: checkAlarm
* Description: Checks if the current time matches the alarm time and handles the alarm accordingly.
* Input: None
* Output: None
*/
void checkAlarm(void)
{
	if(time.alarm_hour == time.hour && time.alarm_min == time.minute)
	{	
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		if(getTick() - TimeOn >= 1300)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			TimeOn = getTick();
			
			if(Servo_State == SERVO_STOPPED)
			{
				servo_Write(&sv1, 0);
				Servo_State = SERVO_MOVING;
			}
			else if(Servo_State == SERVO_MOVING && getTick() - ServoStartTime >= 1000)
			{
				servo_Write(&sv1, 180);
				Servo_State = SERVO_STOPPED;
				ServoStartTime = getTick();
			}
		}
		char alarmOn [16] = "ALARM";
		static uint32_t t_Blink = 0;
		static uint8_t is_Show = 1;
		
		if(getTick() - t_Blink >= 200)
		{
			is_Show =! is_Show;
			if(is_Show ==1)
			{
				alarmOn[0] = alarmOn[1] = alarmOn[2] =alarmOn[3] = alarmOn[4] ='  ';
			}
			lcd_set_cursor(&lcd, 3, 7);
			lcd_printf(&lcd ,"%s", alarmOn);
			t_Blink = getTick();
		}
		
	}
	else if (time.alarm_hour !=time.hour ||  time.alarm_min != time.minute)
	{
		Servo_State = SERVO_STOPPED;
		ADC_UtilitiesHandle();
		lcd_set_cursor(&lcd, 3, 7);
		lcd_printf(&lcd ,"     ");
	}

}

/*
* Function: alarmUpdate
* Description: Updates the alarm time on the LCD display.
* Input: None
* Output: None
*/
void alarmUpdate(void)
{
		char Line_2[16];
		sprintf(Line_2, "%02d:%02d", time.alarm_hour, time.alarm_min);
		lcd_clear_display(&lcd);
		lcd_set_cursor(&lcd, 0, 7);
		lcd_printf(&lcd , "ALARM");
		lcd_set_cursor(&lcd, 2, 7);
		lcd_printf(&lcd, Line_2);
}

/*
* Function: alarmScreen
* Description: Displays the alarm time on the LCD screen with blinking digits based on the clock state.
* Input: None
* Output: None
*/
void alarmScreen(void)
{
	static uint32_t t_Blink = 0;
	static uint8_t is_Show = 1;
	
	if(getTick() - t_Blink >= 200)
	{
		is_Show =! is_Show;
		char Line_2[16];
		sprintf(Line_2, "%02d:%02d", time.alarm_hour, time.alarm_min);
	
		if(is_Show == 1)
		{
			switch(Clock_State)
			{
				case ALARM_HOUR_STATE:
					Line_2[0] = Line_2[1] = '  ';
					break;
				case ALARM_MIN_STATE:
					Line_2[3] = Line_2[4] = '  ';
					break;
			}
		}
		lcd_set_cursor(&lcd, 0, 7);
		lcd_printf(&lcd , "ALARM");
		lcd_set_cursor(&lcd, 2, 7);
		lcd_printf(&lcd, Line_2);
		t_Blink = getTick();
	}
}

/*
* Function: GPIOLED_Config
* Description: Configures the GPIO for LED output.
* Input: None
* Output: None
*/
void GPIOLED_Config(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitTypeDef GPIO_InitStruc;
		GPIO_InitStruc.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStruc.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_InitStruc.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStruc);

	}
//---------------------------------------------------Clock  handle -----------------------------------------------------//

/*
* Function: clockHandle
* Description: Handles clock operations based on the current clock state.
* Input: None
* Output: None
*/
void clockHandle(void)
{
	switch(Clock_State)
		{
			case NORMAL_STATE:
				clockTimeUpdate();
				break;
			case SETTING_HOUR_STATE:
			case SETTING_MIN_STATE:
			case SETTING_SEC_STATE:
			case SETTING_DATE_STATE:
			case SETTING_MONTH_STATE:
			case SETTING_YEAR_STATE:
			{
				settingTimeBlink();
				if(getTick() - TimeStarPress >= 5000)
				{
					Clock_State = NORMAL_STATE;
				}
			}
				break;
			case ALARM_HOUR_STATE: 
			case ALARM_MIN_STATE:
			{
				alarmScreen();
					
				if(getTick() - TimeStarPress >= 5000)
				{
					Clock_State = NORMAL_STATE;

				}
			}
				break;
			default: break;
		}
	}

/*
* Function: clockInit
* Description: Initializes the clock by configuring GPIO, LCD, DS3231, servo, timer, and ADC utilities.
* Input: None
* Output: None
*/
void clockInit(void)
{	
	GPIOLED_Config();
	lcd_init(&lcd, LCD_ADDR);
	ds3231_Init();
	servo_Init(&sv1,TIMx,TIM_Channel_1);
	TIMER_Init();
	ADC_Utilities_Init();
}
