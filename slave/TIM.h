#ifndef __STM32L476R_NUCLEO_TIM_H
#define __STM32L476R_NUCLEO_TIM_H

void Timer_Init(void);
void SysTick_Handler(void);
unsigned int get_rand(unsigned int wall);

#endif
