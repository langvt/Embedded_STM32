#include "flash.h"


void flashLock(void)
{
	FLASH_Lock();
}
void flashUnlock(void)
{
	FLASH_Unlock();
}
void flashErease(uint32_t Addr)
{
	flashUnlock();
	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
	FLASH_ErasePage(Addr);
	flashLock();
}

// a[] = {1, 2, 3, 4, 5, 6, 7, 8}
void flashWriteArr(uint32_t Addr, uint8_t *Data, uint16_t len)
{
	flashUnlock();
	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
	for(uint16_t i = 0; i < len; i+=2)
	{
		FLASH_ProgramHalfWord(Addr + i, Data[i] | ((uint16_t) Data[i+1] << 8));
	}
	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
	flashLock();
}


void flashReadArr(uint32_t Addr, uint8_t *Data, uint16_t len)
{

	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
	for(uint16_t i = 0; i < len; i+=2)
	{
//		volatile uint32_t *p = ( volatile uint32_t *)(Addr + i);
//		uint16_t DataTemp = *p;
		uint16_t DataTemp;
		DataTemp = *( volatile uint32_t*)(Addr + i);
		
		Data[i] = DataTemp;
		Data[i+1] = DataTemp >> 8;
	}
	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
}
