

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
#define DS3231_TEMP_UPBYTE		0x11
#define DS3231_TEMP_LOWBYTE 	0x12

typedef struct
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}Time;

typedef struct
{
	uint8_t TempUp;
	uint8_t TempLow;
	uint16_t Temperature;
	
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
void ds3231_setDate(Time *time);
uint8_t ds3231_getDate( void);
void ds3231_setMonth(Time *time); 
uint8_t ds3231_getMonth( void);
void ds3231_setYear(Time *time);  
uint8_t ds3231_getYear(void);

void ds3231_setTime(Time *time);
void ds3231_getTime(Time *time);
uint8_t ds3231_getTempUpByte(Temp *temp);
uint8_t ds3231_getTempLowByte(Temp *temp);
uint8_t ds3231_getTemp(Temp *temp);
#endif




