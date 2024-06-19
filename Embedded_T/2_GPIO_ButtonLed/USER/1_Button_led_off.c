#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	while(1){
		 if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
				
					GPIO_SetBits(GPIOC, GPIO_Pin_13);
				}
				else{
					GPIO_ResetBits(GPIOC, GPIO_Pin_13);
				}
			}
	}	

void GPIO_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}
