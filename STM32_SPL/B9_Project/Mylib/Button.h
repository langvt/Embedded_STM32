#ifndef BUTTON_H
#define BUTTON_H

#include "systick.h"
#include "stm32f10x_gpio.h"
#include "main.h"

/*
*  structure of button
*/
typedef struct
{
uint8_t btn_current; 					// to show currently status of the button
uint8_t btn_filter ; 					// filter variable to help debounce the button
uint8_t btn_last;						// to show last status of the button 
uint8_t is_debouncing;				// to show flag button is in the debouncing process
uint32_t tim_deboune;				// to show debouncing time
uint32_t time_start_press; 			// to show time for short press detection
uint8_t is_press_timeout; 			// to show time for long press detection
GPIO_TypeDef *GPIOx;				// GPIO port with the button
uint16_t GPIO_Pin;					// GPIO pin with the button
uint32_t time_start_press_repeat; // to show time for press-and-hold repeat detection
uint8_t flag_repeat;					// to show flag if the button is in the press-and-hold repeat state
}Button_Typedef;						


void btn_pressing_callback(Button_Typedef *ButtonX); 
void btn_press_short_callback(Button_Typedef *ButtonX);
void btn_release_callback(Button_Typedef *ButtonX);	
void btn_press_timeout_callback(Button_Typedef *ButtonX);
void btn_press_timeout_repeat_callback(Button_Typedef *ButtonX);
void button_handle(Button_Typedef *ButtonX);
void Button_Init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif
