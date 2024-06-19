#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"


#define TX_PIN							GPIO_Pin_9
#define RX_PIN							GPIO_Pin_10
#define USART_PORT					GPIOA

void USART_HW_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	// Bat clock cho USART va GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// cau hinh chan USART TX(PA.09) RX (PA.10)
	GPIO_InitStructure.GPIO_Pin = TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_PORT, &GPIO_InitStructure);
	
	// Khoi tao USART
	USART_InitStructure.USART_BaudRate = 9600;									// Toc do truyen bits
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// Bit lam viec
	USART_InitStructure.USART_StopBits  = USART_StopBits_1;			// bit stop
	USART_InitStructure.USART_Parity = USART_Parity_No;					// bit chan le
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// che do lam viec: RX, TX
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	// 

	// Apply config
	USART_Init(USART1, &USART_InitStructure);
	
	// Peripher enable
	USART_Cmd(USART1, ENABLE);
	
}

void USART_SendString(USART_TypeDef* USARTx, char* str){
	
	while(*str){
		
	// Cho bo truyen dem trong
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		
		USART_SendData(USARTx, *str);
		str++;
		
	}
}

char USART_Receivechar(USART_TypeDef* USARTx){
	
	// cho cho den khi co du lieu trong bo dem
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET){
	
		return (char)USART_ReceiveData(USARTx);
	}
}

void USART_ReceiveString(USART_TypeDef* USARTx, char* buffer, uint32_t size){

}

void USART_TransmitString(USART_TypeDef* USARTx, char* buffer, uint32_t size){

}

int main(){

}