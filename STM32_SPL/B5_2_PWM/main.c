#include "systick.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_gpio.h"

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* get current Output Data Register value */
  odr = GPIOx->ODR;

  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16u) | (~odr & GPIO_Pin);
}

void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

// create fPWM= 1000hz, ARR = 1000 (1s), PSC = 64, tCNT = 1ms = 1 hz 
void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TIMBaseInitStructure;
	TIM_TIMBaseInitStructure.TIM_Prescaler =  64- 1;
	TIM_TIMBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TIMBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TIMBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TIMBaseInitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_Config(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	TIM_OCInitStructure.TIM_OutputState =ENABLE;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void PWM_setDuty(TIM_TypeDef *TIMx, uint32_t Channel, uint16_t duty)
{
	uint16_t Period = TIMx ->ARR +1;
	uint16_t Pulse = (duty * Period) / 100;
	
	switch(Channel)
	{
		case 1:
			TIMx -> CCR1 = Pulse;
			break;
		case 2:
			TIMx-> CCR2 = Pulse;
			break;
		case 3:
			TIMx -> CCR4 = Pulse;
			break;
		case 4:
			TIMx-> CCR4 = Pulse;
	
		break;
	}
		
}
int main(void)
{
	SystemInit();
	SystickInit();
	GPIO_Config();
	NVIC_Config();
	PWM_Config();
	TIM_Config();
	
// set duty = 20%
	//TIM2->CCR1 = 200;
	//TIM_SetCompare1(TIM2, 100);
	PWM_setDuty(TIM2, 1, 1000); 
	
	while(1)
		{
			
		}
}