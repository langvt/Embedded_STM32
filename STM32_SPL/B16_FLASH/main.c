#include "main.h"


void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uint8_t Buff1 [ ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
uint8_t Buff2 [ 9];

uint32_t a = 123456543;
uint32_t b;

typedef struct
{
	uint8_t Name [30];
	uint8_t Version [10];
	uint8_t Id;
}FirmwareInfor;

FirmwareInfor FirmWare1 = 
{
	"LED",
	"1.1",
	0x12345
};

FirmwareInfor FirmRead;
int main (void)
{
	SystickInit();
	GPIO_Config();
	
	
//	flashErease(0x801FC00);
//	flashWriteArr(0x801FC00, Buff1, sizeof(Buff1));
//	flashReadArr(0x801FC00, Buff2, 9);
	
	/* int*/
	flashErease(0x801FC00);
	flashWriteArr(0x801FC00, (uint8_t *) &a, sizeof(a));
	flashReadArr(0x801FC00, (uint8_t *) &b, sizeof(b));
	
	/* Struct */
	flashErease(0x801FC00);
	flashWriteArr(0x801FC00, (uint8_t *) &FirmWare1, sizeof(FirmWare1));
	flashReadArr(0x801FC00, (uint8_t *) &FirmRead, sizeof(FirmRead));
	while(1)
	{
//		GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		Delay_Ms(1000);
//		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//		Delay_Ms(1000);
	}
}
