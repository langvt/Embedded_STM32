#include "print_cli.h"
#include "stdarg.h"
#include <stdio.h>
#include "uart.h"

void vprint(const char *str, va_list args)
{
	extern char stringArray [128];
	vsprintf (stringArray, str, args);
	USART_SendString(stringArray);
}

void printCli(const char * str, ...)
{
	va_list args;
	va_start(args, str);
	vprint(str, args);
	va_end(args);
}
