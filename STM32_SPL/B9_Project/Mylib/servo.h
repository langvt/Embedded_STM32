#ifndef SERVO_H
#define SERVO_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

 /*
* struct: Servo
* Description:   Structure representing a servo motor controlled
*	- TIM_TypeDef *tim: Pointer to the timer (TIM) used to control the servo.
*   - uint16_t Channel: Timer (TIM) channel used to control the servo.
*   - uint8_t Angle: Angle of the servo, value from 0 to 255, representing the rotation angle of the servo.
*/
typedef struct
{
	TIM_TypeDef *tim;
	uint16_t Channel;
	uint8_t Angel;
} Servo;

void servo_Write( Servo *sv, uint8_t Angel);
void servo_Init(Servo *sv, TIM_TypeDef *tim, uint16_t channel);
#endif