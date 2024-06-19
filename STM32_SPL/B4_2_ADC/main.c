#include "systick.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

void GPIO_Config(void);
void ADC_Config(void);
uint16_t get_channel(uint32_t channel);

uint16_t adc_value; // có 12 bit do phan giai nen chon uint16_t
uint16_t adc_value1;

int main(void)
{
	SystemInit();
	SystickInit();
	GPIO_Config();
	ADC_Config();
	
	while(1)
	{
		adc_value = get_channel(ADC_Channel_0);
		adc_value1 = get_channel(ADC_Channel_1);
		Delay_Ms(10);
	}
}

void GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode =DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	
	// Select input channel for ADC1
	// ADC1 channel 0 (PA0)
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
}
uint16_t get_channel(uint32_t channel)
{
	uint16_t adc;
		ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		while (! ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		adc= ADC_GetConversionValue(ADC1);
		return adc;
}