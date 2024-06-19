#ifndef SERVO_H
#define SERVO_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

typedef struct
{
	TIM_TypeDef *tim;
	uint16_t Channel;
	uint8_t Angel;
} Servo;

void servo_Write( Servo *sv, uint8_t Angel);
void servo_Init(Servo *sv, TIM_TypeDef *tim, uint16_t channel);
#endif