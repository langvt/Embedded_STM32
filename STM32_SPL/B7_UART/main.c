#include "systick.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

char buff [10];
uint8_t index = 0;
void GPIO_Config(void)
{
	//TX
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void UART_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Cau hinh cho nhom Uu Tien NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	// Set System Timer IRQ at higher priority
	NVIC_SetPriority(SysTick_IRQn, 0);
	NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
}


void SendChar(char data)
{
		USART1->DR = 0x00;
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		
		USART_SendData(USART1, data);
}
void USART_SendString( char* str){
	
	while(*str){
	// Cho bo truyen dem trong
		SendChar(*str);
		str++;
	}
}

uint8_t USART_Receivechar(USART_TypeDef* USARTx){
	// cho cho den khi co du lieu trong bo dem
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	
	return USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
		if(index < 10)
		{
			buff[index ++ ] = USART_Receivechar(USART1); 
		}
		else index = 0;
    }
}
int main(void)
{
	SystemInit();
	SystickInit();
	GPIO_Config();
	UART_Config();
	NVIC_Config();
	
	while(1)
	{
		 USART_SendString( "vhjgyjgyj \n");


		Delay_Ms(1000);
	}
}