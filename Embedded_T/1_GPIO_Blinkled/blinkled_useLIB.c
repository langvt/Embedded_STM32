#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	
	while(1){
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
		deưlay(1000000);
		
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);
		delay(1000000);
	}
	
}	

void delay (int time){
	int i;
	for(i = 0; i < time; i++);
}

void GPIO_config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    // GPIO_Pin_13 14 15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
