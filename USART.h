#ifndef USART_H
#define USART_H
#define BUFFER_SIZE 20



void copy_buff(uint8_t *nbuffer);
void System_Clock_Init(void);
void USART_Init(USART_TypeDef * USARTx);
void USART2_Init(void);
void USART3_Init(void);
//void EXTI11_Init(void);
void USART_IRead(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t *pCounter);
void USART_PRead(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes);
//void USART_IWrite(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t *pCounter);
void USART_PWrite(USART_TypeDef * USARTx, uint8_t *buffer, int nBytes);
void UART3_IRQHandler(void);
void usart_delay(void);
//void public_send(USART_TypeDef *USARTx, uint8_t *buffer);

#endif
