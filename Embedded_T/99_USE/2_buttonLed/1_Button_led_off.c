#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define BTN1									GPIO_Pin_0
#define BTN2									GPIO_Pin_1
#define BTN3									GPIO_Pin_2

#define PORT_BTN						GPIOA
#define PORT_BTN_CLOCK			RCC_APB2Periph_GPIOA


void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	
	while(1){
		 if(GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 1){
				
					GPIO_SetBits(GPIOC, GPIO_Pin_13);
					GPIO_SetBits(GPIOC, GPIO_Pin_14);
					GPIO_SetBits(GPIOC, GPIO_Pin_15);
				}
				else{
					GPIO_ResetBits(GPIOC, GPIO_Pin_13);
					GPIO_ResetBits(GPIOC, GPIO_Pin_14);
					GPIO_ResetBits(GPIOC, GPIO_Pin_15);
				}
			}
		//if(GPIO_ReadInputDataBit( PORT_BTN, BTN2) == 1){
		//GPIO_SetBits(GPIOC, GPIO_Pin_14);
		//}
		//else{
		//GPIO_ResetBits(GPIOC, GPIO_Pin_14);
		//}
		
		//if(GPIO_ReadInputDataBit( PORT_BTN, BTN3) == 1){
		//GPIO_SetBits(GPIOC, GPIO_Pin_15);
		//}
		//else{
		//GPIO_ResetBits(GPIOC, GPIO_Pin_15);
		//}
	}	

void delay (int time){
	int i;
	for(i = 0; i < time; i++);
}


void GPIO_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(PORT_BTN_CLOCK|RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  BTN1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(PORT_BTN, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}
