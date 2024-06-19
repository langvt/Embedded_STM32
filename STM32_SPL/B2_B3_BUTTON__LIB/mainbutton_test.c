#include "systick.h"
#include "stm32f10x_gpio.h"

/*
but 1: led 1 turn on with f = 1hz
but 2: led 2 turn on with f = 5hz
but 3: 2 leds turn off
*/

void GPIO_config(void);
uint8_t sta_button;

//----------------------------------- var button------------------------------------
uint8_t btn_current = 1; // bien luu sau khi nut nhan da on dinh khong con bi nhieu
uint8_t btn_filter =1; // bien loc nhieu luu trong qua trinh nhieu 
uint8_t btn_last = 1;		// bien luu trạng thái cuối của nut nhấn
uint8_t is_debouncing;
uint32_t tim_deboune;

uint32_t time_start_press;
uint8_t is_press_timeout;

//----------------------------------- var led------------------------------------
typedef enum
{
	LED_OFF,
	LED1_BLINK_1HZ,
	LED1_BLINK_5HZ
	}


void btn_pressing_callback()  				// nhấn xuống
{

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
int main(void){
	SystemInit();
	SystickInit();
	GPIO_config();
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while(1){
		button_handle();
			//sta_button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			//GPIO_WriteBit(GPIOC, GPIO_Pin_13, sta_button);

		// if( sta_button == 0){
				
		//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		//		}
		//		else{
		//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		//		}
		
		/*if(sta_button == 0)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
		}
		else{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1);
		}*/
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
