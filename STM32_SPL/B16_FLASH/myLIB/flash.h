#ifndef FLASH_H
#define FLASH_H

#include "main.h"

void flashLock(void);
void flashUnlock(void);
void flashErease(uint32_t Addr);
void flashWriteArr(uint32_t Addr, uint8_t *Data, uint16_t len); 
void flashReadArr(uint32_t Addr, uint8_t *Data, uint16_t len); 

#endif
