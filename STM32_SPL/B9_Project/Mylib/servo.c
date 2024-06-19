#include "servo.h"

/*
* Function: map
* Description: Maps a number from one range to another.
* Input: x: The number to map.
*        in_min: The lower bound of the input range.
*        in_max: The upper bound of the input range.
*        out_min: The lower bound of the output range.
*        out_max: The upper bound of the output range.
* Output: The mapped value.
*/
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	//x*(out_max - out_min)
	//  out_min+ (in_max- in_min)
}

/*
* Function: servo_Write
* Description: Sets the angle of the servo by updating the CCR register based on the specified angle.
* Input: sv: Pointer to the Servo structure.
*        Angel: Desired angle (0 to 180 degrees).
* Output: None
*/
void servo_Write( Servo *sv, uint8_t Angel)
{
	// Angel: 0->180
	// CCR: 1000->2000(chu ki xung cap(Ton))	
	// CCR = Angle * 1000 / 180 + 1000
	//CCR = (Angel - 0)*(2000-1000) /(180-0) + 1000
	//uint16_t CCR = (Angel - 0)*(2400-544) /(180-100) + 544          // 100 la goc nho nhat co the thay = bat ki < 180
	uint16_t CCR = map(Angel, 0, 180, 544, 2400);
	switch(sv->Channel)
		{
		case TIM_Channel_1:
			sv->tim ->CCR1= CCR;
			break;
		case TIM_Channel_2:
			sv->tim ->CCR2= CCR;
			break;
		case TIM_Channel_3:
			sv->tim ->CCR3= CCR;
			break;
		case TIM_Channel_4:
			sv->tim ->CCR4= CCR;
			break;
		}
}

/*
* Function: servo_Init
* Description: Initializes the Servo structure with the specified timer and channel.
* Input: sv: Pointer to the Servo structure.
*        tim: Pointer to the timer (TIM) to be used.
*        channel: Timer channel to be used.
* Output: None
*/
void servo_Init(Servo *sv, TIM_TypeDef *tim, uint16_t channel)
{
	sv->tim = tim;
	sv->Channel = channel;
	
}
