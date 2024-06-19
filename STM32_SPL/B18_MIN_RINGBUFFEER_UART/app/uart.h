#ifndef UART_H
#define UART_H
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "Ringbuff.h"

#define BUFF_UART_SIZE  		128


void GPIO_Config(void);
void UART_Config(void);
void NVIC_Config(void);
void UART_SendChar(char data, USART_TypeDef* USARTx);
void USART_SendString( uint8_t* str);
uint8_t USART_Receivechar(USART_TypeDef* USARTx);
void receive_rx(uint8_t data_rx);
uint16_t uart_available(void);
uint8_t uart_read(void);
void UART_Init(void);
#endif
