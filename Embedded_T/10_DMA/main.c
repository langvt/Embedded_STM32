#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

#define SPI1_NSS                  				GPIO_Pin_4
#define SPI1_SCK								GPIO_Pin_5
#define SPI1_MISO								GPIO_Pin_6
#define SPI1_MOSI								GPIO_Pin_7

#define PORT_SPI								GPIOA

uint8_t buffer [10];
void RCC_Config(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}


void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI | SPI1_MISO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(PORT_SPI, &GPIO_InitStructure);
	
}
void SPI_Config(void){
	
	SPI_InitTypeDef SPI_InitStructure;
	
	// Cau hinh cho SPI
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;											
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;									 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;											 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge ;											
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;								
	SPI_InitStructure.SPI_CRCPolynomial = 7 ;
	
	// system clock 64 MHz
	// Precaler 16
	// 64/16 = 4MHz     1s truyen duoc 4trieu bit
	
	// Apply config after enable
	SPI_Init(SPI1, &SPI_InitStructure);
	
	// Peripher enable
	SPI_Cmd(SPI1, ENABLE);
}
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitrStructure;
	DMA_InitrStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1 ->DR;
	DMA_InitrStructure.DMA_MemoryBaseAddr = (uint32_t)buffer[10];
	 DMA_InitrStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitrStructure.DMA_BufferSize =  10; 
	DMA_InitrStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitrStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitrStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte;
	DMA_InitrStructure.DMA_MemoryDataSize=  DMA_MemoryDataSize_Byte;
	DMA_InitrStructure.DMA_Mode = DMA_Mode_Normal;
	 DMA_InitrStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitrStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel2, &DMA_InitrStructure);

}

 
int main ()
{
		RCC_Config();
		SPI_Config();
		GPIO_Config();
		DMA_Config();
		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
		while(1)
			{
			
			}
	
	return 0;
}