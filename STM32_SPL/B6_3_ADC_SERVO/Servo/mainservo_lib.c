#include "systick.h"
#include "servo.h"
#include "stm32f10x_adc.h"


uint16_t adc; 
uint8_t goc;
void GPIO_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//pin ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//pin PWM
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
}

// create fPWM= 50hz, ARR = 20000 (), PSC = 72
void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TIMBaseInitStructure;
	TIM_TIMBaseInitStructure.TIM_Prescaler =  72- 1;
	TIM_TIMBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TIMBaseInitStructure.TIM_Period = 20000 - 1;
	TIM_TIMBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TIMBaseInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_Config(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	TIM_OCInitStructure.TIM_OutputState =ENABLE;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
}

void PWM_setDuty(TIM_TypeDef *TIMx, uint32_t Channel, uint16_t duty)
{
    uint16_t Period = TIMx->ARR + 1;
    uint32_t Pulse = (duty * Period) / 100;

    switch (Channel)
    {
    case TIM_Channel_1:
        TIMx->CCR1 = Pulse;
        break;
    case TIM_Channel_2:
        TIMx->CCR2 = Pulse;
        break;
    case TIM_Channel_3:
        TIMx->CCR3 = Pulse;
        break;
    case TIM_Channel_4:
        TIMx->CCR4 = Pulse;
        break;
    default:
        break;
    }
}
		
int main(void)
{
	SystickInit();
	GPIO_Config();
	PWM_Config();
	TIM_Config();
	ADC_Config();
	
	Servo sv1;
	servo_Init(&sv1, TIM2, TIM_Channel_1);

	while(1)
	{
//		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//		while (! ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
//		adc= ADC_GetConversionValue(ADC1);
//		goc = adc * 180 / 4095;
		//servo_Write(&sv1, goc);
		servo_Write(&sv1, 0);
		Delay_Ms(1000);
		servo_Write(&sv1, 180);
		Delay_Ms(1000);
	}
}
