#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"



volatile uint32_t msTicks = 0;
// GPIO confiig

void GPIO_Config(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// NVIC config

void NVIC_Config(void){

	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_BASE;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// TIM config

void TIM_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIMBaseStructure;
	TIMBaseStructure.TIM_Prescaler = 64 -1;											// 64 000 000 hz        bo dao dong -> 1 000 000 hz/ 1s       -> 1000hz / 1ms
	TIMBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIMBaseStructure.TIM_Period = 1000 -1;
	TIMBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM2, TIM_IT_Update) != RESET){
		
		msTicks ++;
		
		//xoa co ngat
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		}
	}



void Delay(uint32_t ms){
	uint32_t curTicks = msTicks;
	while( msTicks - curTicks  < ms);		
}

uint32_t millis(void){
    return msTicks;
}


int main (){

	GPIO_Config();
	NVIC_Config();
	TIM_Config();
	
	while(1){

	}

	return 0;
}
