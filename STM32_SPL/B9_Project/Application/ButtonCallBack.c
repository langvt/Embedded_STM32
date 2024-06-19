#include "ButtonCallBack.h"

extern Button_Typedef BTN_DOWN, BTN_OK, BTN_UP;
extern ClockState Clock_State;
extern LiquidCrystal_I2C lcd;

//-------------------------------------------------Call_back button -----------------------------------------------------//

/*
* Function: btn_pressing_callback
* Description: Callback function invoked when a button is pressed and held.
* Input:
*   - Button_Typedef *ButtonX: Pointer to the button structure representing the pressed button.
* Output: None
* 
* This function adjusts the time either up or down based on the pressed button and resets the time start.
*/
void btn_pressing_callback(Button_Typedef *ButtonX)
{ 

	if(ButtonX == &BTN_UP)
	{
		adjustTime(1);
	}
	
	else if(ButtonX == &BTN_DOWN)
	{
		adjustTime(0);
	}
	resetTimeStart();
}

/*
* Function: btn_press_short_callback
* Description: Callback function invoked when a button is pressed briefly.
* Input:
*   - Button_Typedef *ButtonX: Pointer to the button structure representing the pressed button.
* Output: None
* 
* This function transitions the clock state based on the pressed button and resets the time start.
*/
void btn_press_short_callback(Button_Typedef *ButtonX)			
{
	if(ButtonX  == &BTN_OK)
	{
		switch(Clock_State)
		{
			case NORMAL_STATE:
				Clock_State = SETTING_HOUR_STATE;
				break;
			
			case SETTING_HOUR_STATE:
				Clock_State = SETTING_MIN_STATE;
				break;
			case SETTING_MIN_STATE:
				Clock_State = SETTING_SEC_STATE;
				break;
			
			case SETTING_SEC_STATE:
				Clock_State = SETTING_DATE_STATE;
				break;
			case SETTING_DATE_STATE:
				Clock_State = SETTING_MONTH_STATE;
				break;
			
			case SETTING_MONTH_STATE:
				Clock_State = SETTING_YEAR_STATE;
				break;
			
			case SETTING_YEAR_STATE:
				Clock_State = NORMAL_STATE;
				break;
			case ALARM_HOUR_STATE:
				Clock_State = ALARM_MIN_STATE;
				break;
			case ALARM_MIN_STATE:
				Clock_State = NORMAL_STATE;
				break;
			default : break;
		}
		resetTimeStart();
	}
}

/*
* Function: btn_press_timeout_callback
* Description: Callback function invoked when a button is pressed for a long duration.
* Input:
*   - Button_Typedef *ButtonX: Pointer to the button structure representing the pressed button.
* Output: None
* 
* This function updates the alarm and sets the clock state to ALARM_HOUR_STATE, then resets the time start.
*/
void btn_press_timeout_callback(Button_Typedef *ButtonX) 		
{
	
	if(ButtonX  == &BTN_OK)
	{
		alarmUpdate();
		Clock_State  =  ALARM_HOUR_STATE ;
	
	}
	resetTimeStart();
}

/*
* Function: btn_press_timeout_repeat_callback
* Description: Callback function invoked when a button is held down for a long duration and repeats.
* Input:
*   - Button_Typedef *ButtonX: Pointer to the button structure representing the pressed button.
* Output: None
* 
* This function adjusts the time either up or down based on the pressed button and resets the time start.
*/
void btn_press_timeout_repeat_callback(Button_Typedef *ButtonX)
{
	if (ButtonX == &BTN_UP)
	{
		adjustTime(1);
	}
	else if(ButtonX == &BTN_DOWN)
	{
		adjustTime(0);
	}
	resetTimeStart();
}

/*
* Function: GPIO_BTN_config
* Description: Configures the GPIO pins for buttons.
* Input: None
* Output: None
* 
* This function initializes the GPIO pins used for the buttons on the microcontroller.
*/
void GPIO_BTN_config(void)
{
		//enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 2,3,4
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
* Function: buttonCallBackInit
* Description: Initializes button structures for callback handling.
* Input: None
* Output: None
* 
* This function initializes the button structures used for callback handling.
*/
void buttonCallBackInit(void)
{
	Button_Init(&BTN_DOWN,GPIOA,GPIO_Pin_4);
	Button_Init(&BTN_OK,GPIOA,GPIO_Pin_3);
	Button_Init(&BTN_UP,GPIOA,GPIO_Pin_2);
}

/*
* Function: buttonCallBackHandle
* Description: Handles button callback events.
* Input: None
* Output: None
* 
* This function handles button callback events by calling the button_handle function for each button.
*/
void buttonCallBackHandle(void)
{
		button_handle(&BTN_DOWN);
		button_handle(&BTN_UP);
		button_handle(&BTN_OK);
}
