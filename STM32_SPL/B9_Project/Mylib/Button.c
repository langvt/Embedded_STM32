#include "Button.h"


/*
* Function: btn_pressing_callback
* Description: call back function when the button is being pressed
* Input: ButtonX pointer to the Button_Typedef
* Output: None
*/
//void btn_pressing_callback(Button_Typedef *ButtonX)
//{ 
//}

/*
* Function: btn_press_short_callback
* Description: call back function when the button is being press and released quickly
* Input: ButtonX pointer to the Button_Typedef
* Output: None
*/
//void btn_press_short_callback(Button_Typedef *ButtonX)			
//{
//}

/*
* Function: btn_press_short_callback
* Description: call back function when the button is being released
* Input: ButtonX pointer to the Button_Typedef
* Output: None
*/
//void btn_release_callback(Button_Typedef *ButtonX) 					 
//{
//}

/*
* Function: btn_press_short_callback
* Description: call back function when the button is being pressed and held  exceeding the timeout multiple times
* Input: ButtonX pointer to the Button_Typedef
* Output: None
*/
//void btn_press_timeout_callback(Button_Typedef *ButtonX) 		
//{
//}

/*
* Function: btn_press_timeout_repeat_callback
* Description: call back function when the button is being pressed and hold a long time
* Input: ButtonX pointer to the Button_Typedef
* Output: None
*/
//void btn_press_timeout_repeat_callback(Button_Typedef *ButtonX)
//{
//}

/*
* Function: button_handle
* Description: called in the main loop of the program, check the current status of the buttob, update state variable and call the callback base on the button state
* Input: - ButtonX pointer to the Button_Typedef contains the button information
* Output: None
*/
void button_handle(Button_Typedef *ButtonX)
{

	//------------------------------------Debounce--------------------------------------
	uint8_t sta = GPIO_ReadInputDataBit(ButtonX->GPIOx, ButtonX ->GPIO_Pin);
	if(sta != ButtonX -> btn_filter)
	{
		ButtonX -> btn_filter = sta;
		ButtonX -> is_debouncing = 1; 									
		ButtonX -> tim_deboune = getTick();
		}
		
	/*-------------------------after pressed button carry out the condition-----------------*/
			/*---------------------------signals stabilization---------------------------*/
		
	if(ButtonX -> is_debouncing ==1 &&(getTick() - ButtonX -> tim_deboune >= 15))   
		/*----when there is noise and valid condition >=15ms is met-----*/
		{
			ButtonX -> btn_current = ButtonX -> btn_filter;
			ButtonX -> is_debouncing = 0;										
			}
			/*----------------------------noise eliminated-----------------------------*/
			
	/*----------------------------------------handle button pressed -------------------------------*/
	if(ButtonX -> btn_current != ButtonX -> btn_last)
	{ 
			if(ButtonX -> btn_current == 0)	
				/*------button pressed------------*/
			{
				ButtonX -> flag_repeat = 1;
				ButtonX -> is_press_timeout = 1;				// variable for long press: when button is pressed, start handle
				btn_pressing_callback(ButtonX); 					// callback button pressed
				ButtonX -> time_start_press = getTick();		// variable for quick press 1s: start timing when button is pressed
				ButtonX -> time_start_press_repeat = getTick(); // set time for countinous button press
			}
			else	/*----------------- button released ---------------------*/
			{
				if(getTick() - ButtonX -> time_start_press <= 1000 )
				{
					btn_press_short_callback(ButtonX);  		// callback button short press and release
				}
				//btn_release_callback(ButtonX ); 				// callback button released
				ButtonX -> is_press_timeout = 0; 				// when button is released, no longer signals for long press
				ButtonX -> flag_repeat = 0;
			}	
			ButtonX -> btn_last = ButtonX -> btn_current;
	}
			
		// ----------------------------------- handle 3s long press---------------------------
	if(ButtonX -> is_press_timeout == 1 &&  ( getTick() -  ButtonX -> time_start_press >= 2000)) 
	/*--------- // when there is button press and condition is met----------------*/
	{
		btn_press_timeout_callback(ButtonX );					// callback button long press
		 ButtonX -> is_press_timeout = 0;
	}
	/*----------------------------------- Handle continuous increase on long press---------------*/
	if(ButtonX ->flag_repeat == 1 && (getTick() - ButtonX -> time_start_press_repeat >= 400))
	{
		btn_press_timeout_repeat_callback(ButtonX);			// callback button increase value and long press
		ButtonX -> time_start_press_repeat = getTick();
	}
}

/*
* Function: Button_Init
* Description: set up related GPIO port, pin used for the button and initial configurations for button
* Input: - ButtonX pointer to the Button_Typedef
*			- GPIO port with the button
*			- GPIO pin with the button
* Output: None
*/
void Button_Init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin )
{
	ButtonX ->btn_current = 1;
	ButtonX ->btn_filter = 1;
	ButtonX ->btn_last = 1;
	ButtonX -> GPIOx = GPIOx;
	ButtonX -> GPIO_Pin = GPIO_Pin;
	
}

