#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "TIM.h"
#include "TASK.h"

#define GAME_TIME 60

int main(void){
	USART2_Init(); // USB
	USART3_Init(); // SLAVE
	Timer_Init();
	
	uint8_t buffer[2]; // BUFFER
	uint8_t game_id[1]; // LEVEL NUMBER
	
	
	buzz((double)220.0f,2);
	buzz((double)330.0f,2);
	buzz((double)440.0f,2);
	
	// Handshake with slave
	usart_delay();
	
	USART_Clear(USART2); // Clear screen
	
	USART_Write(USART3, (uint8_t*) "II", 2); // note to self: only 2 characters seem to work for now

	USART_Read(USART3, buffer, 2);
	if (buffer[0] != 'I' || buffer[1] != 'I') {
		USART_Write(USART2, (uint8_t*) "THERE WAS AN ERROR WITH II. RESTART SLAVE, THEN RESTART MASTER", 100);
		return 1;
	}
	
	// Welcome screen for player 1
	USART_Clear(USART2); // Print welcome screen
	USART_Write(USART2, (uint8_t*) "WELCOME TO SPACE THINGY\r\n", 80);
	USART_Write(USART2, (uint8_t*) "***********************\r\n", 80);
	USART_Write(USART2, (uint8_t*) "ENTER YOUR GAME NUMBER(0-9):\r\n\n", 80);
	
	USART_Read(USART2, game_id, 1); // read in level number
	USART_Write(USART2, (uint8_t*) "PROCESSING...\r\n", 80); // Tell the user we're winding
	
	setGame((int) game_id[0] - 48);
	buffer[1] = game_id[0]; // Send game select signal, 'I_' where _ is the level number
	USART_Write(USART3, buffer, 2);
	
	wind(GAME_TIME); // Wind output timer
	
	USART_Clear(USART2); // Prompt level begin
	USART_Write(USART2, (uint8_t*) "PRESS ANY KEY TO COMMENCE MISSION.\r\n", 80);
	USART_Read(USART2, buffer, 1); // 
	USART_Clear(USART2);
	
	// handshake again with slave
	USART_Write(USART3, (uint8_t*) "IG", 2);
	USART_Read(USART3, buffer, 2);
	if (buffer[0] != 'I' || buffer[1] != 'G') {
		USART_Write(USART2, (uint8_t*) "THERE WAS AN ERROR WITH IG. RESTART SLAVE, THEN RESTART MASTER", 100);
		return 1;
	}
	
	set_timer(GAME_TIME); 
	while (1) taskMaster();
}


