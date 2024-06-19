#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	
	while(1){
		// GPIOA 0 1 2 3  4 5 6 7 
		GPIO_Write(GPIOA, 0x55); // 1010 1010 = 5 5, ON
		delay(2000000);
		GPIO_Write(GPIOA, 0xAA); // 0101 0101 = 10 10 = A A , OFF
		delay(2000000);
	}
	
}	

void delay (int time){
	int i;
	for(i = 0; i < time; i++);
}

void GPIO_config(void) {
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    // GPIO_Pin_13 14 15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
