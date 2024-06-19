/*
		Display.c file is a Board Support Package file.
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



void InitDisplay(void)
{
		/* LCD IS CONNECTED TO i2c-2
			 change this if you are using other ports
		 */
		SSD1306_Init(I2C2);
}

void ClearDisplay(void)
{
		SSD1306_Fill(SSD1306_COLOR_BLACK);
		SSD1306_UpdateScreen();
}

void WriteDisplayString(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_Fill(SSD1306_COLOR_BLACK);
		SSD1306_GotoXY (x , y);
	  SSD1306_Puts(data , &Font_7x10 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    SSD1306_UpdateScreen();
}

void WriteDisplayString1(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_Fill(SSD1306_COLOR_BLACK);
		SSD1306_GotoXY (x , y);
	  SSD1306_Puts(data , &Font_11x18 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    SSD1306_UpdateScreen();
}

void WriteDisplayString2(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_Fill(SSD1306_COLOR_BLACK);
		SSD1306_GotoXY (x , y);
	  SSD1306_Puts(data , &Font_16x26 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    SSD1306_UpdateScreen();
}



void WriteDisplayNoClear(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_GotoXY (x , y);
	  	SSD1306_Puts(data , &Font_7x10 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    	SSD1306_UpdateScreen();
}

void WriteDisplayNoClear1(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_GotoXY (x , y);
	  	SSD1306_Puts(data , &Font_11x18 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    	SSD1306_UpdateScreen();
}

void WriteDisplayNoClear2(char *data , DisplayPixel_t color , uint8_t x , uint8_t y)
{
		SSD1306_GotoXY (x , y);
	  	SSD1306_Puts(data , &Font_16x26 , color == DISPLAY_BLUE_COLOR ? SSD1306_COLOR_WHITE : SSD1306_COLOR_BLACK);
    	SSD1306_UpdateScreen();
}


void DrawPage(PageContainer_t *container)
{
		ClearDisplay();
		if(container->pageIndex == 0) {
			WriteDisplayNoClear(container->header , DISPLAY_BLUE_COLOR , 40 , 5);
			WriteDisplayNoClear(container->line_one , DISPLAY_BLUE_COLOR , 15 , 20);
			WriteDisplayNoClear(container->line_two , DISPLAY_BLUE_COLOR , 45 , 35);
			WriteDisplayNoClear(container->line_three , DISPLAY_BLUE_COLOR , 45 , 50);
		}
		else {
			WriteDisplayNoClear(container->header , DISPLAY_BLUE_COLOR , 15, 5);
			WriteDisplayNoClear(container->line_one , DISPLAY_BLUE_COLOR , 15 , 17);
			WriteDisplayNoClear(container->line_two , DISPLAY_BLUE_COLOR , 15 , 27);
			WriteDisplayNoClear(container->line_three , DISPLAY_BLUE_COLOR , 15 , 37);
			WriteDisplayNoClear(container->line_four , DISPLAY_BLUE_COLOR , 15 , 48);
		}
}

void DisplayThreeLinePage(char *line_one , char *line_two , char *line_three)
{
		PageContainer_t container;
		//container.header = "Ebrahim Co"; //"GB CELL";
		container.line_one = line_one;
		container.line_two = line_two;
		container.line_three = line_three;
		container.pageIndex = 2;
		//updateState = DISPLAY_UPDATE_DENIED;
		DrawPage(&container);
}


void DisplayFourLinePage(char *line_one , char *line_two , char *line_three , char *line_four)
{
		PageContainer_t container;
		container.header = line_one;
		container.line_one = line_two;
		container.line_two = line_three;
		container.line_three = line_four;
		container.pageIndex = 3;
		//updateState = DISPLAY_UPDATE_DENIED;
		DrawPage(&container);
}
void DisplayFineLinePage(char *line_one , char *line_two , char *line_three , char *line_four,  char *line_fine )
{
		PageContainer_t container;
		container.header = line_one;
		container.line_one = line_two;
		container.line_two = line_three;
		container.line_three = line_four;
		container.line_four = line_fine;
		container.pageIndex = 4;
		//updateState = DISPLAY_UPDATE_DENIED;
		DrawPage(&container);
}

void DrawPageOneLine(PageContainer_t *container)
{
		ClearDisplay();
			WriteDisplayNoClear(container->header , DISPLAY_BLUE_COLOR , 25, 25);
		}

void DisplayOneLinePage(char *line_one )
{
		PageContainer_t container;
		container.header = line_one;
		//container.line_one = line_one;
		container.pageIndex = 1;
		//updateState = DISPLAY_UPDATE_DENIED;
		DrawPageOneLine(&container);
}

void DrawPageTwoLine(PageContainer_t *container)
{
			WriteDisplayNoClear(container->line_one , DISPLAY_BLUE_COLOR , 15, 18);
			WriteDisplayNoClear(container->line_two , DISPLAY_BLUE_COLOR , 15 , 33);
	}

	
	void DisplayTwoLinePage(char *line_one , char *line_two)
{
		PageContainer_t container;
		container.line_one = line_one;
		container.line_two = line_two;
		container.pageIndex = 1;
		DrawPageTwoLine(&container);
}
