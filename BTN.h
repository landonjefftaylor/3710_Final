#ifndef __STM32L476R_NUCLEO_BTN_H
#define __STM32L476R_NUCLEO_BTN_H

void Button_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
int get_state(void);

#endif
