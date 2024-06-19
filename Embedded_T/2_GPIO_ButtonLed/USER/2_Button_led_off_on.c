#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define BTN1									GPIO_Pin_13
#define BTN2									GPIO_Pin_14
#define BTN3									GPIO_Pin_14

#define LED1									GPIO_Pin_0
#define LED2									GPIO_Pin_1
#define LED3									GPIO_Pin_2


#define PORT_BTN						GPIOC
#define PORT_BTN_CLOCK			RCC_APB2Periph_GPIOC

#define PORT_LED						GPIOA
#define PORT_LED_CLOCK 			RCC_APB2Periph_GPIOA


void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	GPIO_SetBits(GPIOA, LED1 | LED2 | LED3);
	
	while(1){
		 if(GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0 ){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0);
			 
				uint16_t ledState = GPIO_ReadOutputData(PORT_LED) ^ (LED1 | LED2 | LED3);
				GPIO_Write(PORT_LED, ledState);
		}
	}
}

void delay (int time){
	int i;
	for(i = 0; i < time; i++);
}


void GPIO_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(PORT_BTN_CLOCK | PORT_LED_CLOCK, ENABLE);
	
	
    GPIO_InitTypeDef GPIO_InitStructure; 
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  BTN1 |BTN2 | BTN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(PORT_BTN, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
		GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);

}
