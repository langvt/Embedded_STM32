#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void  ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_InitTypeDef ADC_initStructure;
	ADC_initStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_initStructure.ADC_NbrOfChannel = 1;
	ADC_initStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_initStructure.ADC_ScanConvMode = DISABLE;
	ADC_initStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_initStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_Init(ADC1, &ADC_initStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t val =0;
int main(void)
{
	GPIO_Config();
	ADC_Config();
	while(1)
	{
		val = ADC_GetConversionValue(ADC1);
	}
}