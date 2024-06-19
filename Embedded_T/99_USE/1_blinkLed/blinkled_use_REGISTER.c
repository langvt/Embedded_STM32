#include "stm32f10x.h"
#define HIGH 1
#define LOW 0


void delay(int time ){
	for(int i = 0; i < time; i ++);
}
	
void digitalWrite(uint16_t pin, uint8_t status){
	if(status == HIGH){
		GPIOC -> BSRR = (1 << pin); //GPIO_BSRR_BS13
	}
	else{
		GPIOC-> BSRR = (1 << (pin + 16)); //GPIO_BSRR_BR13
	}
}
int main (void){
	// bat xung clock cho GPIO
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//reset
	
	GPIOC -> CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
	GPIOC -> CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	GPIOC -> CRH &= ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15);
	
	// output
	
	GPIOC -> CRH |= GPIO_CRH_MODE13_0;
	GPIOC -> CRH |= GPIO_CRH_MODE14_0;
	GPIOC -> CRH |= GPIO_CRH_MODE15_0;
	
	while(1){
		digitalWrite(13,HIGH);
		delay(1000000);
		digitalWrite(13,LOW);
		delay(1000000);
		
		digitalWrite(14,HIGH);
		delay(1000000);
		digitalWrite(14,LOW);
		delay(100000);
		
		digitalWrite(15,HIGH);
		delay(1000000);
		digitalWrite(15,LOW);
		delay(1000000);
	}
}

