#ifndef UART_H
#define UART_H
#include "main.h"

#define BUFF_UART_SIZE  		128


void GPIO_Config(void);
void UART_Config(void);
void NVIC_Config(void);
void UART_SendChar(char data, USART_TypeDef* USARTx);
void USART_SendString( char* str);
uint8_t USART_Receivechar(USART_TypeDef* USARTx);
void UART_Init(void);
void UART_handle(void);
#endif
