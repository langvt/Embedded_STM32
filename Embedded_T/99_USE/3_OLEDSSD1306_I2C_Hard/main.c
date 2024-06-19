/*
		main.c file is Example of using.
    Copyright (C) 2018 Nima Mohammadi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "display.h"





void DisplayShowTestPage(void);
void delay(int time);

int main(void)
{
	
	
	// InitDisplay
	InitDisplay();



	
		// InitDisplay
		InitDisplay();

		//UpdateDisplay
		//DisplayShowTestPage();
		//DisplayThreeLinePage("XIN CHAO", "HUwf", "XI");
		//DisplayFineLinePage("XIN CHAO", "HUGwf", "XH", "fdgs", "fdsdghhg" );
			//DisplayOneLinePage("Hi, Wellcom" );
			//delay(9000000);
			//ClearDisplay();
	
			//DisplayOneLinePage("How it's going" );
			//delay(9000000);
			//ClearDisplay();
	
			//DisplayOneLinePage("And" );
			//delay(9000000);
			//ClearDisplay();
			//DisplayTwoLinePage("Today, is my birthday 21st");
			//delay(9000000);
			//ClearDisplay();
	
			//DisplayOneLinePage("Hehe, Bai Baii =))/" );	
	
	
	//WriteDisplayString("hi" , DISPLAY_BLUE_COLOR, 15, 10);
	
	
//	WriteDisplayString("dung buon nua" , DISPLAY_BLUE_COLOR, 6, 12);
	//WriteDisplayNoClear( "hay vui lenn! =))." , DISPLAY_BLUE_COLOR, 6, 40);


	
			
	WriteDisplayString1("Hallo" , DISPLAY_BLUE_COLOR, 3 , 25);
		SSD1306_DrawBitmap(65 , 18, haha, 30, 30, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	SSD1306_ScrollRight( 0x00, 0x0f);  // scroll entire screen left
    delay (2300000);	
		SSD1306_Stopscroll();
		
		
			delay(8000000);
			ClearDisplay();
	WriteDisplayString1("How's it" , DISPLAY_BLUE_COLOR, 20, 8);
	WriteDisplayNoClear1("going?" , DISPLAY_BLUE_COLOR, 20, 40);
	
	
	
		delay(9500000);
			ClearDisplay();
		SSD1306_DrawBitmap(0 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(5 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(10 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(15 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
		delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(20 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(25 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(30 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(35 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(40 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(45 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(50 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(55 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(55 , 7, walkmen_4, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
			delay(1600000);
	WriteDisplayNoClear("**Just Do It**" , DISPLAY_BLUE_COLOR, 10, 49);
	delay(9000000);
	WriteDisplayNoClear("**and Keep going**", DISPLAY_BLUE_COLOR, 0, 49);
		
				delay(9000000);
			ClearDisplay();
		SSD1306_DrawBitmap(55 , 7, walkmen_5, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
		delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(60 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(65 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(70 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(75 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(80 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(85 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(90 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(95 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
			SSD1306_DrawBitmap(100 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(105 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(110 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(115 , 7, walkmen_3, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
			
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(120 , 7, walkmen_0, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
	
			delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(120 , 7, walkmen_1, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
				delay(1600000);
			ClearDisplay();
		SSD1306_DrawBitmap(130 , 7, walkmen_2, 19, 39, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();



			delay(4000000);
			ClearDisplay();
	WriteDisplayString2("AND" , DISPLAY_BLUE_COLOR, 42, 22);
	
			delay(8000000);
			ClearDisplay();
	WriteDisplayString("Today is" , DISPLAY_BLUE_COLOR, 6, 12);
	WriteDisplayNoClear( "my 21st birthday!" , DISPLAY_BLUE_COLOR, 6, 40);
	
	
			delay(14000000);
			ClearDisplay();
	WriteDisplayString2("So..." , DISPLAY_BLUE_COLOR, 30, 22);
	
	
			delay(10000000);
			ClearDisplay();
		SSD1306_DrawBitmap(0,0, beer, 128, 64, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
			
		SSD1306_ScrollRight( 0x00, 0x0f);    // scroll entire screen right
    delay (5000000);
    SSD1306_ScrollLeft( 0x00, 0x0f);  // scroll entire screen left
    delay (5000000);
    SSD1306_Stopscroll();   // stop scrolling. If not done, screen will keep on scrolling
    SSD1306_InvertDisplay( 1);   // invert the display
    delay (5000000);
		SSD1306_InvertDisplay( 0);  // normalize the display


		delay(9000000);
		ClearDisplay();
		WriteDisplayString2("AND" , DISPLAY_BLUE_COLOR, 42, 22);
	

	delay(8500000);
	ClearDisplay();
	SSD1306_DrawBitmap(0,5, cake2, 128, 64, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
	
		
		

    SSD1306_ScrollLeft( 0x00, 0x0f);  // scroll entire screen left
    delay (5000000);
	SSD1306_ScrollRight( 0x00, 0x0f);    // scroll entire screen right
    delay (5000000);
    //SSD1306_Scrolldiagright( 0x00, 0x0f);  // scroll entire screen diagonal right
    //delay (5000000);
	//SSD1306_Scrolldiagleft( 0x00, 0x0f);  // scroll entire screen diagonal left
    // delay (5000000);
    SSD1306_Stopscroll();   // stop scrolling. If not done, screen will keep on scrolling
    SSD1306_InvertDisplay( 1);   // invert the display
    delay (5000000);
		SSD1306_InvertDisplay( 0);  // normalize the display
		
	delay(9000000);
	ClearDisplay();
	WriteDisplayString1("Happy" , DISPLAY_BLUE_COLOR, 5, 8);
	WriteDisplayNoClear1("Birthday to" , DISPLAY_BLUE_COLOR, 5 , 42);
	 delay (11000000);
	 

		ClearDisplay();
		SSD1306_DrawBitmap(0, 0, me2, 124, 64, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
	delay(9000000);
	ClearDisplay();
	WriteDisplayString1("Bai Baii" , DISPLAY_BLUE_COLOR, 20, 10);
	WriteDisplayNoClear1( "=))." , DISPLAY_BLUE_COLOR, 47, 38);

			delay(90000000);
		ClearDisplay();
		WriteDisplayString2("X" , DISPLAY_BLUE_COLOR, 42, 22);
			
/*			delay(10000000);
			ClearDisplay();
	  SSD1306_DrawBitmap(0,0,walkmen_0, 19, 5, SSD1306_COLOR_WHITE);
	  SSD1306_DrawBitmap(0,0,walkmen_1, 19, 5, SSD1306_COLOR_WHITE);
	  SSD1306_DrawBitmap(0,0,walkmen_2, 19, 5, SSD1306_COLOR_WHITE);
	  SSD1306_DrawBitmap(0,0,walkmen_3, 19, 5, SSD1306_COLOR_WHITE);
	  SSD1306_DrawBitmap(0,0,walkmen_4, 19, 5, SSD1306_COLOR_WHITE);		
		SSD1306_UpdateScreen();
*/

/*
	//display animation
uint8_t loop;
while(loop = 10){
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey1,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey2,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey3,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey4,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey5,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey6,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey7,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey8,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey9,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			ClearDisplay();
			SSD1306_DrawBitmap(0,0,monkey10,128,64,SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
		}		
*/
			while(1);
}


void DisplayShowTestPage(void)
{ 
		PageContainer_t container;
		container.header = "XIN CHAO";
		container.line_one = "Hwf";
		container.line_two = "XHH";
		container.line_three = "=))/";
		container.line_four = "fdgs";
		DrawPage(&container);
}

void delay (int time){
	int i;
	for(i = 0; i < time; i++);
}