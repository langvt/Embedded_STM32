#include "Button.h"

void btn_press_short_callback(Button_Typedef *ButtonX)			
{
}
void btn_release_callback(Button_Typedef *ButtonX) 					 
{
}
void btn_press_timeout_callback(Button_Typedef *ButtonX) 		
{
}

void button_handle(Button_Typedef *ButtonX)
{
	//------------------------------------lọc nhiễu--------------------------------------
	uint8_t sta = GPIO_ReadInputDataBit(ButtonX->GPIOx, ButtonX ->GPIO_Pin);
	if(sta != ButtonX -> btn_filter)
	{
		ButtonX -> btn_filter = sta;
		ButtonX -> is_debouncing = 1; 									
		ButtonX -> tim_deboune = getTick();
		}
		
	//-------------------------sau khi bấm nút thi mới tiến hành thực hiện điều kiện
			//----------------------------tín hiệu xác lập---------------------------
	if(ButtonX -> is_debouncing &&(getTick() - ButtonX -> tim_deboune >= 15))   // khi có nhiễu và điều kiện hợp lệ >=15 mới thực hiện 
		{
			ButtonX -> btn_current = ButtonX -> btn_filter;
			ButtonX -> is_debouncing = 0;										// hết nhiễu
			}
		
	//----------------------------------------xử lý nhấn xuống ---------------------------------------
	if(ButtonX -> btn_current != ButtonX -> btn_last)
	{ 
			ButtonX -> is_press_timeout = 1;						// biến cho nhấn lâu: khi nhấn nút mới bắt đầu xư ly
			if(ButtonX -> btn_current == 0)	// nhấn nút
			{
				btn_pressing_callback(ButtonX); 									// nhấn nút	
				ButtonX -> time_start_press = getTick();	// biến cho nhấn nut nhanh 1s: bắt đầu đếm tgian khi nhấnnut
			}
			else					// nhả nút
			{
				if(getTick() - ButtonX -> time_start_press <= 1000 )
				{
					btn_press_short_callback(ButtonX);  				// nhấn nút nhả nhanh
				}
				btn_release_callback(ButtonX );                             // nhả nút
				ButtonX -> is_press_timeout = 0; 		// khi nha nut thi khong con dau hiệu để vào hàm nhấn lâu
			}	
			ButtonX -> btn_last = ButtonX -> btn_current;
	}
			
		// ----------------------------------- xử lý nhẫn giữ---------------------------
	if(ButtonX -> is_press_timeout &&  ( getTick() -  ButtonX -> time_start_press >= 3000)) // khi co hien tuong nhan nhut va ket hop voi dieu kien
	{
		btn_press_timeout_callback(ButtonX );									// nhấn giữ lâu
		 ButtonX -> is_press_timeout = 0;
	}
}

void Button_Init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin )
{
	ButtonX -> GPIOx = GPIOx;
	ButtonX -> GPIO_Pin = GPIO_Pin;
}