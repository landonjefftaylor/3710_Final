#include "stm32l476xx.h"
#include "USART.h"

//uint32_t temp;

void USART_Init(USART_TypeDef * USARTx) {
	// from page 534
	USARTx->CR1 &= ~USART_CR1_UE; // turn off the usart to change settings
	USARTx->CR1 &= ~USART_CR1_M; // set data length to 8 bits 00
	USARTx->CR2 &= ~USART_CR2_STOP; // one stop bit
	USARTx->CR1 &= ~USART_CR1_PCE; // no parity
	USARTx->CR1 &= ~USART_CR1_OVER8; // oversample by 16
	USARTx->BRR = 0x683; // baud rate 9600, ex1 in sec 22.1.2
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE); // enable transmit and recv
	USARTx->CR1 |= USART_CR1_UE; // turn on the usart
	while ((USARTx->ISR & USART_ISR_TEACK) == 0); // wait until usart is ready to transmit
	while ((USARTx->ISR & USART_ISR_REACK) == 0); // wait until usart is ready to recieve
	int i;
	i = 0;
}

void System_Clock_Init(void) {
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );
}


void USART2_Init(void) {
	// set the clock to HSI clock at 16 MHz
	System_Clock_Init();
	
	// from page 535
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // clock for USART2
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // clock for GPIOA
	
	GPIOA->MODER &= 0xFFFFFFAF; // pins 2 and 3 in AF mode
	GPIOA->MODER |= 0x000000A0;
	
	GPIOA->AFR[0] |= 0x77 << (4*2); // pins 2 and 3 to AF7 or UART2 tx and rx
	
	GPIOA->OSPEEDR |= 0xF<<(2*2); // pins 2 and 3 in high speed 11 mode
	
	GPIOA->PUPDR &= ~(0xF<<(2*2));
	GPIOA->PUPDR |= 0x5 << (2*2); // pin 2 3 in pull-up mode
	
	//GPIOB->OTYPER &= 0xFFFFFFF3; // pin 2 3 in push pull mode
	
	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL); // use system clock
	RCC->CCIPR |=  (RCC_CCIPR_USART2SEL_0); // use system clock
	
	USART_Init(USART2);
}

void USART3_Init(void) {
	// set the clock to HSI clock at 16 MHz
	System_Clock_Init();
	
	// from page 535
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN; // clock for USART3
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // clock for GPIOC
	
	GPIOC->MODER &= 0xFFAFFFFF; // pins 10 and 11 in AF mode
	GPIOC->MODER |= 0x00A00000;
	
	GPIOC->AFR[1] |= 0x77 << (4*2); // pins 10 and 11 to AF7 or UART2 tx and rx
	
	GPIOC->OSPEEDR |= 0xF<<(2*10); // pins 10 and 11 in high speed 11 mode
	
	GPIOC->PUPDR &= ~(0xF<<(2*10));
	GPIOC->PUPDR |= 0x5 << (2*10); // pin 10 11 in pull-up mode
	
	//GPIOC->OTYPER &= 0xFFFFFFF3; // pC 10 and 11 in push pull mode
	
	RCC->CCIPR &= ~(RCC_CCIPR_USART3SEL); // use system clock
	RCC->CCIPR |=  (RCC_CCIPR_USART3SEL_0); // use system clock
	
	USART_Init(USART3);
}

void USART_Read(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes) {
	//page 536
	volatile int i; 
	for (i = 0; i < nBytes; i++) { // loop through each byte
		while (!(USARTx->ISR & USART_ISR_RXNE)); // wait until reciever not empty
		buffer[i] = USARTx->RDR; // read into buffer clear rxne
		if (buffer[i] == '\0') break;
	}
	usart_delay();
}

void usart_delay(void) {
	volatile int i = 0;
	for (i = 0; i < 1000; i++);
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes) {
	//page 536
	usart_delay();
	int i;
	for (i = 0; i < nBytes && buffer[i] != '\0'; i++) { // loop through each byte
		while ((USARTx->ISR & USART_ISR_TXE) == 0); // wait until transmitter empty
		USARTx->TDR = buffer[i] & 0xFF; // load buffer into transmit register
		//usart_delay();
	}
	while ((USARTx->ISR & USART_ISR_TC) == 0); // wait until transmit complete
	//USARTx->ICR |= 0x00000020; // set trasnmit complete clear changed from TCCF 
	USARTx->ISR &= ~USART_ISR_TC;
	//usart_delay();
}

void USART_Clear(USART_TypeDef * USARTx) {
	uint8_t command[1];
	command[0] = 27;
	
	USART_Write(USARTx, command, 1);
	USART_Write(USARTx, (uint8_t*) "[2J", 20);
	USART_Write(USARTx, command, 1);
	USART_Write(USARTx, (uint8_t*) "[H", 20);
}
