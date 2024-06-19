#ifndef BUTTON_H
#define BUTTON_H

#include "systick.h"
#include "stm32f10x_gpio.h"

typedef struct
{
uint8_t btn_current = 1 ; 
uint8_t btn_filter = 1 ; 
uint8_t btn_last = 1;		
uint8_t is_debouncing;
uint32_t tim_deboune;
uint32_t time_start_press; // bien dem nhan nhanh
uint8_t is_press_timeout; // bien cho ham nhan giu lau
GPIO_TypeDef *GPIOx;
uint16_t GPIO_Pin;
	
}Button_Typedef;

void GPIO_BTN_config(void);
void btn_pressing_callback(Button_Typedef *ButtonX); 
void btn_press_short_callback(Button_Typedef *ButtonX);		
void btn_release_callback(Button_Typedef *ButtonX);					 
void btn_press_timeout_callback(Button_Typedef *ButtonX);
void button_handle(Button_Typedef *ButtonX);
void Button_Init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin );
#endif
