#include "DS3231.h"

uint8_t Decimal2BCD(uint8_t num)
{
	return ((num/10) << 4) + (num%10);  // x0000 | 0000x = BCD
}
uint8_t BCD2_Decimal( uint8_t num)
{
	return ((num >> 4) * 10) + (num&0x0F); // 0000x * 10 + 0000x & 00001111
}

void rtc_write_time(Date_time *dt)
{

	uint8_t data[8];
	//data[0] = 0x00;
	data[0] = Decimal2BCD(dt->second);
	data[1] = Decimal2BCD(dt->minute);
	data[2] = Decimal2BCD(dt->hour);
	data[3] = Decimal2BCD(dt->day);
	data[4] = Decimal2BCD(dt->date);
	data[5] = Decimal2BCD(dt->month);
	data[6] = Decimal2BCD(dt->year);
	
	//wait until i2c1 not busy anymore
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	// Send slave address
	I2C_Send7bitAddress(I2C1, ADDRESS_DEVICE, I2C_Direction_Transmitter);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	// Send data byte
	int i;
	for (i = 0; i < 7; i ++)
	{
		I2C_SendData(I2C1, data[i]);
		// Wait for I2C EV8_2.
		// It means that the data has been physically shifted out and 
		// output on the bus)
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	
	// Generate I2C stop condition
	 I2C_GenerateSTOP(I2C1, ENABLE);

}

void rtc_read_time (Date_time *dt)
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
	I2C_Send7bitAddress(I2C1, ADDRESS_DEVICE, I2C_Direction_Transmitter);
	
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
	I2C_Send7bitAddress(I2C1, ADDRESS_DEVICE, I2C_Direction_Transmitter);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	// Enable ACK of received data
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

	int i;
	for(i = 0; i < 7; i++)
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


uint16_t temp;
uint8_t TempUpbyte; // thanh ghi 11
uint8_t TempLowByte; //thanh ghi 12
temp = (uint16) TempUpbyte << 2 |  TempLowByte >> 6;