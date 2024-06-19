#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


// dinh nghia cac che do spi

typedef enum {
	SPI_Mode0 = 0,						// CPOL = 0, CPHA = 0
	SPI_Mode1,								// CPOL = 0, CPHA = 1
	SPI_Mode2,								// CPOL = 1, CPHA = 0
	SPI_Mode3,								// CPOL = 1, CPHA = 1
}SPI_Mode;


typedef struct{
	GPIO_TypeDef* port;
	uint16_t sck_pin;
	uint16_t mosi_pin;
	uint16_t miso_pin;
	SPI_Mode mode;
	uint32_t speed_Khz;
}SPI_Config;

// ham delay micro dung de xung clock 

void delayUs(uint32_t us){ 		//72,000,000, 100hz/100ms
	us *=72;
	while(us--);
}


// khoi tao cac chan spi

void SPI_Ini (SPI_Config *spiConfig){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//bat clock cho GPIO
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// cau hinh sck va mosi out put che do push_pull
	
	GPIO_InitStructure.GPIO_Pin = spiConfig ->sck_pin | spiConfig -> mosi_pin ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(spiConfig ->port , &GPIO_InitStructure);
	
	// cau hinh miso la input
	
	GPIO_InitStructure.GPIO_Pin = spiConfig -> miso_pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init (spiConfig ->port , &GPIO_InitStructure);
}

// truyen mot byte nhan 1 byte

