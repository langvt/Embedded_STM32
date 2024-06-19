#ifndef I2C_H
#define I2C_H

/** Includes ---------------------------------------------------------------- */
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/** Defines ----------------------------------------------------------------- */
#define I2Cx					I2C1
#define I2C_RCC				RCC_APB1Periph_I2C1
#define I2C_GPIO			GPIOB
#define I2C_GPIO_RCC		RCC_APB2Periph_GPIOB
#define I2C_PIN_SDA		GPIO_Pin_7
#define I2C_PIN_SCL		GPIO_Pin_6
/** Public function prototypes ---------------------------------------------- */
void I2C_Config(void);
void I2C_Write_Reg(uint8_t Address, uint8_t Reg, uint8_t Data);
void I2C_Write_No_Reg(uint8_t Address, uint8_t Data);
void I2C_Read_Reg(uint8_t Address, uint8_t Reg, uint8_t *Data);
void I2C_Read_No_Reg(uint8_t Address, uint8_t *Data);

#endif
