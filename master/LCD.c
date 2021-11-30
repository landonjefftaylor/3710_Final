#include "LCD.h"
#include "stm32l476xx.h"

#define WAIT 2

void delay_ms(unsigned int ms) {
	volatile unsigned int t = 16 * ms; // 16000 cycles per ms
	while (t != 0) {
		t -= 1;
	}
}

void LCD_Pulse(void) {
	delay_ms(WAIT);
	GPIOB->ODR |= 0x00000200;
	delay_ms(WAIT);
	GPIOB->ODR &= 0xFFFFFDFF; //fall
	delay_ms(WAIT);
	GPIOB->ODR |= 0x00000200;
	delay_ms(WAIT);
}

void LCD_PutNibble(unsigned char c) {
	GPIOB->ODR &= 0xFFFFFFF0;
	GPIOB->ODR |= c;
	LCD_Pulse();
}


void LCD_WriteCom(unsigned char com) {
	GPIOB->ODR &= 0xFFFFFEFF; // turn off RS
	
	// send upper 4 bits
	LCD_PutNibble(com >> 4);
	// send lower 4 bits
	LCD_PutNibble(com & 0x0F);
	
	GPIOB->ODR |= 0x00000100; // turn on RS
}

void LCD_WriteData(unsigned char dat) {
	
	// send upper 4 bits
	LCD_PutNibble(dat >> 4);
	// send lower 4 bits
	LCD_PutNibble(dat & 0x0F);
	
}

void LCD_Init(void){
	// set the clock to HSI clock at 16 MHz
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock
	// set the GPIOB->MODER 0 1 2 3 8 9 as outputs
	GPIOB->MODER &= 0xFFF0FF00;
	GPIOB->MODER |= 0x00050055;
	delay_ms(WAIT);
	GPIOB->ODR &= 0xFFFFFFF0;
	GPIOB->ODR |= 0x00000300;
	delay_ms(WAIT);
	
	// check these commands against the manual
	LCD_WriteCom(0x28); // function
	delay_ms(WAIT);
	LCD_WriteCom(0x0C); // display switch
	delay_ms(WAIT);
	LCD_WriteCom(0x06); // input mode
	delay_ms(WAIT);
	LCD_WriteCom(0x01); // set cursor
	delay_ms(WAIT);
	LCD_WriteCom(0x14); // cursor shifting
	delay_ms(WAIT);
	LCD_WriteCom(0x40); // set CGRAM to 0
	delay_ms(WAIT);
	LCD_Clear();
}

void LCD_Clear(void){
  LCD_WriteCom(0x01); // clear screen function
	LCD_WriteCom(0x02); // return function
	delay_ms(WAIT *10);
	// LCD_WriteCom(0x40); // set up CGRAM to start at 0
}

void LCD_DisplayString(unsigned int line, unsigned char *ptr) {
	if (line == 0) {
		//ddram 1st line
		delay_ms(WAIT *10);
		LCD_WriteCom(0x80);
		delay_ms(WAIT *10);
	}
	else {
		//ddram 2nd line
		delay_ms(WAIT *10);
		LCD_WriteCom(0xC0);
		delay_ms(WAIT *10);
	}
	int i = 0;
	unsigned char c;
	do {
		c = ptr[i];
		LCD_WriteData(c);
		delay_ms(WAIT);
		i++;
	} while (ptr[i] != 0);
}



