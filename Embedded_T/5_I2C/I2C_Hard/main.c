#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#define SCL_PIN											GPIO_Pin_6
#define SDA_PIN											GPIO_Pin_7

#define PORT_I2C										GPIOB

#define DEVICE_I2C_ADDRESS					0x50 // dia chi cua thiet bi

void I2C_HW_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef	 I2C_InitStructure;

	// Bat clock cho I2C1 va PORT I2C
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// Cau hinh chan SCL va SDA
	GPIO_InitStructure.GPIO_Pin = SCL_PIN | SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_I2C, &GPIO_InitStructure);
	
	// Config I2C
	
	I2C_InitStructure.I2C_ClockSpeed = 100; 						//Toc do truyen			
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 	// Chu ki xung: 2_toc do la 100khz, 16_9_ toc do la 400khz
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;						// Dia chi: MASTER = 0x00, SLAVE = address define 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	// Apply config
	I2C_Init(I2C1, &I2C_InitStructure);
	
		// Peripher enable
	I2C_Cmd(I2C1, ENABLE);
}


void I2C_Write(uint8_t data){
	
	I2C_GenerateSTART(I2C1, ENABLE);
	
		// Wait for start to complete
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		
		// Gui dia chi cho slave
		I2C_Send7bitAddress(I2C1, DEVICE_I2C_ADDRESS, I2C_Direction_Transmitter);
		
		// wait for data tranfer complete
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		
		// Gui du lieu
		I2C_SendData(I2C1, data);
	
		// wait for data tranfer complete
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

		// Ket thuc truyen
		I2C_GenerateSTOP(I2C1,ENABLE);

}


uint8_t I2C_Read(){
	uint8_t data;
	
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for start to complete	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	
	// Gui dia chi cho slave
	I2C_Send7bitAddress(I2C1, DEVICE_I2C_ADDRESS, I2C_Direction_Receiver);
	
	// wait for data tranfer complete
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	// store data
	data = I2C_ReceiveData(I2C1);
	
	// Gui khong xac nhan dung truyen
	I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Current);
	
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return data;
}


int main(){
	
	uint8_t receive_data = 0;
	
	I2C_HW_Init();
	
	I2C_Write(0x55);
	
	receive_data = I2C_Read();
	
	//while(){

	return 0;
}