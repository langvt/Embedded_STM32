#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
//#include "system_stm32f10x.h"



volatile uint32_t msTicks = 0;

// GPIO confiig

void GPIO_Config(void){
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// 	// Nested vectored interrupt config

void NVIC_Config(void){

	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// TIM config

void TIM_Config(){
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM2 initialization for overflow every 1ms
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Prescaler = 64 -1;											// 64 000 000 hz        bo dao dong -> 1 000 000 hz/ 1s       -> 1000hz / 1ms
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1000 -1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// Start TIM2
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(){
	if(TIM_GetFlagStatus(TIM2, TIM_IT_Update) != RESET){
		
		msTicks ++;
		
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		}
	}



void Delay(uint32_t ms){
	uint32_t curTicks = msTicks;
	while( msTicks - curTicks  < ms);		
}

uint32_t millis(void){
    return msTicks;
}

// LED1

void LED1 (void) {
	
	uint8_t ledState1 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
	
	 ledState1 = !ledState1;
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, ledState1);
}


//LED2

void LED2 (void) {
	
	uint8_t ledState2 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_14);
	
	 ledState2 = !ledState2;
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, ledState2);
}


void LED3 (void) {
	
	uint8_t ledState3 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15);
	
	 ledState3 = !ledState3;
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_15, ledState3);
}
// struc task

typedef struct{
			void (*func)();
			uint32_t delay;
			uint32_t time ;
	}Task;

//taskInit
static void taskInit(Task *task){
		task->time = millis();
}

// MutilTask
void mutilTask(Task *task){
	
	
		 //taskInit(task);
	uint32_t current = millis();
	
	if((millis() - task->time) >= task->delay){
		
		//chuyen tang thaii LED
		task->func();
	
		//Cap nhat lai task->time = voii thoi gian cua millis() chuyen trang thai LED
		task->time = current;
	}
}

int main (){

	GPIO_Config();
	NVIC_Config();
	TIM_Config();
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	
	Task task1 = {&LED1, 500, 0 };
	Task task2 = {&LED2, 1000, 0};
	Task task3 = {&LED3, 2000, 0};
	
	while(1){
		mutilTask(&task1);
		mutilTask(&task2);
		mutilTask(&task3);
	}

	return 0;
}
