#include "LCD_I2C.h"


/* write cmd Rs = 0x00
	ES = 1100 = 0x0C
	ES = 1000 = 0x09*/
void LCD_I2C_WriteCMD(uint8_t Data)
{
	uint8_t Buff[4];
	
	uint8_t Data_H = (Data & 0xf0);
	uint8_t Data_L = ((Data << 4) &0xf0);
	
	Buff[0] = Data_H | 0x0C;	//en=1, rs=0
	Buff[1] = Data_H | 0x08;	//en=0, rs=0
	Buff[2] = Data_L | 0x0C;	//en=1, rs=0
	Buff[3] = Data_L | 0x08;	 //en=0, rs=0
	
	I2C_Write_No_Reg(LCD_ADDR, Buff[0]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[1]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[2]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[3]);
}

/* write cmd Rs = 0x01
	ES = 1101 = 0x0D
	ES = 1001 = 0x09*/

void LCD_I2C_WriteData(uint8_t Data)
{
	uint8_t Buff[4];
	
	uint8_t Data_H = (Data & 0xf0);
	uint8_t Data_L = ((Data << 4) &0xf0);
	
	Buff[0] = Data_H | 0x0D;	//en=1, rs=0
	Buff[1] = Data_H | 0x09;	 //en=0, rs=0
	Buff[2] = Data_L | 0x0D;	//en=1, rs=0
	Buff[3] = Data_L | 0x09;	//en=0, rs=0
	
	I2C_Write_No_Reg(LCD_ADDR, Buff[0]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[1]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[2]);
	I2C_Write_No_Reg(LCD_ADDR, Buff[3]);
}

void LCD_I2C_Init(void)
{
	
	LCD_I2C_WriteCMD(0x33);		//khoi tao
	LCD_I2C_WriteCMD(0x32);		//khoi tao
	LCD_I2C_WriteCMD(0x28);		//mode 4 bit, 2lines,  5x8
	LCD_I2C_WriteCMD(0x01);		// xoa toan man hinh
	Delay_Ms(2);
	LCD_I2C_WriteCMD(0x06);		//tang con tro
	LCD_I2C_WriteCMD(0x0C);	// hien thi man hinh va tat con tro
	

}
void LCD_I2C_Clear(void)
{
	LCD_I2C_WriteCMD(0x01);		
	Delay_Ms(2);
}

void LCD_I2C_Location(uint8_t Rows, uint8_t Lows)
{

	switch(Rows)
	{
		case 0:
			LCD_I2C_WriteCMD(0x80|Lows);
			break;
		case 1:
			LCD_I2C_WriteCMD(0xC0|Lows);
			break;
		case 2:
			LCD_I2C_WriteCMD(0x94|Lows);
			break;
		case 3:
			LCD_I2C_WriteCMD(0xD4|Lows);
			break;
	}
}

void LCD_I2C_Write_String(char *string)
{
	while (*string) 
	{
		LCD_I2C_WriteData (*string++);
	}
}