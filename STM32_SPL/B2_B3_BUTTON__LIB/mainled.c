#include "systick.h"
#include "stm32f10x_gpio.h"

/*
but 1: led 1 turn on with f = 1hz
but 2: led 2 turn on with f = 5hz
but 3: 2 leds turn off
*/

void GPIO_config(void);

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




//----------------------------------- var led------------------------------------
typedef enum
{
	LED_OFF,
	LED1_BLINK_1HZ,
	LED2_BLINK_5HZ
	} LedStatus;

	LedStatus led_status;


void btn_pressing_callback()  				// nhấn xuống
{
	switch(led_status)
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
	}
	
}
void btn_press_short_callback()			// nhấn nút nhanh
	{

		}
void btn_release_callback() 					 // nhả nút 
{
	
	}
void btn_press_timeout_callback() 		// nhấn nút lâu
	{
		
		}

void button_handle(void)
{
	//------------------------------------lọc nhiễu--------------------------------------
	uint8_t sta = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	if(sta != btn_filter)
		{
			btn_filter = sta;
			is_debouncing = 1; 									// thể hiện mỗi lần có nhiễu
			tim_deboune = getTick();
			}
		
	//-------------------------sau khi bấm nút thi mới tiến hành thực hiện điều kiện
			//----------------------------tín hiệu xác lập---------------------------
	if(is_debouncing &&(getTick() - tim_deboune >= 15))   // khi có nhiễu và điều kiện hợp lệ >=15 mới thực hiện 
		{
			btn_current = btn_filter;
			is_debouncing = 0;										// hết nhiễu
			}
		
	//----------------------------------------xử lý nhấn xuống ---------------------------------------
	if(btn_current != btn_last)
			{ 
				is_press_timeout = 1;						// biến cho nhấn lâu: khi nhấn nút mới bắt đầu xư ly
				if(btn_current == 0)	// nhấn nút
					{
						btn_pressing_callback(); 									// nhấn nút	
						time_start_press = getTick();	// biến cho nhấn nut nhanh 1s: bắt đầu đếm tgian khi nhấnnut
					}
				else						// nhả nút
					{
						if(getTick() - time_start_press <= 1000 )
							{
								btn_press_short_callback();  				// nhấn nút nhả nhanh
							}
							btn_release_callback();                             // nhả nút
							is_press_timeout = 0; 		// khi nha nut thi khong con dau hiệu để vào hàm nhấn lâu
					}	
				btn_last = btn_current;
			}
			
		// ----------------------------------- xử lý nhẫn giữ---------------------------
	if(is_press_timeout &&  ( getTick() -  time_start_press >= 3000)) // khi co hien tuong nhan nhut va ket hop voi dieu kien
		{
			btn_press_timeout_callback();									// nhấn giữ lâu
			 is_press_timeout = 0;
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
	}
}
int main(void){
	SystemInit();
	SystickInit();
	GPIO_config();
	while(1){
		button_handle();
		led_handle();
	}
}	

void GPIO_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_Pin_ 13_14_15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}
