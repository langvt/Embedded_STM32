#include "ADC_Utilities.h"

extern Servo sv1;
ADC_State AdcState = ADC_IDLE;


/*
* Function: ADC_ConversionHandle
* Description: Handles the conversion process of the ADC and controls the servo motor angle accordingly.
* Input: None
* Output: None
* 
* This function initiates the ADC conversion process and waits for the conversion to complete. Once the conversion
* is finished, it calculates the angle based on the ADC value and adjusts the servo motor position accordingly.
*/
void ADC_ConversionHandle(void)
{
	extern uint16_t Adc;
	extern uint8_t Angle;
//	uint16_t Adc; uint8_t Angle ;
	switch(AdcState)
	{
		case ADC_IDLE:
			ADC_SoftwareStartConvCmd(ADCx, ENABLE);
			AdcState = ADC_CONVERT;
			break;
		case ADC_CONVERT:
		{
			if (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC))
			{
				Adc = ADC_GetConversionValue(ADCx);
				Angle = Adc * 180 / 4095;
				servo_Write(&sv1, Angle);
				AdcState = ADC_IDLE;
			}
			
		}
			break;

		default: break;
	}
}

/*
* Function: ADC_Utilities_Init
* Description: Initializes the ADC utility by configuring the ADC.
* Input: None
* Output: None
* 
* This function initializes the ADC utility by calling the ADC_Config function to configure the ADC for usage.
*/
void ADC_Utilities_Init(void)
{
	ADC_Config();

}

/*
* Function: ADC_UtilitiesHandle
* Description: Handles the ADC utility process by invoking the ADC conversion handler.
* Input: None
* Output: None
* 
* This function manages the ADC utility process by calling the ADC_ConversionHandle function, which controls
* the conversion process of the ADC and servo motor angle adjustment.
*/
void ADC_UtilitiesHandle(void)
{
		ADC_ConversionHandle();
}
