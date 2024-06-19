#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "misc.h"

#define SCL_PIN											GPIO_Pin_6
#define SDA_PIN											GPIO_Pin_7

#define PORT_I2C										GPIOB

// Config GPIO
 void GPIO_Config(void){
 	GPIO_InitTypeDef GPIO_InitStructure;

	// Bat clock cho I2C1 va PORT I2C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// Cau hinh chan SCL va SDA
	GPIO_InitStructure.GPIO_Pin = SCL_PIN | SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_I2C, &GPIO_InitStructure);
 }
 
 // Config I2C
 void I2C_Config(void){
	 
	 I2C_InitTypeDef	 I2C_InitStructure;
	 
	 // Bat clock cho I2C1 
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
 
	 // Config I2C
	I2C_InitStructure.I2C_ClockSpeed = 100; 						//Toc do truyen			
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 	// Chu ki xung: 2_toc do la 100khz, 16_9_ toc do la 400khz
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;						// Dia chi: MASTER = 0x00, SLAVE = address define 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	// I2C Peripher enable
	I2C_Cmd(I2C1, ENABLE);
	 
	 // Apply I2C config after enableing it
	I2C_Init(I2C1, &I2C_InitStructure);
	 	 
 }
 
 
 // Config NVIC
 void NVIC_Config(void){
 
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 
	 NVIC_Init(&NVIC_InitStructure);
 }
 
 void I2C1_EV_IRQHandler(void){
	if(I2C_GetITStatus(I2C1, I2C_IT_RXNE ) != RESET) // khi nao la receiver thi ngat
	{
		// xu ly ngat 
		// xoa co ngat
		I2C_ClearITPendingBit(I2C1, I2C_IT_RXNE);
	}
}
 
int main (){

	GPIO_Config();
	I2C_Config();
	NVIC_Config();
	
	while(1){
	}
	
	return 0;
}
 