#include "systick.h"
#include "stm32f10x_gpio.h"
void gpioinit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioinit.GPIO_Pin = GPIO_Pin_13;
	gpioinit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioinit);
}
int main()
{
	SystickInit();
	gpioinit();
while(1)
	{
		//GPIO_SetBits(GPIOC, GPIO_Pin_13);
	static uint8_t time = 0;
	if(getTick() - time >= 1000)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			time = getTick();

		}

		}
}

