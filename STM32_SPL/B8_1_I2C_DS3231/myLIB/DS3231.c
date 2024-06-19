/** Includes ---------------------------------------------------------------- */	
#include "DS3231.h"

void ds3231_Init(void)
{
	I2C_Config();
}

uint8_t Decimal2BCD(uint8_t num)
{
	return ((num/10) << 4) + (num%10);  // x0000 | 0000x = BCD
}
uint8_t BCD2_Decimal( uint8_t num)
{
	return ((num >> 4) * 10) + (num&0x0F); // 0000x * 10 + 0000x & 00001111
}

void ds3231_setSeconds(Time *time )
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_SECONDS, Decimal2BCD(time->second));
}

uint8_t ds3231_getSeconds(void)
{
	uint8_t seconds;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_SECONDS, &seconds);
	return BCD2_Decimal(seconds);
}

void ds3231_setMinutes(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_MINUTES, Decimal2BCD(time->minute));
}

uint8_t ds3231_getMinutes(void)
{
	uint8_t minutes;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_MINUTES, &minutes);
	return BCD2_Decimal(minutes);
}

void ds3231_setHours(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_HOURS, Decimal2BCD(time->hour));
}

uint8_t ds3231_getHours(void)
{
	uint8_t hours;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_HOURS, &hours);
	return BCD2_Decimal (hours);
}

void ds3231_setDay(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_DAY, Decimal2BCD(time->day));
}

uint8_t ds3231_getDay( void)
{
	uint8_t day;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_DAY, &day);
	return BCD2_Decimal (day);
}

void ds3231_setDate(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_DATE, Decimal2BCD(time->date));
}

uint8_t ds3231_getDate( void)
{
	uint8_t date;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_DATE, &date);
	return BCD2_Decimal (date);
}


void ds3231_setMonth(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_MONTH, Decimal2BCD(time->month));
}

uint8_t ds3231_getMonth(void)
{
	uint8_t month;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_MONTH, &month);
	return BCD2_Decimal (month);
}

void ds3231_setYear(Time *time)
{
	I2C_Write_Reg(DS3231_ADDRESS, DS3231_YEAR, Decimal2BCD(time->year));
}

uint8_t ds3231_getYear(void )
{
	uint8_t year;
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_YEAR, &year);
	return BCD2_Decimal(year);
}

void ds3231_setTime(Time *time)
{
	ds3231_setSeconds(time);
	ds3231_setMinutes(time); 
	ds3231_setHours(time);
	ds3231_setDay(time); 
	ds3231_setDate(time);
	ds3231_setMonth(time); 
	ds3231_setYear(time);  
}

void ds3231_getTime(Time *time)
{
	time->second = ds3231_getSeconds();
	time->minute = ds3231_getMinutes();
	time->hour = ds3231_getHours();
	time->day = ds3231_getDay();
	time->date = ds3231_getDate();
	time->month = ds3231_getMonth();
	time->year = ds3231_getYear();	
}

uint8_t ds3231_getTemp(Temp *temp)
{

	uint8_t TempUpByte ;
	uint8_t TempLowByte ;
	
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_TEMP_UPBYTE, &TempUpByte);
	 temp ->TempUp = TempUpByte;
	
	I2C_Read_Reg(DS3231_ADDRESS, DS3231_TEMP_LOWBYTE, &TempLowByte);
	 temp ->TempLow = TempLowByte;
	
	 temp->Temperature = (uint16_t)temp ->TempUp << 2 | temp ->TempLow >> 6;
	
	return temp->Temperature ;
}


void rtc_write_time(Time *dt)
{

	uint8_t data[8];
	data[0] = 0x00;
	data[1] = Decimal2BCD(dt->second);
	data[2] = Decimal2BCD(dt->minute);
	data[3] = Decimal2BCD(dt->hour);
	data[4] = Decimal2BCD(dt->day);
	data[5] = Decimal2BCD(dt->date);
	data[6] = Decimal2BCD(dt->month);
	data[7] = Decimal2BCD(dt->year);
	
	//wait until i2c1 not busy anymore
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	// Send slave address
	I2C_Send7bitAddress(I2C1, DS3231_ADDRESS, I2C_Direction_Transmitter);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	// Send data byte
	int i;
	for (i = 0; i < 7; i ++)
	{
			// Wait for I2C EV8_2.
		// It means that the data has been physically shifted out and 
		// output on the bus)
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		I2C_SendData(I2C1, data[i]);

	}
	
	// Generate I2C stop condition
	 I2C_GenerateSTOP(I2C1, ENABLE);

}

void rtc_read_time (Time *dt)
{
	uint8_t ADD_REG = 0x00;
	uint8_t data[7];
	//wait until i2c1 not busy anymore
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
		// Send slave address
	I2C_Send7bitAddress(I2C1, DS3231_ADDRESS, I2C_Direction_Transmitter);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	// Send data byte
	I2C_SendData(I2C1, ADD_REG);
	// Wait for I2C EV8_2.
	// It means that the data has been physically shifted out and 
	// output on the bus)
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	// Generate I2C stop condition
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	//wait until i2c1 not busy anymore
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
			// Send slave address
	I2C_Send7bitAddress(I2C1, DS3231_ADDRESS, I2C_Direction_Transmitter);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	// Enable ACK of received data
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

	for(uint8_t i = 0; i < 7; i++)
	{
		// Enable ACK of received data
		I2C_AcknowledgeConfig(I2C1, DISABLE);
		// Wait for I2C EV7
		// It means that the data has been received in I2C data register
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

		data[i] = I2C_ReceiveData(I2C1);
	}

	dt->second 		= BCD2_Decimal(data[0]);
	dt->minute		= BCD2_Decimal(data[1]);
	dt->hour  			= BCD2_Decimal(data[2]);
	dt->day				= BCD2_Decimal(data[3]);
	dt->date			= BCD2_Decimal(data[4]);
	dt->month			= BCD2_Decimal(data[5]);
	dt->year 			= BCD2_Decimal(data[6]);
	

	I2C_GenerateSTOP(I2C1, ENABLE); 
	//return dt->second | dt->minute | dt->hour | dt->day | dt->date | dt->month | dt->year; 
}