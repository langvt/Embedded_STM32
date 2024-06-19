#include "uart.h"

#define RING_UART_LEN 				64
uint8_t Buff_Uart [RING_UART_LEN];
RingBuff ring_buff;

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

void UART_SendChar(char data, USART_TypeDef* USARTx)
{
		USART_SendData(USART1, data);
	
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}
void USART_SendString( uint8_t* str){
	
	
	for (uint8_t i = 0 ; i < strlen(str); i ++)
	{
		UART_SendChar(str[i], USART1);
	}
}
uint8_t USART_Receivechar(USART_TypeDef* USARTx){
	// cho cho den khi co du lieu trong bo dem
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	
	return USART_ReceiveData(USARTx);
}

void receive_rx(uint8_t data_rx)
{
	ring_buff_push(&ring_buff, data_rx);
	
}

uint16_t uart_available(void)
{
 		return ring_buff_available(&ring_buff);
}

uint8_t uart_read(void)
{
	uint8_t data;
	ring_buff_pop(&ring_buff, &data);
	return data;
}
void USART1_IRQHandler(void)
 {

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {
			uint8_t data_rx = (uint8_t)USART_ReceiveData(USART1);
			receive_rx(data_rx);
    }
}

void UART_Init(void)
{
	GPIO_Config();
	UART_Config();
	NVIC_Config();
	ring_buff_init(&ring_buff, Buff_Uart, RING_UART_LEN);
}
