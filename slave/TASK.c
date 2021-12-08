#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"
#include "KEY.h"

// Player 1 has the buttons
// Each button is pulled up with a 2.2k resistor
static uint8_t* player1[16] = { 
	"Press the red button", // 0
	"Press the blue button", // 1
	"Press the green button", // 2
	"Press the yellow button", // 3
	"Press the black button" // 4
	/*"Flip the switch", // 5
	"Press the ", // 6
	"Press the ", // 7
	"Press the ", // 8
	"Press the ", // 9
	"Press the ", // 10
	"Press the ", // 11
	"Press the ", // 12
	"Press the ", // 13 
	"Press the ", // 14
	"Press the "  // 15*/
};

// Player 2 has the keypad
static uint8_t* player2[16] = { 
	"Press the 0 key", // 0
	"Press the 1 key", // 1
	"Press the 2 key", // 2
	"Press the 3 key", // 3
	"Press the 4 key", // 4
	"Press the 5 key", // 5
	"Press the 6 key", // 6
	"Press the 7 key", // 7
	"Press the 8 key", // 8
	"Press the 9 key", // 9
	"Press the A key", // 10
	"Press the B key", // 11
	"Press the C key", // 12
	"Press the D key", // 13 
	"Press the # key", // 14
	"Press the * key"  // 15
};

static uint8_t player1_com = 0;
static uint8_t player2_com = 0;
static uint8_t points = 0;

// Task Slave Function
void taskSlave(void) {
	uint8_t buffer[2] = {0};
	USART_Read(USART3, buffer, 2);
	//USART_Write(USART2, buffer, 2); // confirm the command
	
	if (buffer[0] == 'X') {
		USART_Write(USART2, (uint8_t*) "I AM HERE\r\n", 80);
		end_game();
	}
	
	if (buffer[0] != '$') {
		// set the command for player 1
		player1_com = buffer[0] - 48;
	}
	if (buffer[1] != '$') {
		// set the command for player 2
		player2_com = buffer[1] - 48;
		
		// write the command to the screen
		USART_Clear(USART2);
		USART_Write(USART2, buffer, 2);
		USART_Write(USART2, player2[player2_com], 80);
	}
	
	while (player1_com < 250 && player2_com < 250) { // Loop until a player has done an input
		
		// Scan the keypad once
		
		uint8_t key_pressed = 0;
		key_pressed = scan_key();
		if (key_pressed != 0) { // if a key press is detected
			if (key_pressed == player2_com + 48) { // if right key is pressed
				USART_Write(USART3, (uint8_t*) "$y", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT KEY! NICELY DONE!", 80);
				player2_com = 250;
				points++;
			}
			else { // if wrong key is pressed
				USART_Write(USART3, (uint8_t*) "$n", 2);
				USART_Write(USART2, (uint8_t*) "INCORRECT KEY! YOU IMBECILE!", 80);
				player2_com = 250;
			}
		}
		
		// Check the button inputs
		
		if ((GPIOB->IDR | 0xFFFFFFFE) == 0xFFFFFFFE) { // red_btn_pressed PB0 
			while ((GPIOB->IDR | 0xFFFFFFFE) == 0xFFFFFFFE);
			if (player1_com == 0) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				player1_com = 250;
				points++;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				player1_com = 250;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFF7) == 0xFFFFFFF7) { // blue btn is PB3
			while ((GPIOB->IDR | 0xFFFFFFF7) == 0xFFFFFFF7);
			if (player1_com == 1) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				player1_com = 250;
				points++;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				player1_com = 250;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFFB) == 0xFFFFFFFB) { // green btn is PB2
			while ((GPIOB->IDR | 0xFFFFFFFB) == 0xFFFFFFFB);
			if (player1_com == 2) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				player1_com = 250;
				points++;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				player1_com = 250;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFFD) == 0xFFFFFFFD) { // yellow btn is PB1
			while ((GPIOB->IDR | 0xFFFFFFFD) == 0xFFFFFFFD);
			if (player1_com == 3) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				player1_com = 250;
				points++;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				player1_com = 250;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFDFF) == 0xFFFFFDFF) { // black is PB9
			while ((GPIOB->IDR | 0xFFFFFDFF) == 0xFFFFFDFF);
			if (player1_com == 4) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				player1_com = 250;
				points++;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				player1_com = 250;
			}
		}
	} // while breakout loop
}

void end_game(void) {
	USART_Clear(USART2);
	uint8_t buffer[1] = {0};

	// break points into digits
	uint8_t pointage[3] = {'e', 'e', 'e'};
	
	uint8_t hundreds = points / (uint8_t) 100;
	points -= (100*hundreds);
	uint8_t tens = points / 10;
	uint8_t ones = points % 10;
	
	pointage[0] = hundreds + 48;
	pointage[1] = tens + 48;
	pointage[2] = ones + 48;
	
	//USART_Write(USART3, pointage, 3);
	
	USART_Write(USART2, (uint8_t*) "CONGARTULATIONS\r\n", 80);
	USART_Write(USART2, (uint8_t*) "YOUR SCORE IS\r\n", 80);
	USART_Write(USART2, pointage, 3);
	USART_Write(USART2, (uint8_t*) "POINTS!\r\n\r\n", 80);
	USART_Write(USART2, (uint8_t*) "RESET SLAVE THEN MASTER TO REPLAY\r\n", 80);
	
	while (1);
}
