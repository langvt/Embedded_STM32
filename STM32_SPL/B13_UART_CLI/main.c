#include "main.h"

char BuffUart [BUFF_UART_SIZE ];
uint8_t IndexUart = 0;
uint8_t FlagUart = 0;
char stringArray [128];

int main(void)
{
	UART_Init();
	
	while(1)
	{
		UART_handle();
	}
}
