

#ifndef DS3231_H
#define DS3231_H

/** Includes ---------------------------------------------------------------- */	
#include "I2C.h"
#define DS3231_ADDRESS 		(0x68 << 1)  

// Register location
#define DS3231_SECONDS			0x00
#define DS3231_MINUTES			0x01
#define DS3231_HOURS				0x02
#define DS3231_DAY					0x03
#define DS3231_DATE					0x04
#define DS3231_MONTH				0x05
#define DS3231_YEAR					0x06
#define DS3231_AlARM_MIN			0x08
#define DS3231_ALARM_HOUR		0x09
#define DS3231_TEMP_MSB			0x11
#define DS3231_TEMP_LSB 			0x12


/*
* struct: Time
* Description: Structure representing the current time and date, including alarm settings.
*   - int8_t second: Seconds (0-59).
*   - int8_t minute: Minutes (0-59).
*   - int8_t hour: Hours (0-23).
*   - int8_t day: Day of the week (1-7).
*   - int8_t date: Day of the month (1-31).
*   - int8_t month: Month (1-12).
*   - int8_t year: Year (0-99, representing 2000-2099).
*   - int8_t alarm_hour: Alarm hour (0-23).
*   - int8_t alarm_min: Alarm minute (0-59).
*/
typedef struct
{
	int8_t second;
	int8_t minute;
	int8_t hour;
	int8_t day;
	int8_t date;
	int8_t month;
	int8_t year;
	int8_t alarm_hour;
	int8_t alarm_min;
}Time;

/*
* struct: Temp
* Description: Structure representing the temperature read from the DS3231.
*   - uint8_t TempMSB: Most significant byte of the temperature.
*   - uint8_t TempLSB: Least significant byte of the temperature.
*   - float Teamperature: Temperature in degrees Celsius.
*/
typedef struct
{
	uint8_t TempMSB;
	uint8_t TempLSB;
	float Teamperature;
}Temp;


void rtc_read_time (Time *dt);
void rtc_write_time(Time *dt);


uint8_t Decimal2BCD(uint8_t num);
uint8_t BCD2_Decimal( uint8_t num);

void ds3231_Init(void);
void ds3231_setSeconds(Time *time );
uint8_t ds3231_getSeconds(void); 
void ds3231_setMinutes(Time *time); 
uint8_t ds3231_getMinutes(void);
void ds3231_setHours(Time *time);
uint8_t ds3231_getHours(void);
void ds3231_setDay(Time *time); 
uint8_t ds3231_getDay( void);
uint8_t ds3231_getDayOfWeek(Time *time);
void ds3231_setDate(Time *time);
uint8_t ds3231_getDate( void);
void ds3231_setMonth(Time *time); 
uint8_t ds3231_getMonth( void);
void ds3231_setYear(Time *time);  
uint8_t ds3231_getYear(void);
void ds3231_setAlarmHour(Time *time);  
uint8_t ds3231_getAlarmHour(void);
void ds3231_setAlarmMin(Time *time);  
uint8_t ds3231_getAlarmMin(void);
void ds3231_setTime(Time *time);
void ds3231_getTime(Time *time);
uint8_t ds3231_getTempInterger(Temp *temp);
uint8_t ds3231_getTempFraction(Temp *temp);
uint8_t ds3231_getTemp(Temp *temp);
#endif




