#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "KEY.h"
#include "TIM.h"
#include "TASK.h"

// Remember pull up voltage for the keypad

int main(void){
	USART2_Init();
	USART3_Init();
	key_init();
	Timer_Init();
	
	uint8_t buffer[50] = {0};
	
	USART_Clear(USART2);
	
	// Handshake with master
	USART_Read(USART3, buffer, 2); // Read II
	if (buffer[0] != 'I' || buffer[1] != 'I') {
		USART_Write(USART2, (uint8_t*) "THERE WAS AN ERROR WITH II. RESTART SLAVE, THEN RESTART MASTER", 100);
		USART_Write(USART2, buffer, 2);
		return 1;
	}
	usart_delay();
	USART_Write(USART3, (uint8_t*) "II", 2);
	
	// Welcome screen for player 2
	USART_Write(USART2, (uint8_t*) "WELCOME TO SPACE THINGY\r\n", 80);
	USART_Write(USART2, (uint8_t*) "***********************\r\n", 80);
	USART_Write(USART2, (uint8_t*) "PLAYER 1 CHOOSES A MODE\r\n", 80);
	USART_Write(USART2, (uint8_t*) "YOU ARE PLAYER 2 ======)\r\n", 80);
	
	USART_Read(USART3, buffer, 2); // get game id, throw away for now
	set_mode(buffer[1] - 48);
	//USART_Write(USART2, buffer, 2);
	
	USART_Read(USART3, buffer, 2); // get IG confirmation
	//USART_Write(USART2, buffer, 2);
	if (buffer[0] != 'I' || buffer[1] != 'G') {
		USART_Write(USART2, (uint8_t*) "THERE WAS AN ERROR WITH IG. RESTART SLAVE, THEN RESTART MASTER", 100);
		return 1;
	}
	USART_Clear(USART2);
	
	// second handshake
	USART_Write(USART3, (uint8_t*) "IG", 2);
	
	while (1) taskSlave();
	
}

