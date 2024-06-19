#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <setjmp.h>

#define LED1												GPIO_Pin_0
#define LED2												GPIO_Pin_1
#define LED3												GPIO_Pin_2
#define LED4												GPIO_Pin_3
#define LED5												GPIO_Pin_4

#define BTN1												GPIO_Pin_13
#define BTN2												GPIO_Pin_14
#define BTN3												GPIO_Pin_15

#define PORT_LED										GPIOA
#define PORT_BTN										GPIOC

#define PORT_LED_CLOCK							RCC_APB2Periph_GPIOA
#define PORT_BTN_CLOCK							RCC_APB2Periph_GPIOC

void GPIO_config(void);
void delay_n(int time);
void delay_10ms(int time);

void offLed(void);
void blinkLed(int n);
void chaseLed(int n);

jmp_buf buf;

int main(void){
	
	GPIO_config();
	GPIO_SetBits(PORT_LED, LED1 | LED2 | LED3 | LED4 | LED5); 
	
	while(1){
	 int i = setjmp(buf);
	
        if (GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0) {
            while (GPIO_ReadInputDataBit(PORT_BTN, BTN1) == 0);
            offLed();
        }
        else if (GPIO_ReadInputDataBit(PORT_BTN, BTN2) == 0) {
            while (GPIO_ReadInputDataBit(PORT_BTN, BTN2) == 0);
            blinkLed(10);
        }
        else if (GPIO_ReadInputDataBit(PORT_BTN, BTN3) == 0) {
            while (GPIO_ReadInputDataBit(PORT_BTN, BTN3) == 0);
            chaseLed(7);
        }
    }
	}

void delay_n(int n) {
    uint32_t i;
    for (i = 0; i < n; i++);
}


// delay 10ms chia nho chuong kiem tra nut nhan
void delay_10ms(int n){
	uint32_t i;
	for(i = 0; i < n; i++){
		if(GPIO_ReadInputDataBit(PORT_BTN, BTN1) ==0){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN1) ==0);
			offLed();
		}
		if(GPIO_ReadInputDataBit(PORT_BTN, BTN2) ==0){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN2) ==0);
			blinkLed(10);
		}
		
		if(GPIO_ReadInputDataBit(PORT_BTN, BTN3) ==0){
			while(GPIO_ReadInputDataBit(PORT_BTN, BTN3) ==0);
			chaseLed(7);
		}
		
	}
	delay_n(10);
}


void GPIO_config(void) {
    // turn on clock for button and led
    RCC_APB2PeriphClockCmd(PORT_BTN_CLOCK | PORT_LED_CLOCK, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // config button 1, 2, 3
    GPIO_InitStructure.GPIO_Pin = BTN1 | BTN2 | BTN3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(PORT_BTN, &GPIO_InitStructure);

		
    // config led 1, 2, 3
    GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4 | LED5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);
}

void blinkLed(int n) {
	uint32_t i;
	for( i = 0 ; i < n; i++){
		GPIO_SetBits(PORT_LED, LED1);
		GPIO_SetBits(PORT_LED, LED2);
		GPIO_SetBits(PORT_LED, LED3);
		GPIO_SetBits(PORT_LED, LED4);
		GPIO_SetBits(PORT_LED, LED5);
		delay_10ms(100000);
		
		GPIO_ResetBits(PORT_LED, LED1);
		GPIO_ResetBits(PORT_LED, LED2);
		GPIO_ResetBits(PORT_LED, LED3);
		GPIO_ResetBits(PORT_LED, LED4);
		GPIO_ResetBits(PORT_LED, LED5);
		delay_10ms(100000);
	}
	longjmp(buf, 1);
}

void chaseLed(int n) {
    uint32_t i;
	for( i = 0; i < n; i++){
		GPIO_SetBits(PORT_LED, LED1);
		delay_10ms(100000);
		GPIO_ResetBits(PORT_LED, LED1);
		delay_10ms(10000);
		
		GPIO_SetBits(PORT_LED, LED2);
		delay_10ms(100000);
		GPIO_ResetBits(PORT_LED, LED2);
		delay_10ms(10000);
		
		GPIO_SetBits(PORT_LED, LED3);
		delay_10ms(100000);
		GPIO_ResetBits(PORT_LED, LED3);
		delay_10ms(100000);
		
		GPIO_SetBits(PORT_LED, LED4);
		delay_10ms(100000);
		GPIO_ResetBits(PORT_LED, LED4);
		delay_10ms(10000);
		
		GPIO_SetBits(PORT_LED, LED5);
		delay_10ms(100000);
		GPIO_ResetBits(PORT_LED, LED5);
		delay_10ms(10000);
	}
	longjmp(buf, 1);
}

void offLed(){
	uint16_t ledState = GPIO_ReadOutputData(PORT_LED) ^(LED1 | LED2 | LED3 | LED4 | LED5);
	GPIO_Write(PORT_LED, ledState);
	longjmp(buf, 1);
}
