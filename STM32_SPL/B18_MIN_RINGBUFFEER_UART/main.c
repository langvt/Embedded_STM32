#include "uart.h"

uint8_t data_rx;

int main(void)
{
	UART_Init();
	
	while(1)
	{
		if(uart_available() > 0)
		{
			 data_rx = uart_read();
			
			USART_SendString(&data_rx );
		}
	}
}