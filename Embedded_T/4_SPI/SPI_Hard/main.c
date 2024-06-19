#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

#define SS_PIN                  				GPIO_Pin_4
#define SCK_PIN									GPIO_Pin_5
#define MISO_PIN								GPIO_Pin_6
#define MOSI_PIN								GPIO_Pin_7

#define PORT_SPI								GPIOA

void SPI_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// Bat clock cho GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// Cau hinh SCK, MISO va MOSI la output che do pushpull
	GPIO_InitStructure.GPIO_Pin = SCK_PIN | MISO_PIN | MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(PORT_SPI, &GPIO_InitStructure);
	
	// cau hinh chan MISO la input
	GPIO_InitStructure.GPIO_Pin = MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SPI, &GPIO_InitStructure);
	
	// Bat clock cho SPI1
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	// Cau hinh cho SPI
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 		// function 2lines
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							// MASTER or SLAVER
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						// DATA FRAME 8 or 16 bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;								// Xung HIGH or LOW
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge ;							// Xung 1Edge or 2Edge push data
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								// NSS_Soft with master, NSS_hard with slave
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		// he so chia: APB2 = 72MHz max, APB1 = 36MHz max
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						// MSB or LSB
	SPI_InitStructure.SPI_CRCPolynomial = 7 ;								// CRC-7-16-32
	
	// system clock 64 MHz
	// Precaler 16
	// 64/16 = 4MHz     1s truyen duoc 4trieu bit
	
	// Apply config after enable
	SPI_Init(SPI1, &SPI_InitStructure);
	
	// Peripher enable
	SPI_Cmd(SPI1, ENABLE);
}

void SPI_SelectSlave() {
  // Dat chan SS (Slave Select) xuong muc thap
  GPIO_ResetBits(PORT_SPI, SS_PIN);
}

void SPI_DeselectSlave() {
  // Dat chan SS (Slave Select) len muc cao
  GPIO_SetBits(PORT_SPI, SS_PIN);
}

void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data){
	
	// Gui du lieu
	SPI_I2S_SendData(SPIx, Data);
	
	// ham kiem tra thanh ghi da trong 16 o hay chua
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	
		// if (timeout == 0) break;
}
SPI_TypeDef* SPI_TypeDefPtr;
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx){
	
	// Cho den khi co du lieu trong thanh ghi(bo nho dem nhan)
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	// timeout thoat khoi vong while
	
	return SPI_I2S_ReceiveData(SPIx);
}

void SPI_SendAndReceiveData(SPI_TypeDef* SPIx, uint16_t dataToSend, uint16_t *dataToReceived){


	// Gui du lieu
	SPI_I2S_SendData(SPIx, dataToSend);
	
	// ham kiem tra thanh ghi da trong 16 o hay chua
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	
	// Cho den khi co du lieu trong thanh ghi(bo nho dem nhan)
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	// timeout thoat khoi vong while
	
	*dataToReceived = SPI_I2S_ReceiveData(SPIx);
	
}

int main (){
		uint16_t dataToSend =  0x1234;
		uint16_t ReceiveData;
		SPI_Config();
		
		SPI_SendAndReceiveData(SPI1, dataToSend, &ReceiveData);
	
	return 0;
}