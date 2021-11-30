#ifndef __STM32L476R_NUCLEO_TIM_H
#define __STM32L476R_NUCLEO_TIM_H

void Timer_Init(void);
void SysTick_Handler(void);
void Set_Time_Zero(void);
void buzz(volatile double hz, volatile unsigned int tsec);
void set_state(unsigned int s);
void set_timer(unsigned int s);
void buzz_delay(volatile unsigned int t);

void wind_delay(void);
void wind(unsigned int secs);
unsigned int get_timer(void);

unsigned int get_rand(unsigned int wall);

/*
int state;
int step;
int timer;
	*/
#endif
