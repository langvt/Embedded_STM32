#include "main.h"

Time time; 
Temp temp;

int main(void)
{
	ds3231_Init();
	SystickInit();

	time.second = 00;
	time. minute =33;
	time. hour= 14;
	time. day = 5;
	time. date = 22;
	time. month = 3;
	time. year = 24;
	ds3231_setTime(&time);

	while(1)
	{
		static uint32_t read_time = 0;
		if(getTick() -  read_time >= 1000)
		{
		ds3231_getTime(&time);
			
		ds3231_getTemp(&temp);
			
		read_time = getTick();
		}
		Delay_Ms(1000);
	}
}

