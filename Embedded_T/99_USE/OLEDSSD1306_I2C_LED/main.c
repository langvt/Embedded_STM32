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

	/*
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

*/
	ClearDisplay();
	SSD1306_DrawBitmap(0, 0, heart, 30, 30 , SSD1306_COLOR_WHITE);
    //SSD1306_ScrollLeft( 0x00, 0x0f);  // scroll entire screen left
    //delay (5000000);
	SSD1306_ScrollRight( 0x00, 0x0f);    // scroll entire screen right
    delay (500000);
    SSD1306_Scrolldiagright( 0x00, 0x0f);  // scroll entire screen diagonal right
    delay (50000);
	SSD1306_Scrolldiagleft( 0x00, 0x0f);  // scroll entire screen diagonal left
    delay (50000);
    SSD1306_Stopscroll();   // stop scrolling. If not done, screen will keep on scrolling
    SSD1306_InvertDisplay( 1);   // invert the display
    delay (5000000);
	SSD1306_InvertDisplay( 0);  // normalize the display
	SSD1306_UpdateScreen();
		


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