#include "servo.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	//x*(out_max - out_min)
	//  out_min+ (in_max- in_min)
}

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

void servo_Init(Servo *sv, TIM_TypeDef *tim, uint16_t channel)
{
	sv->tim = tim;
	sv->Channel = channel;
	
}
