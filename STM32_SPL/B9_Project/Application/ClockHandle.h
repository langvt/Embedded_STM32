#ifndef CLOCKHANDLE_H
#define CLOCKHANDLE_H

#include "main.h"

/*
* enum: ClockState
* Description: Enumeration representing different states of the clock system.
*   - NORMAL_STATE: Normal clock display mode.
*   - SETTING_HOUR_STATE: State for setting the hour.
*   - SETTING_MIN_STATE: State for setting the minute.
*   - SETTING_SEC_STATE: State for setting the second.
*   - SETTING_DATE_STATE: State for setting the date.
*   - SETTING_MONTH_STATE: State for setting the month.
*   - SETTING_YEAR_STATE: State for setting the year.
*   - ALARM_HOUR_STATE: State for setting the alarm hour.
*   - ALARM_MIN_STATE: State for setting the alarm minute.
*/
typedef enum
{
	NORMAL_STATE ,
	SETTING_HOUR_STATE,
	SETTING_MIN_STATE,
	SETTING_SEC_STATE,
	SETTING_DATE_STATE,
	SETTING_MONTH_STATE,
	SETTING_YEAR_STATE,
	ALARM_HOUR_STATE,
	ALARM_MIN_STATE,
}ClockState ;

/*
* enum: ServoState
* Description: Enumeration representing the states of a servo motor.
*   - SERVO_STOPPED: Servo motor is stopped.
*   - SERVO_MOVING: Servo motor is in motion.
*/
typedef enum
{
	SERVO_STOPPED,
	SERVO_MOVING
}ServoState;

// Function prototypes
void GPIOLED_Config(void);
void Max_Min_Number(int8_t *Number, int8_t Max, int8_t Min, int8_t Plus );
int8_t checkleapYear(uint8_t Year);
int8_t getMaxDate(int8_t Month, int8_t Year);
void adjustTime(int8_t Plus);
void resetTimeStart(void);
void updateTimeNow(void);
void clockTimeUpdate(void);
void settingTimeBlink(void);
void alarmUpdate(void);
void updatCheckAlarm(void);
void checkAlarm(void);
void alarmScreen(void);
void clockHandle(void);
void clockInit(void);
#endif
