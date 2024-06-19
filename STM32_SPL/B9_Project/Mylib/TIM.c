#include "TIM.h"

// create fPWM= 50hz, ARR = 20000 (), PSC = 72

/*
* Function: TIM_Config
* Description: Configures the timer (TIM) for generating a PWM signal with a frequency of 50Hz.
*              Sets the Prescaler (PSC) to 72 and the Auto-Reload Register (ARR) to 20000.
* Input: None
* Output: None
*/
void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(TIM_RCC, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimBaseinitStructure;
	TIM_TimBaseinitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseinitStructure.TIM_Prescaler = 72-1;
	TIM_TimBaseinitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseinitStructure.TIM_Period = 20000 - 1;

	TIM_TimeBaseInit(TIMx, &TIM_TimBaseinitStructure);
	TIM_Cmd(TIMx, ENABLE);
}

/*
* Function: PWM_Config
* Description: Configures the PWM output on a specific GPIO pin. Initializes the GPIO pin as an alternate function push-pull.
*              Sets up the PWM mode, pulse, polarity, and output state.
* Input: None
* Output: None
*/
void PWM_Config(void)
{
	
	/** GPIO config*/
	RCC_APB1PeriphClockCmd(PWM_GPIO_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PWM_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(PWM_GPIO, &GPIO_InitStructure);
	
	/**PWM config*/
	TIM_OCInitTypeDef TIM_OCInitstructure;
	TIM_OCInitstructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitstructure.TIM_Pulse = 0;
	TIM_OCInitstructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitstructure.TIM_OutputState = ENABLE;
	
	TIM_OC1Init(TIMx, &TIM_OCInitstructure);
}

/*
* Function: TIMER_Init
* Description: Initializes the timer and PWM configuration by calling TIM_Config and PWM_Config functions.
* Input: None
* Output: None
*/
void TIMER_Init(void)
{
	TIM_Config();
	PWM_Config();
}