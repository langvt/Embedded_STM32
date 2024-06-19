#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "systick.h"
#include "I2C.h"

#define LCD_ADDR			0x4E

void LCD_I2C_WriteCMD(uint8_t Data);
void LCD_I2C_WriteData(uint8_t Data);
void LCD_I2C_Init(void);
void LCD_I2C_Clear(void);
void LCD_I2C_Location(uint8_t Rows, uint8_t Lows);
void LCD_I2C_Write_String(char *string);
#endif