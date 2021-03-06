#include "TIM.h"
#include "stm32l476xx.h"

volatile unsigned int rand;

unsigned int get_rand(unsigned int wall) {
	return rand % wall;
}

void Timer_Init(void) {
	
	rand = 0;
	
	// set the clock to HSI clock at 16 MHz
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable clock
	
	unsigned int ticks = 58600; // 400k is to 0.1 as 58600 is to 1/68.26
	// The distance was 40ms, we want it to be 100
	
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); // Set priority to 2
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x00000007;

}

void SysTick_Handler(void) {
	rand++;
}
