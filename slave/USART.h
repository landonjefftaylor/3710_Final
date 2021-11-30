#ifndef USART_H
#define USART_H
//#include "stm32l412xx.h"
//void ADC1_Wakeup();
void USART_Init(USART_TypeDef * USARTx);
void USART2_Init(void);
void USART3_Init(void);
void USART_Read(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes);
void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes);
void usart_delay(void);
void System_Clock_Init(void);
void USART_Clear(USART_TypeDef * USARTx);
#endif
