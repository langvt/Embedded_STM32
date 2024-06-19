#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

uint16_t sangdan[8] = {0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF};
uint16_t tatdan[8] = {0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F};
void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	
	while(1){
		// GPIOA 7 6 5 4 3 2 1 0
		// 0000 0001, 0000 0011, 0000 0111, 0000 1111, 0001 1111, 0011 1111, 0111 1111, 1111 1111
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
