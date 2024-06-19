/** Includes ---------------------------------------------------------------- */	
#include "I2C.h"

/** Private function prototypes --------------------------------------------- */
void I2c_Start(void);
void I2c_Stop(void);
void I2c_Address_Direction(uint8_t Address, uint8_t Direction);
void I2c_Transmit(uint8_t Byte);
uint8_t I2c_Receive_Ack(void);
uint8_t I2c_Receive_Nack(void);

 
 /*
* Function: I2C_Config
* Description: Initializes the I2C peripheral and configures the GPIO pins
* Input: None
* Output: None
*/
void I2C_Config(void)
{
	//ConfigGPIO
	RCC_APB2PeriphClockCmd(I2C_GPIO_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = I2C_PIN_SCL | I2C_PIN_SDA ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

	//Config I2C
	RCC_APB1PeriphClockCmd(I2C_RCC, ENABLE);	
	I2C_InitTypeDef	 I2C_InitStructure;
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx, &I2C_InitStructure);
	I2C_Cmd(I2Cx, ENABLE);
}

 /*
* Function: I2C_Write_Reg
* Description: Writes a data byte to a specific register of an I2C device.
* Input: - Address: 7 bit i2c drive
			-Reg:  Register address to write to
			-Data: data byte to write to the register.
* Output: None
*/
void I2C_Write_Reg(uint8_t Address, uint8_t Reg, uint8_t Data)
{
	I2c_Start();
	I2c_Address_Direction(Address , I2C_Direction_Transmitter);
	I2c_Transmit(Reg);
	I2c_Transmit(Data);
	I2c_Stop();
}

 /*
* Function: I2C_Write_No_Reg
* Description: Writes a data byte to an I2C device without specifying a register
* Input: - Address: 7 bit i2c drive
			-Data: data byte to write to the register.
* Output: None
*/
void I2C_Write_No_Reg(uint8_t Address, uint8_t Data)
{
	I2c_Start();
	I2c_Address_Direction(Address , I2C_Direction_Transmitter);
	I2c_Transmit(Data);
	I2c_Stop();
}

 /*
* Function: I2C_Read_Reg
* Description: Reads a data byte from a specific register of an I2C device.
* Input: - Address: 7 bit i2c drive
			- Reg: Register address to read from.
			-Data: data byte to write to the register.
* Output: None
*/
void I2C_Read_Reg(uint8_t Address, uint8_t Reg, uint8_t *Data)
{
	I2c_Start();
	I2c_Address_Direction(Address, I2C_Direction_Transmitter);
	I2c_Transmit(Reg);
	I2c_Stop();
	I2c_Start();
	I2c_Address_Direction(Address, I2C_Direction_Receiver);
	*Data = I2c_Receive_Nack();
	I2c_Stop();
}

 /*
* Function: I2C_Read_No_Reg
* Description:Reads a data byte from an I2C device without specifying a register.
* Input: - Address: 7 bit i2c drive
			-Data: data byte to write to the register.
* Output: None
*/
void I2C_Read_No_Reg(uint8_t Address, uint8_t *Data)
{
	I2c_Start();
	I2c_Address_Direction(Address, I2C_Direction_Transmitter);
	I2c_Stop();
	I2c_Start();
	I2c_Address_Direction(Address, I2C_Direction_Receiver);
	*Data = I2c_Receive_Nack();
	I2c_Stop();
}

 /*
* Function: I2c_Start
* Description: Generates a start condition on the I2C bus
* Input: None
* Output: None
*/
void I2c_Start(void)
{
	// Wait until I2Cx is not busy anymore
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	
	// Generate start condition
	I2C_GenerateSTART(I2Cx, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	/* BUSY, MSL and SB flag */
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
}

 /*
* Function: I2c_Stop
* Description:  Generates a stop condition on the I2C bus.
* Input: None
* Output: None
*/
void I2c_Stop(void)
{
	// Generate I2C stop condition
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

 /*
* Function: I2c_Address_Direction
* Description:  Sends the address of the I2C device along with the data direction
* Input: address: 7-bit I2C device address.
			direction: Data direction (I2C_Direction_Transmitter or I2C_Direction_Receiver).
* Output: None
*/
void I2c_Address_Direction(uint8_t address, uint8_t direction)
{
	// Send slave address
	I2C_Send7bitAddress(I2Cx, address, direction);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	if (direction == I2C_Direction_Transmitter)
	{
		/* BUSY, MSL, ADDR, TXE and TRA flags */
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if (direction == I2C_Direction_Receiver)
	{	
		 /* BUSY, MSL and ADDR flags */
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

 /*
* Function: I2c_Transmit
* Description:   Transmits a data byte over the I2C bus.
* Input: -byte: Data byte to transmit.
* Output: None
*/
void I2c_Transmit(uint8_t byte)
{
	// Send data byte
	I2C_SendData(I2Cx, byte);
	// Wait for I2C EV8_2.
	// It means that the data has been physically shifted out and 
	// output on the bus)
	/* TRA, BUSY, MSL, TXE and BTF flags */
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

 /*
* Function: I2c_Receive_Ack
* Description:   Receives a data byte from the I2C bus and acknowledges the reception.
* Input: None
* Output: return Received data byte.
*/
uint8_t I2c_Receive_Ack(void)
{
	// Enable ACK of received data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	 /* BUSY, MSL and RXNE flags */
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2Cx);
}

 /*
* Function: I2c_Receive_Nack
* Description:   Receives a data byte from the I2C bus without acknowledging the reception.
* Input: None
* Output: return Received data byte.
*/
uint8_t I2c_Receive_Nack(void)
{
	// Disable ACK of received data
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2Cx);
}