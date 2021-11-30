#include "BTN.h"
#include "TIM.h"
#include "stm32l476xx.h"

unsigned char state;

int get_state() {
	return state;
}

void Button_Init(void) {
	
	state = 0;
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable clock
	GPIOC->MODER &= 0xFFFFFFC0;
	//GPIOC->MODER |= 0x0000002A;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC;
	
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	
	EXTI->FTSR1 |= EXTI_FTSR1_FT0;
	EXTI->FTSR1 |= EXTI_FTSR1_FT1;
	EXTI->FTSR1 |= EXTI_FTSR1_FT2;
}

void debounce(void) {
	volatile unsigned int i = 160;
	while (i != 0) i--;
}

// Red
void EXTI0_IRQHandler(void) {
	debounce();
	Set_Time_Zero();
	LCD_DisplayString(0, (unsigned char*)"00:00.0");
	EXTI->PR1 |= EXTI_PR1_PIF0;
}

// Green
void EXTI1_IRQHandler(void) {
	debounce();
	state = 0;
	EXTI->PR1 |= EXTI_PR1_PIF1;
}

// Yellow
void EXTI2_IRQHandler(void) {
	debounce();
	state = 1;
	//while (1) SysTick->VAL = 0;
	EXTI->PR1 |= EXTI_PR1_PIF2;
}