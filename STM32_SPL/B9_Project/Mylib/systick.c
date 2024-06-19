#include "systick.h"

volatile uint32_t msTick; // Global variable to store the tick count in milliseconds

/*
 * Function: SysTick_Handler
 * Description: Interrupt handler for the SysTick timer.
 * Input: None
 * Output: None
 * 
 * This function is called when the SysTick timer interrupt occurs. It increments the global
 * variable msTick, which is used for timekeeping.
 */
void SysTick_Handler(void)
{
    msTick++; // Increment the millisecond tick count
}


/*
 * Function: SystickInit
 * Description: Initializes the SysTick timer.
 * Input: None
 * Output: None
 * 
 * This function initializes the SysTick timer by configuring its clock source and frequency,
 * and enabling the SysTick interrupt.
 */
void SystickInit(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000); // Configure SysTick for 1 ms interrupts

		/*	SysTick->LOAD = 72 * 1000  - 1; 		// Set reload value for 1 ms interrupt
			SysTick ->VAL = 0;								// Initialize current value
			SysTick ->CTRL = 5;							// Enable SysTick with AHP clock source and interrupt (101 = 5)
																// Bit 2: Clock source
																// Bit 1: Tick interrupt enable when an interrupt event is triggered by the system
																// Bit 0: Enable SysTick
		while( ! (SysTick ->CTRL & (1 << 16))) // Wait until the SysTick counts down from 72000 to 0
		{
			// Wait for SysTick countdown
		}*/
	
	SysTick_Handler();
}


/*
 * Function: getTick
 * Description: Returns the current tick count.
 * Input: None
 * Output:
 *   - uint32_t: Current tick count in milliseconds.
 * 
 * This function returns the current tick count, which represents the number of milliseconds
 * since the system started.
 */
uint32_t getTick(void)
{
	return msTick;
}


/*
 * Function: getTick
 * Description: Returns the current tick count.
 * Input: None
 * Output:
 *   - uint32_t: Current tick count in milliseconds.
 * 
 * This function returns the current tick count, which represents the number of milliseconds
 * since the system started.
 */
void Delay_Ms(int time)
{
  uint32_t start = getTick(); // Get the current tick count
	
  while (getTick() - start <= time)
  {
     // Wait until the required time has elapsed
  }
}

