#include "systick.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#define 			HCSR04_TRIG_Pin					GPIO_Pin_0
#define 			HCSR04_ECHO_EXT_Pin			GPIO_Pin_1

void GPIO_Config (void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_EXT_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_WriteBit(GPIOA, HCSR04_TRIG_Pin, 0);
}

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_Line1 ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

void EXTI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode =  EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStructure);
}

void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TIMBaseInitStructure;
	TIM_TIMBaseInitStructure.TIM_Prescaler =  64 - 1;
	TIM_TIMBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TIMBaseInitStructure.TIM_Period = 65535 - 1;
	TIM_TIMBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TIMBaseInitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

typedef enum
{
	HCSR04_IDLE_STATE,							// trang thai chua do
	HCSR04_WAIT_EXT_RISING_STATE,			// trang thai xung len
	HCSR04_WAIT_FALLING_STATE,				// trang thai xung xuong
	HCSR04_COMPLETE_STATE					// trang thai da chuyen doi xong
}HCSR04_State;

HCSR04_State hcsr04_state = HCSR04_IDLE_STATE;

void HCSR04_Complete_Callback(float Distance);

void GPIO_EXTI_callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == HCSR04_ECHO_EXT_Pin)
	{
		switch(hcsr04_state)
		{
			case HCSR04_WAIT_EXT_RISING_STATE:
			{
				if(GPIO_ReadInputDataBit(GPIOA, HCSR04_ECHO_EXT_Pin) == 1)
				{
					TIM_SetCounter(TIM2, 0);
					TIM_Cmd(TIM2, ENABLE);
					hcsr04_state = HCSR04_WAIT_FALLING_STATE;
				}
				else
				{
					hcsr04_state = HCSR04_IDLE_STATE;
				}
				break;
			}
			case HCSR04_WAIT_FALLING_STATE:
			{
				if(GPIO_ReadInputDataBit(GPIOA, HCSR04_ECHO_EXT_Pin) == 0)
				{
					TIM_Cmd(TIM2, DISABLE);
					hcsr04_state = HCSR04_COMPLETE_STATE;
				}
				else 
				{
					hcsr04_state = HCSR04_IDLE_STATE;
				}
				break;
			}
			default:
				break;
			
		}
	}
}
void EXTI1_IRQHandler(void)
{
		if(EXTI_GetFlagStatus(EXTI_Line1) != RESET)
		{
			GPIO_EXTI_callback(GPIO_PinSource1);
			EXTI_ClearITPendingBit(EXTI_Line1);
		}
}


	// tao 1 xung 10us
void HCSR04_Start(void)
{
	GPIO_WriteBit(GPIOA, HCSR04_TRIG_Pin, 1);
	Delay_Ms(1);
	GPIO_WriteBit(GPIOA, HCSR04_TRIG_Pin, 0);
	hcsr04_state = HCSR04_WAIT_EXT_RISING_STATE;
}

float kc ;
void HCSR04_Complete_Callback(float Distance)
{
	//hien thi lcd
	//delay
	//tinh toan linh tinh
	kc = Distance;
}

//  s = v * t = v * T/2 = 340 * 100 / 10^6 * T / 2 =  0,017 * T 
void HCSR04_Handle(void)
{
	switch(hcsr04_state)
	{
		case HCSR04_COMPLETE_STATE:
		{
			float Distance = 0.17 * TIM_GetCounter(TIM2);
			HCSR04_Complete_Callback(Distance);
			
		}
		default:
			break;
		
	}
}
int main(void)
{
	SystemInit();
	SystickInit();
	GPIO_Config();
	NVIC_Config();
	EXTI_Config();
	TIM_Config();
	

	while(1)
	{
			static uint32_t t_read_hcsr;
		if(getTick() - t_read_hcsr >= 300)
		{
			HCSR04_Start();
			t_read_hcsr = getTick();
		}
		
		HCSR04_Handle();
	}
}