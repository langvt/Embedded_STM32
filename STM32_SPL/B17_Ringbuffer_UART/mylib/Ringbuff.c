#include "Ringbuff.h"

void ring_buff_init(RingBuff  *ring_buff, uint8_t *buff, uint16_t len)
{
	ring_buff ->buffer = buff;
	ring_buff ->pHead = 0;
	ring_buff->pTail = 0;
	ring_buff->maxlen = len;
}

int8_t ring_buff_push(RingBuff *ring_buff, uint8_t data)
{
	uint16_t next;
	next = ring_buff->pHead + 1;
	if(next >= ring_buff->maxlen) // when pHead at the end of  ring buffer
	{
		next == 0;
	}
	if(next == ring_buff ->pTail) // ring buffer is full
	{
		return -1;
	}
	
	ring_buff ->buffer[ring_buff->pHead] = data ; // load data and then move
	ring_buff ->pHead = next;
	return 0;
} 

int8_t ring_buff_pop(RingBuff *ring_buff, uint8_t *data)
{
	uint16_t next;
	
	if(ring_buff->pHead == ring_buff->pTail) // the ring buff is empty
	{
		return -1;
	}
	
	next = ring_buff->pTail + 1;
	
	if(next >= ring_buff->maxlen)
	{
		next = 0;
	}
	*data = ring_buff->buffer[ring_buff->pTail]; // read data and then move
	ring_buff ->pTail = next;
	
	return 0;
}

uint16_t ring_buff_available(RingBuff *ring_buff)
{
	if (ring_buff->pHead < ring_buff ->pTail)
	{
		return ring_buff->maxlen - (ring_buff ->pTail - ring_buff ->pHead);
	}
	else 
	{
		return ring_buff ->pHead - ring_buff ->pTail;
	}
}