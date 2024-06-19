#include "Button.h"

/*
but 1: led 1 turn on with f = 1hz
but 2: led 2 turn on with f = 5hz
but 3: 2 leds turn off
*/

void GPIO_config(void);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

Button_Typedef button1;
Button_Typedef button2;
//----------------------------------- var led------------------------------------
typedef enum
{
	LED_OFF,
	LED1_BLINK_1HZ,
	LED2_BLINK_5HZ
	} LedStatus;

	LedStatus led_status;
	
void btn_pressing_callback(Button_Typedef *ButtonX)  
{
	if(ButtonX == &button1)
	{	switch(led_status)
		{
			case LED_OFF:
				led_status = LED1_BLINK_1HZ;
				break;
			case LED1_BLINK_1HZ:
				led_status = LED2_BLINK_5HZ;
				break;
			case LED2_BLINK_5HZ:
				led_status = LED_OFF;
				break;
			default:
				break;
		}
	}
	else if(ButtonX == &button2)
	{

	}
}

void led1Blink1hz()
{
	static uint32_t tled1_blink;			// static khai bao cucbo thi k dug toan cuc duoc
	if(getTick() - tled1_blink >= 500)
	{
		GPIO_TogglePin(GPIOC, GPIO_Pin_13);
		tled1_blink = getTick();
	}
}

void led2Blink5hz()
{
	static uint32_t tled2_blink ;			// static khai bao cucbo thi k dug toan cuc duoc
	if(getTick() - tled2_blink >= 100)
	{
		GPIO_TogglePin(GPIOC, GPIO_Pin_14);
		tled2_blink = getTick();
	}
}

void led_off(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13 | GPIO_Pin_14, 0);
}

void led_handle (void)
{
	switch(led_status)
	{
		case LED_OFF:
			led_off();
			break;
		case LED1_BLINK_1HZ:
			led1Blink1hz();
			break;
		case LED2_BLINK_5HZ:
			led2Blink5hz();
			break;
		default:
			break;
	}
}
int main(void){
	SystickInit();
	GPIO_config();
	Button_Init(&button1, GPIOA, GPIO_Pin_0);
	Button_Init(&button2, GPIOA, GPIO_Pin_1);
	while(1){
		button_handle(&button1);
		button_handle(&button2);
		led_handle();
	}
}	

void GPIO_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* get current Output Data Register value */
  odr = GPIOx->ODR;

  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16u) | (~odr & GPIO_Pin);
}