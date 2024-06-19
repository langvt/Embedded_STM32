#include "ADC.h"

/*
* Function: ADC_Config
* Description: Configures the Analog-to-Digital Converter (ADC) peripheral and its associated GPIO pin.
* Input: None
* Output: None
* 
* This function initializes the GPIO pin connected to the ADC input and configures the ADC module for
* single-channel, single-conversion mode with a specified sample time. It enables the ADC peripheral.
*/
void ADC_Config(void)
{
	/*config adc gpio*/
	RCC_APB2PeriphClockCmd(ADC_GPIO_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(ADC_GPIO, &GPIO_InitStructure);
	
	/* config adc*/
	RCC_APB2PeriphClockCmd(ADC_RCC, ENABLE);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_RegularChannelConfig(ADCx, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
	
	ADC_Init(ADCx, &ADC_InitStructure);
	ADC_Cmd(ADCx, ENABLE);
}

