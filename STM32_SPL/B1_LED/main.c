// blink led: 1 led with 1hz and 1 led with 2hz


#include "systick.h"
#include "stm32f10x_gpio.h"

void GPIO_Config(void);
uint32_t Time_Curent = 0;
uint32_t Time_Curent2 = 0;

int main(void)
{
	SystickInit();
	GPIO_Config();
	while(1)
	{
	//GPIO_SetBits(GPIOC, GPIO_Pin_13);
	//Delay_Ms(1000);
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	//Delay_Ms(1000);
		
		if(getTick() - Time_Curent >= 500)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Time_Curent = getTick();
		}
		
		if(getTick() - Time_Curent2 >= 100)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_14);
			Delay_Ms(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_14);
			Time_Curent2 = getTick();
		}
	}
}
void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	// GPIO_Pin_13 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13 |  GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
