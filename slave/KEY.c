#include "stm32l476xx.h"
#include "KEY.h"

// Array of buttons
unsigned char keys[4][4] = { {'1', '2', '3', 'A'},
														 {'4', '5', '6', 'B'},
														 {'7', '8', '9', 'C'},
														 {'*', '0', '#', 'D'}
														};

// Values to check against rows
unsigned int rows[4] = {0xE0, 0xD0, 0xB0, 0x70};

// Hold your horses to help debounce button
void key_delay(void) { // debounce and delay
	volatile unsigned int t = 1600;
	while (t != 0) {
		t -= 1;
	}
}

// Wait for a column to go low
unsigned char scan_key(void) {
	GPIOB->ODR &= 0xFFFFFF0F;
	unsigned int btn1 = GPIOC->IDR & 0x1;
	unsigned int btn2 = GPIOC->IDR & 0x2;
	unsigned int btn3 = GPIOC->IDR & 0x4;
	unsigned int btn4 = GPIOC->IDR & 0x8;
	unsigned int btns = btn1 && btn2 && btn3 && btn4;
	if ( !btns ) {
		return key_detect();
	}
	else return 0;
}

// Check each column with a specific low row
void scan_row(unsigned int* row, unsigned int* col, unsigned int btns, unsigned int colnum, unsigned int i) {
	key_delay();	// wait
	unsigned int cols = GPIOC->IDR | btns; // check column 1
	key_delay();
	while (cols == btns) {
		*row = i;
		*col = colnum;
		cols = GPIOC->IDR | btns;
		if (cols != btns) return;
	}
}

// Find out which specific key was pressed
unsigned char key_detect(void) {
	unsigned int row = 3;
	unsigned int col = 3;
	key_delay();
	for (unsigned int i = 0; i < 4; i++) { // iterate through rows
		GPIOB->ODR &= 0xFFFFFF0F;
		GPIOB->ODR |= rows[i]; // 1110, enable R1		// enable an output row
		
		scan_row(&row, &col, 0xFFFFFFFE, 0, i); // check column 0
		scan_row(&row, &col, 0xFFFFFFFD, 1, i); // check column 1
		scan_row(&row, &col, 0xFFFFFFFB, 2, i); // check column 2
		scan_row(&row, &col, 0xFFFFFFF7, 3, i); // check column 3
		
		// check the input columns
		// if a button is pressed, return it
	}
	return keys[row][col];
}

unsigned char get_time(void) {
	//get time from user
	unsigned char time = 0;
	unsigned char d10 = 0;
	unsigned char d1 = 0;
	unsigned char dp = 0;
	while (1) {
		d10 = d1 * 10;
		d1 = dp;
		dp = scan_key();
		if (dp == '#' && (d1 || d10)) break;
	}
	time = d10 + d1;
	return time;
}

void wait_for_pound(void) {
	while (scan_key() != '#');
}


// Initialize the things
void key_init(void) {
	// set the clock to HSI clock at 16 MHz
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable clock
	// set the GPIOB->MODER 4 5 6 7 as outputs
	GPIOB->MODER &= 0xFFFF00FF;
	GPIOB->MODER |= 0x00005500;
	// set the output ports to open drain
	GPIOB->OTYPER |= 0x000000F0;
	GPIOB->ODR |= 0xF0;
	// set the GPIOC->MODER 0 1 2 3 as inputs
	GPIOC->MODER &= 0xFFFFFF00;
}
