#include "Button.h"

 
void btn_pressing_callback(Button_Typedef *ButtonX)
{
}
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
	
	/*khi co tin hieu nhan nut(sta == 0)*/
	if(sta != ButtonX -> btn_filter)  
	{
		ButtonX -> btn_filter = sta; 	// btn_filter = 1 -> btn_filter = 0
		ButtonX -> is_debouncing = 1; 							
		ButtonX -> tim_deboune = getTick();		//  thoi diem gan is_debouncing = 1 
		}
		
	//-------------------------sau khi bấm nút thi mới tiến hành thực hiện điều kiện
			//----------------------------tín hiệu xác lập---------------------------
		/*is_debouncing == 1 den khi tim_deboune duoc 15s */
	if(ButtonX -> is_debouncing == 1 &&(getTick() - ButtonX -> tim_deboune >= 15))   // khi có nhiễu và điều kiện hợp lệ >=15 mới thực hiện 
		{
			ButtonX -> btn_current = ButtonX -> btn_filter;	// trang thai cua nut nhan la btn_filter gan cho btn_current
			ButtonX -> is_debouncing = 0;						// het nhieu thi  is_debouncing = 0 de k thuc hien vong if nay 
			}
		
	//----------------------------------------xử lý nhấn xuống ---------------------------------------
	if(ButtonX -> btn_current != ButtonX -> btn_last) // trang thai hien tai khac voi trang nhan lan cuoi truoc do
	{ 
				
			if(ButtonX -> btn_current == 0)	// nhấn nút
			{
				ButtonX -> is_press_timeout = 1; 	// biến cho nhấn lâu: khi nhấn nút mới bắt đầu xư ly
				btn_pressing_callback(ButtonX); 			// nhấn nút	
				ButtonX -> time_start_press = getTick();	// biến cho nhấn nut nhanh 1s: bắt đầu đếm tgian khi nhấnnut
			}
			else					// nhả nút
			{
				if(getTick() - ButtonX -> time_start_press <= 1000 )
				{
					btn_press_short_callback(ButtonX);  // nhấn nút nhả nhanh
				}
				btn_release_callback(ButtonX );           // nhả nút
				ButtonX -> is_press_timeout = 0; 		// khi nha nut thi khong con dau hiệu để vào hàm nhấn lâu
			}	
			ButtonX -> btn_last = ButtonX -> btn_current; // trang thai hien đuoc gan cho btn_last
	}
			
		// ----------------------------------- xử lý nhẫn giữ---------------------------
		/*khi is_press_timeout == 1 va nhan 3s thi thuc hien ham*/
	if(ButtonX -> is_press_timeout ==1 &&  ( getTick() -  ButtonX -> time_start_press >= 3000)) // khi co hien tuong nhan nhut va ket hop voi dieu kien
	{
		btn_press_timeout_callback(ButtonX );			// nhấn giữ lâu
		 ButtonX -> is_press_timeout = 0;
	}
}

void Button_Init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin )
{
	ButtonX -> btn_filter = 1;
	ButtonX -> btn_current = 1;
	ButtonX -> btn_last = 1;
	ButtonX -> GPIOx = GPIOx;
	ButtonX -> GPIO_Pin = GPIO_Pin;
}
void GPIO_BTN_config(void) {
	//enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		
	// BUTTON 1, 2 ,3 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}