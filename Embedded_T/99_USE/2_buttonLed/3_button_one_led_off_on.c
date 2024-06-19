#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define BTN1									GPIO_Pin_0
#define BTN2									GPIO_Pin_1
#define BTN3									GPIO_Pin_2
#define BTN4									GPIO_Pin_3

#define LED1									GPIO_Pin_13
#define LED2									GPIO_Pin_14
#define LED3									GPIO_Pin_15


#define PORT_BTN						GPIOA
#define PORT_BTN_CLOCK			RCC_APB2Periph_GPIOA

#define PORT_LED						GPIOC
#define PORT_LED_CLOCK 			RCC_APB2Periph_GPIOC


void GPIO_config(void);
void delay (int time);

int main(void){
	
	GPIO_config();
	GPIO_SetBits(GPIOC, LED1 | LED2 | LED3);
	uint16_t led1State;
	uint16_t led2State;
	uint16_t led3State;
	
	while(1){
		 if(GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0 ){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0);
				//led1State = GPIO_ReadOutputDataBit(PORT_LED, LED1) ^ (LED1);
				led1State = (BitAction) (1^ GPIO_ReadOutputDataBit(PORT_LED, LED1));
				GPIO_WriteBit(PORT_LED, LED1, led1State);
		}
		 
		 if(GPIO_ReadInputDataBit(PORT_BTN, BTN2) == 0 ){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN2) == 0);
				//led2State = GPIO_ReadOutputDataBit(PORT_LED, LED2) ^ (LED2);
				led2State = (BitAction) (1^ GPIO_ReadOutputDataBit(PORT_LED, LED2));
				GPIO_WriteBit(PORT_LED, LED2, led2State);
		}
		 
			if(GPIO_ReadInputDataBit(PORT_BTN, BTN3) == 0 ){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN3) == 0);
				//led2State = GPIO_ReadOutputDataBit(PORT_LED, LED2) ^ (LED2);
				led3State = (BitAction) (1^ GPIO_ReadOutputDataBit(PORT_LED, LED3));
				GPIO_WriteBit(PORT_LED, LED3, led3State);
		}
			
			if(GPIO_ReadInputDataBit(PORT_BTN, BTN4) == 0 ){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN4) == 0);
				led3State = GPIO_ReadOutputData(PORT_LED) ^ (LED1 | LED2 | LED3);
				GPIO_Write(PORT_LED, led3State);
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
	GPIO_InitStructure.GPIO_Pin =  BTN1 |BTN2 | BTN3 |BTN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(PORT_BTN, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
		GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);

}
