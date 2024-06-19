#include "main.h" 
uint16_t Adc; uint8_t Angle ;
Temp temp;
Button_Typedef BTN_DOWN, BTN_OK, BTN_UP;
int main(void)
{	
	SystickInit();
	buttonCallBackInit();
	clockInit();
	while(1)
	{	 
		clockHandle();
		buttonCallBackHandle();
		checkAlarm();
	}
}

