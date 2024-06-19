#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define SDA_PIN					GPIO_Pin_7
#define SCL_PIN					GPIO_Pin_6
#define I2C_PORT				GPIOB


void I2C_Software_Init(void){

	 GPIO_InitTypeDef GPIO_InitStructure;
	
	// Cau hinh chan SCL va SDA
	
	GPIO_InitStructure.GPIO_Pin =  SDA_PIN | SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(I2C_PORT, &GPIO_InitStructure);

	// Ðat trang thai ban dau la HIGH cho SDA va SCL
	
	GPIO_SetBits(I2C_PORT, SDA_PIN);
	GPIO_SetBits(I2C_PORT, SCL_PIN);
		
}

// Dinh nghia cac ham co ban cua I2C

void I2C_StartBit(void){

	GPIO_SetBits(I2C_PORT, SDA_PIN);
	GPIO_SetBits(I2C_PORT, SCL_PIN);
	
	GPIO_ResetBits (I2C_PORT, SDA_PIN);
	GPIO_ResetBits (I2C_PORT, SCL_PIN);
	
}

void I2C_StopBit (void){
	
	GPIO_ResetBits (I2C_PORT, SDA_PIN);
	GPIO_ResetBits (I2C_PORT, SCL_PIN);

	GPIO_SetBits(I2C_PORT, SCL_PIN);
	GPIO_SetBits(I2C_PORT, SDA_PIN);

}

void I2C_SendOneByte(uint8_t byte){									// byte = 0b10010110				

		for(int i = 0; i < 8; i++){
				
			GPIO_ResetBits(I2C_PORT, SCL_PIN);						// SCL LOW
			
			if(byte & 0x80){															// 0x80 = 0b10000000					
					GPIO_SetBits(I2C_PORT, SDA_PIN);
			}
			else{
					GPIO_ResetBits(I2C_PORT, SDA_PIN);
			} 
			
					GPIO_SetBits(I2C_PORT, SCL_PIN);					// SCL HIGH de day cac bit di	
					
					byte<<= 1;
		}
		
		GPIO_ResetBits(I2C_PORT, SCL_PIN);							// SCL LOW de chuan bi HIGH gui bit moi								
}

uint8_t I2C_ReadOneByte(void){
		
	uint8_t byte = 0;
	
	// Dat SDA thanh input
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(I2C_PORT, &GPIO_InitStructure);
	
	for(int i = 0; i < 8; i++){
		
		byte <<=1;
		GPIO_SetBits(I2C_PORT, SCL_PIN);								// SCL HIGH;
		
		if(GPIO_ReadInputDataBit(I2C_PORT, SDA_PIN)){
				byte |=1;
		}
		GPIO_ResetBits(I2C_PORT, SCL_PIN);							//SCL LOW
		
		}

	// Dat SDA thanh output


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(I2C_PORT, &GPIO_InitStructure);
		
		return byte;
}

void I2C_ACK(void){
	
	GPIO_ResetBits(I2C_PORT, SCL_PIN); 									// SCL LOW
	GPIO_ResetBits(I2C_PORT, SDA_PIN);									// SDA LOW
	
	GPIO_SetBits(I2C_PORT, SCL_PIN); 										// SCL HIGH de co xung gui ACK
	GPIO_ResetBits(I2C_PORT, SCL_PIN);									// SCL LOW
}

void I2C_NACK(void){
	
	GPIO_ResetBits(I2C_PORT, SCL_PIN); 									// SCL LOW
	GPIO_SetBits(I2C_PORT, SDA_PIN);										// SDA HIGH
	
	GPIO_SetBits(I2C_PORT, SCL_PIN); 										// SCL HIGH de co xung gui ACK
	GPIO_ResetBits(I2C_PORT, SCL_PIN);									// SCL LOW
}

uint8_t I2C_ReadACK(void){
	
	uint8_t ack;
		// Dat SDA thanh input
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(I2C_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(I2C_PORT, SCL_PIN);											//SCL_PIN HIGH
	ack = GPIO_ReadInputDataBit(I2C_PORT, SDA_PIN);
	GPIO_ResetBits(I2C_PORT, SCL_PIN); 										// SCL LOW
	
	return ack;                                 // return 0 = ACK , 1 = NACK
}

void I2C_SendBytes(uint8_t *data, uint32_t len){
		for(int i = 0; i < len; i++){
			
			I2C_SendOneByte(data[i]);
			if(I2C_ReadACK()){
					
				// xu ly loi
				break;
			}
	  	}

}


void I2C_ReadBytes(uint8_t *buffer, uint32_t len){
		for(int i = 0; i < len; i++){
				
			buffer[i] = I2C_ReadOneByte();
			
			if(buffer[i] != '\0'){
				I2C_ACK();
			}
			else{
				I2C_NACK();
			}
		}
	
}

int main(void){

	return 0;	
}