#include  "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "misc.h"


#define SS_PIN                  					GPIO_Pin_4
#define SCK_PIN									GPIO_Pin_5
#define MISO_PIN								GPIO_Pin_6
#define MOSI_PIN								GPIO_Pin_7

#define PORT_SPI								GPIOA


//  Config GPIO
void GPIO_Config(void){
	
	// turn on clock GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	// config SPI1 pins: SCK, MISO and MOSI
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// config SCK and MOSI pins as Alternate Function Push Pull
	GPIO_InitStructure.GPIO_Pin = SCK_PIN | MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//config MISO pin as Input Floating 
	GPIO_InitStructure.GPIO_Pin = MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// Config SPI
void SPI_Config(void){
	
	SPI_InitTypeDef SPI_InitStructure;
	
	// SPI_MASTER config
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
}

// Config NVIC
void NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
}

void SPI1_IRQHandler(void){
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) != RESET)
	{
		// thuc hien lenh
		// clear flag
		SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
	}
}


int main(){
	GPIO_Config();
	SPI_Config();
	NVIC_Config();
	
	while(1){
	
	}
	return 0;
}
