#ifndef UTILITIES_H
#define UTILITIES_H
/** Includes ---------------------------------------------------------------- */
#include "main.h"
//#include "servo.h"
//#include "TIM.h"

/*
* Enum: ADC_State
* Description: Enumeration representing the states of the ADC utility.
*   - ADC_IDLE: Represents the idle state of the ADC utility.
*   - ADC_CONVERT: Represents the state during ADC conversion.
* 
* This enum defines the possible states of the ADC utility, which are used to control the process
* of ADC conversion.
*/
typedef enum
{
	ADC_IDLE,
	ADC_CONVERT
}ADC_State;

/** Public function prototypes ---------------------------------------------- */
void ADC_ConversionHandle(void);
void ADC_Utilities_Init(void);
void ADC_UtilitiesHandle(void);
#endif
