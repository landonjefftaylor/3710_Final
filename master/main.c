#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "TIM.h"
#include "TASK.h"

int main(void){
	USART2_Init(); // USB
	USART3_Init(); // SLAVE
	Timer_Init();
	uint8_t buffer[2]; // BUFFER
	uint8_t game_id[1]; // LEVEL NUMBER
	
	// Handshake with slave
	usart_delay();
	USART_Write(USART3, (uint8_t*) "II", 2); // note to self: only 2 characters seem to work for now
	usart_delay();
	while(buffer[0] != 'I' || buffer[1] != 'I'){
		USART_Read(USART3, buffer, 2);
	}
	
	
	// Initialize level start
	USART_Clear(USART2); // Print welcome screen
	USART_Write(USART2, (uint8_t*) "WELCOME TO SPACE THINGY\r\n", 80);
	USART_Write(USART2, (uint8_t*) "***********************\r\n", 80);
	USART_Write(USART2, (uint8_t*) "ENTER YOUR GAME NUMBER:\r\n\n", 80);
	
	USART_Read(USART2, game_id, 1); // read in level number
	
	buffer[1] = game_id[0]; // Send game select signal, 'I_' where _ is the level number
	USART_Write(USART3, buffer, 2);
	wind(40); // Wind output timer
	
	USART_Clear(USART2); // Prompt level begin
	USART_Write(USART2, (uint8_t*) "PRESS ANY KEY TO COMMENCE MISSION.\r\n", 80);
	USART_Read(USART2, buffer, 1); // 
	USART_Clear(USART2);
	USART_Write(USART3, (uint8_t*) "IG", 2);
	 
	taskMaster();
	while(1);
}


