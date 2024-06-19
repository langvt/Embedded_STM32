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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
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
void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TIMBaseInitStructure;
	TIM_TIMBaseInitStructure.TIM_Prescaler =  64000 - 1;
	TIM_TIMBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TIMBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TIMBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TIMBaseInitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void Delay_us(uint16_t us)
{
	TIM_SetCounter(TIM2, 0);
	TIM_SetAutoreload(TIM2, us);
	while(TIM_GetCounter(TIM2) < us);
	
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		//GPIO_TogglePin(GPIOC, GPIO_Pin_13
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_us(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_us(1000);
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(void)
{
	SystemInit();
	SystickInit();
	GPIO_Config();
	NVIC_Config();
	TIM_Config();
	while(1)
		{
			
		}
}