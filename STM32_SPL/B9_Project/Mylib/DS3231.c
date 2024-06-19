/** Includes ---------------------------------------------------------------- */	
#include "DS3231.h"

/*
* Function: ds3231_Init
* Description: Initializes the DS3231 module by configuring the I2C interface.
* Input: None
* Output: None
*/
void ds3231_Init(void)
{
	I2C_Config();
}

/*
* Function: Decimal2BCD
* Description: Converts a decimal number to BCD format.
* Input: 
*   - uint8_t num: Decimal number to be converted.
* Output: 
*   - uint8_t: Converted BCD number.
*/
uint8_t Decimal2BCD(uint8_t num)
{
	return ((num/10) << 4) + (num%10);  // x0000 | 0000x = BCD
}

/*
* Function: BCD2_Decimal
* Description: Converts a BCD number to decimal format.
* Input: 
*   - uint8_t num: BCD number to be converted.
* Output: 
*   - uint8_t: Converted decimal number.
*/
uint8_t BCD2_Decimal( uint8_t num)
{
	return ((num >> 4) * 10) + (num&0x0F); // 0000x * 10 + 0000x & 00001111
}

/*
* Function: ds3231_setSeconds
* Description: Sets the seconds in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the seconds to be set.
* Output: None
*/
void ds3231_setSeconds(Time *time )
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_SECONDS, Decimal2BCD(time->second));
}

/*
* Function: ds3231_getSeconds
* Description: Gets the seconds from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current seconds.
*/
uint8_t ds3231_getSeconds(void)
{
	uint8_t seconds;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_SECONDS, &seconds);
	return BCD2_Decimal(seconds);
}

/*
* Function: ds3231_setMinutes
* Description: Sets the minutes in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the minutes to be set.
* Output: None
*/
void ds3231_setMinutes(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_MINUTES, Decimal2BCD(time->minute));
}

/*
* Function: ds3231_getMinutes
* Description: Gets the minutes from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current minutes.
*/
uint8_t ds3231_getMinutes(void)
{
	uint8_t minutes;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_MINUTES, &minutes);
	return BCD2_Decimal(minutes);
}

/*
* Function: ds3231_setHours
* Description: Sets the hours in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the hours to be set.
* Output: None
*/
void ds3231_setHours(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_HOURS, Decimal2BCD(time->hour));
}

/*
* Function: ds3231_getHours
* Description: Gets the hours from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current hours.
*/
uint8_t ds3231_getHours(void)
{
	uint8_t hours;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_HOURS, &hours);
	return BCD2_Decimal (hours);
}

/*
* Function: ds3231_setDay
* Description: Sets the day in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the day to be set.
* Output: None
*/
void ds3231_setDay(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_DAY, Decimal2BCD(time->day));
}

/*
* Function: ds3231_getDay
* Description: Gets the day from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current day.
*/
uint8_t ds3231_getDay( void)
{
	uint8_t day;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_DAY, &day);
	return BCD2_Decimal (day);
}

/*
* Function: ds3231_getDayOfWeek
* Description: Gets the day of the week based on the date.
* Input: 
*   - Time *time: Pointer to a Time structure.
* Output: 
*   - uint8_t: The current day of the week.
*/
uint8_t ds3231_getDayOfWeek(Time *time)
{
uint16_t d    = time ->date   ;
uint16_t m    = time ->month    ;
uint16_t y    = 2000 + time ->year ; 

uint8_t weekday  =(d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
	
	return weekday;
}

/*
* Function: ds3231_setDate
* Description: Sets the date in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the date to be set.
* Output: None
*/
void ds3231_setDate(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_DATE, Decimal2BCD(time->date));
}

/*
* Function: ds3231_getDate
* Description: Gets the date from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current date.
*/
uint8_t ds3231_getDate( void)
{
	uint8_t date;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_DATE, &date);
	return BCD2_Decimal (date);
}

/*
* Function: ds3231_setMonth
* Description: Sets the month in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the month to be set.
* Output: None
*/
void ds3231_setMonth(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_MONTH, Decimal2BCD(time->month));
}

/*
* Function: ds3231_getMonth
* Description: Gets the month from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current month.
*/
uint8_t ds3231_getMonth(void)
{
	uint8_t month;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_MONTH, &month);
	return BCD2_Decimal (month);
}

/*
* Function: ds3231_setYear
* Description: Sets the year in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the year to be set.
* Output: None
*/
void ds3231_setYear(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_YEAR, Decimal2BCD(time->year));
}

/*
* Function: ds3231_getYear
* Description: Gets the year from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current year.
*/
uint8_t ds3231_getYear(void )
{
	uint8_t year;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_YEAR, &year);
	return BCD2_Decimal(year);
}

/*
* Function: ds3231_setAlarmHour
* Description: Sets the alarm hour in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the alarm hour to be set.
* Output: None
*/
void ds3231_setAlarmHour(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_ALARM_HOUR, Decimal2BCD(time->alarm_hour));
}

/*
* Function: ds3231_getAlarmHour
* Description: Gets the alarm hour from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current alarm hour.
*/
uint8_t ds3231_getAlarmHour(void)
{
	uint8_t alarmhour;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_ALARM_HOUR, &alarmhour);
	return BCD2_Decimal(alarmhour);
}

/*
* Function: ds3231_setAlarmMin
* Description: Sets the alarm minute in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing the alarm minute to be set.
* Output: None
*/
void ds3231_setAlarmMin(Time *time)
{
I2C_Write_Reg(DS3231_ADDRESS, DS3231_AlARM_MIN, Decimal2BCD(time->alarm_min));
}	

/*
* Function: ds3231_getAlarmMin
* Description: Gets the alarm minute from the DS3231.
* Input: None
* Output: 
*   - uint8_t: The current alarm minute.
*/
uint8_t ds3231_getAlarmMin(void)
{
	uint8_t alarmmin;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_AlARM_MIN, &alarmmin);
	return BCD2_Decimal(alarmmin);
}


/*
* Function: ds3231_setTime
* Description: Sets the complete time (seconds, minutes, hours, day, date, month, year, alarm hour, alarm minute) in the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure containing all the time values to be set.
* Output: None
*/
void ds3231_setTime(Time *time)
{
	ds3231_setSeconds(time);
	ds3231_setMinutes(time); 
	ds3231_setHours(time);
	ds3231_setDay(time); 
	ds3231_setDate(time);
	ds3231_setMonth(time); 
	ds3231_setYear(time);  
	ds3231_setAlarmHour(time);
	ds3231_setAlarmMin(time);
}


/*
* Function: ds3231_getTime
* Description: Gets the complete time (seconds, minutes, hours, day, date, month, year, alarm hour, alarm minute) from the DS3231.
* Input: 
*   - Time *time: Pointer to a Time structure where the time values will be stored.
* Output: None
*/
void ds3231_getTime(Time *time)
{
	time->second = (int8_t)ds3231_getSeconds();
	time->minute = (int8_t)ds3231_getMinutes();
	time->hour = (int8_t)ds3231_getHours();
	time->day = (int8_t)ds3231_getDay();
	time->date = (int8_t)ds3231_getDate();
	time->month = (int8_t)ds3231_getMonth();
	time->year = (int8_t)ds3231_getYear();	
	time ->alarm_hour = (int8_t) ds3231_getAlarmHour();
	time ->alarm_min = (int8_t) ds3231_getAlarmMin();
}

/*
* Function: ds3231_getTempInterger
* Description: Gets the integer part of the temperature from the DS3231.
* Input: 
*   - Temp *temp: Pointer to a Temp structure where the temperature value will be stored.
* Output: 
*   - uint8_t: The integer part of the temperature.
*/
uint8_t ds3231_getTempInterger(Temp *temp)
{
	uint8_t TempInterger;
	I2C_Read_Reg(DS3231_ADDRESS,DS3231_TEMP_MSB, &TempInterger);
	 temp->TempMSB = TempInterger;
	return temp->TempMSB;
}


/*
* Function: ds3231_getTempFraction
* Description: Gets the fractional part of the temperature from the DS3231.
* Input: 
*   - Temp *temp: Pointer to a Temp structure where the temperature value will be stored.
* Output: 
*   - uint8_t: The fractional part of the temperature.
*/
uint8_t ds3231_getTempFraction(Temp *temp)
{
	uint8_t TempFraction;
	I2C_Read_Reg(DS3231_ADDRESS,DS3231_TEMP_LSB, &TempFraction);
	 temp->TempMSB = TempFraction ;
	return (temp->TempLSB >> 6)  *25;
}

/*
* Function: ds3231_getTemp
* Description: Gets the complete temperature (integer and fractional parts) from the DS3231.
* Input: 
*   - Temp *temp: Pointer to a Temp structure where the temperature value will be stored.
* Output: 
*   - float: The complete temperature.
*/
uint8_t ds3231_getTemp(Temp *temp)
{
    uint8_t tempInteger;
    uint8_t tempFraction;

    // read MSB from DS3231
    I2C_Read_Reg(DS3231_ADDRESS, DS3231_TEMP_MSB, &tempInteger);
    temp->TempMSB = tempInteger;

    //  read LSB from DS3231
    I2C_Read_Reg(DS3231_ADDRESS, DS3231_TEMP_LSB, &tempFraction);
    temp->TempLSB = tempFraction;

    //  Calculate and return the total temperature
     temp->Teamperature = (float) ((temp->TempMSB & 0x7F) + ((temp->TempLSB >> 6) * 0.25));
	return temp ->Teamperature;
}
