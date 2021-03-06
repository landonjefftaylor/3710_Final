#include "TIM.h"
#include "TASK.h"
#include "stm32l476xx.h"

unsigned int gameCanO;
unsigned int timer;
unsigned int state;
unsigned int step;

volatile unsigned int rand;

void set_state(unsigned int s) {
	state = s;
}

void set_timer(unsigned int s) {
	timer = s * 68;
}

unsigned int get_timer(void) {
	return timer;
}

unsigned int get_rand(unsigned int wall) {
	return rand % wall;
}

void Timer_Init(void) {
	
	state = 0;
	timer = 0;
	step = 0;
	rand = 0;
	gameCanO = 0;
	
	//Set_Time_Zero();
	
	// set the clock to HSI clock at 16 MHz
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable clock
	
	unsigned int ticks = 586000; // 400k is to 0.1 as 58600 is to 1/68.26
	// The distance was 40ms, we want it to be 100
	
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); // Set priority to 2
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x00000007;
	
	GPIOB->MODER &= 0xFFFFFF55; //motor
	GPIOB->MODER |= 0x00000055;
	
	GPIOC->MODER &= 0xFFFFFCFF; // buzzer on C4
	GPIOC->MODER |= 0x00000100;
	
}

void SysTick_Handler(void) {
	// drive the motor
	rand++;
	if (timer) {
		gameCanO = 1;
		switch (step) {
			case 7: 
				GPIOB->ODR &= 0xFFFFFFF1; //A
				GPIOB->ODR |= 0x00000001; //A
				break;
			case 6: 
				GPIOB->ODR &= 0xFFFFFFF3; //AB
				GPIOB->ODR |= 0x00000003; //AB
				break;
			case 5: 
				GPIOB->ODR &= 0xFFFFFFF2; //B
				GPIOB->ODR |= 0x00000002; //B
				break;
			case 4: 
				GPIOB->ODR &= 0xFFFFFFF6; //BC
				GPIOB->ODR |= 0x00000006; //BC
				break;
			case 3: 
				GPIOB->ODR &= 0xFFFFFFF4; //C
				GPIOB->ODR |= 0x00000004; //C
				break;
			case 2: 
				GPIOB->ODR &= 0xFFFFFFFC; //CD
				GPIOB->ODR |= 0x0000000C; //CD
				break;
			case 1: 
				GPIOB->ODR &= 0xFFFFFFF8; //D
				GPIOB->ODR |= 0x00000008; //D
				break;
			case 0: 
				GPIOB->ODR &= 0xFFFFFFF9; //DA
				GPIOB->ODR |= 0x00000009; //DA
				break;
		}
		step++;
		if (step == 8) step = 0;
		timer--;
	}else if(gameCanO){
		end_game();
	}
}

void buzz_delay(volatile unsigned int t) { // debounce and delay
	while (t != 0) {
		t -= 1;
	}
}

// buzzer is on PC4
// tsec is number of tenths of seconds
void buzz(volatile double hz, volatile unsigned int tsec) {
	volatile double del = ((double)4.0f / hz) * 160000;
	volatile unsigned int t = (80000 * tsec) / (volatile unsigned int) del;
	while (t != 0) {
		GPIOC->ODR &= 0xFFFFFFEF;
		buzz_delay((volatile unsigned int) del);
		GPIOC->ODR |= 0x00000010;
		buzz_delay((volatile unsigned int) del);
		t--;
	}
}

void wind_delay(void) { // debounce and delay
	volatile unsigned int t = 3000;
	while (t != 0) {
		t -= 1;
	}
}

void wind(unsigned int secs) {
	volatile unsigned int ticks = 68 * (secs);
	// drive the motor
	while (ticks) {
		GPIOB->ODR &= 0xFFFFFFF1; //A
		GPIOB->ODR |= 0x00000001; //A
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF3; //AB
		GPIOB->ODR |= 0x00000003; //AB
		//step = 6;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF2; //B
		GPIOB->ODR |= 0x00000002; //B
		//step = 5;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF6; //BC
		GPIOB->ODR |= 0x00000006; //BC
		//step = 4;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF4; //C
		GPIOB->ODR |= 0x00000004; //C
		//step = 3;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFFC; //CD
		GPIOB->ODR |= 0x0000000C; //CD
		//step = 2;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF8; //D
		GPIOB->ODR |= 0x00000008; //D
		//step = 1;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
		GPIOB->ODR &= 0xFFFFFFF9; //DA
		GPIOB->ODR |= 0x00000009; //DA
		//step = 0;
		ticks--;
		wind_delay();
		if (ticks == 0) break;
	}
}

