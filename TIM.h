#ifndef __STM32L476R_NUCLEO_TIM_H
#define __STM32L476R_NUCLEO_TIM_H

void Timer_Init(void);
void SysTick_Handler(void);
void Set_Time_Zero(void);
void buzz(void);
void set_state(unsigned int s);
void set_timer(unsigned int s);
void buzz_delay(void);

void wind_delay(void);
void reward_time(unsigned int secs);
void penalty_time(unsigned int secs);
unsigned int get_timer(void);

/*
int state;
int step;
int timer;
	*/
#endif
