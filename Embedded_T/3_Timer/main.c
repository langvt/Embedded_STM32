#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

void Gpio_config(void);
void Timer_config(void);

void delay_ms(uint16_t time);

uint32_t  millis(void);

int main(void){
	
	Gpio_config();
	
	Timer_config();
	
	
	while(1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(1000);
		
	}
}


void Gpio_config(void){
		GPIO_InitTypeDef GPIO_InitStructure;

    // cau hinh gpio
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	}



// timer 1 ms xung duoc 100 dao dong thi ngat 1 lan

void Timer_config(void){
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//72Mhz / 720 = 100 KHz,    1ms = 100 xung 
	TIM_TimBaseStructure.TIM_Prescaler = (uint16_t) 719; // o nho dem tu 0
	TIM_TimBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseStructure.TIM_ClockDivision = 0;
	TIM_TimBaseStructure.TIM_Period = 999;// o nho dem tu 0
	
	TIM_TimeBaseInit(TIM2, &TIM_TimBaseStructure);
	TIM_Cmd(TIM2, ENABLE);
}

//counter khi duoc 1 ms thi dem them 1 lan 
void delay_ms(uint16_t time){
	 TIM_SetCounter(TIM2, 0);
   while(TIM_GetCounter(TIM2) < time);
}

uint32_t  millis(void);