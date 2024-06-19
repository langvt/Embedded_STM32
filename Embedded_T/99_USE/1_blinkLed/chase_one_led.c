#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

uint16_t sangdan[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
uint16_t tatdan[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	
	while(1){
		// GPIOA 7 6 5 4 3 2 1 0
		// 1000 0000, 0100 0000, 0010 0000, 0001 0000, 0000 1000, 0000 0100, 0000 0010, 0000 0001      
		int i ;
		for(i = 0; i <8; i++){
			GPIO_Write(GPIOA, sangdan[i]);
			delay(1000000);
		}
		
		for(i = 7; i >= 0; i--){
			GPIO_Write(GPIOA, tatdan[i]);
			delay(1000000);
	}
	
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
