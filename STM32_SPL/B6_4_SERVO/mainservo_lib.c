#include "systick.h"
#include "servo.h"
#include "stm32f10x_tim.h"

	Servo sv1;

void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//pin PWM
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

// create fPWM= 50hz, ARR = 20000 (), PSC = 72
void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TIMBaseInitStructure;
	TIM_TIMBaseInitStructure.TIM_Prescaler =  72- 1;
	TIM_TIMBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TIMBaseInitStructure.TIM_Period = 20000 - 1;
	TIM_TIMBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TIMBaseInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_Config(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	TIM_OCInitStructure.TIM_OutputState =ENABLE;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
}

void PWM_setDuty(TIM_TypeDef *TIMx, uint32_t Channel, uint16_t duty)
{
    uint16_t Period = TIMx->ARR + 1;
    uint32_t Pulse = (duty * Period) / 100;

    switch (Channel)
    {
    case TIM_Channel_1:
        TIMx->CCR1 = Pulse;
        break;
    case TIM_Channel_2:
        TIMx->CCR2 = Pulse;
        break;
    case TIM_Channel_3:
        TIMx->CCR3 = Pulse;
        break;
    case TIM_Channel_4:
        TIMx->CCR4 = Pulse;
        break;
    default:
        break;
    }
}
		
int main(void)
{


	SystickInit();
	GPIO_Config();
	TIM_Config();
	PWM_Config();
	servo_Init(&sv1, TIM2, TIM_Channel_1);


	while(1)
	{
		servo_Write(&sv1, 0);
		Delay_Ms(1000);
		servo_Write(&sv1, 180);
		Delay_Ms(1000);
	}
}
