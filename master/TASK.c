#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"

// Player 1 has the buttons
static uint8_t* player1[16] = { 
	"Press the red button ", // 0
	"Press the blue button ", // 1
	"Press the green button ", // 2
	"Press the yellow button ", // 3
	"Press the black button " // 4
};

// Player 2 has the keypad

// Task Master Function
void taskMaster(void){
	uint8_t task1 = 0 + 48; //(uint8_t) get_rand(4);
	uint8_t task2 = 0 + 48; //(uint8_t) get_rand(15);
	
	uint8_t buffer[2]; // store random tasks in buffer
	buffer[0] = task1;
	buffer[1] = task2;
	
	USART_Write(USART3, buffer, 2); // Send over the two instructions to scan
	
	//USART_Clear(USART2);
	USART_Write(USART2, player1[task1 - 48], 80); // print player 1 instructions
	
	USART_Read(USART3, buffer, 2); // Wait for a response from the slave
	
	if (buffer[0] != '$'){
		if(buffer[0] == 'y'){
			wind(10);
			USART_Write(USART2, (uint8_t*) "Hooray - we completed the p1 task!\r\n", 80);
		} else {
			USART_Write(USART2, (uint8_t*) "You suck balls - not p1 task completed\r\n", 80);
		}
	}
	if (buffer[1] != '$') {
		if(buffer[1] == 'y'){
			wind(10);
			USART_Write(USART2, (uint8_t*) "Hooray - we completed the p2 task!\r\n", 80);
		} else {
			USART_Write(USART2, (uint8_t*) "You suck balls - not p2 task completed\r\n", 80);
		}
	}
}

void end_game(void) {
	/*uint8_t pointage[3] = {'e', 'e', 'e'};
	uint8_t buffer[2] = {0};
	USART_Clear(USART2);
	
	USART_Write(USART2, (uint8_t*) "TIME'S UP! PRESS BLACK BUTTON TO SEE SCORE.\r\n", 80);
	USART_Read(USART3, buffer, 2);*/
	USART_Clear(USART2);
	USART_Write(USART2, (uint8_t*) "TIME'S UP! PRESS BLACK BUTTON TO SEE SCORE DISPLAYED ON PLAYER 2 SCREEN\r\n", 100);
	
	while(1){
		USART_Write(USART3, (uint8_t*) "XX", 2);
		usart_delay();
	}
	/*
	USART_Write(USART3, (uint8_t*) "XX", 2);
	
	USART_Read(USART3, pointage, 3);
	USART_Write(USART2, (uint8_t*) "\n\n\n", 3);
	
	USART_Write(USART2, (uint8_t*) "CONGARTULATIONS\r\n", 80);
	USART_Write(USART2, (uint8_t*) "YOUR SCORE IS\r\n", 80);
	USART_Write(USART2, pointage, 3);
	USART_Write(USART2, (uint8_t*) " POINTS!\r\n\r\n", 80);
	USART_Write(USART2, (uint8_t*) "RESET SLAVE THEN MASTER TO REPLAY\r\n", 80);
	while (1);*/
}

/* PSEUDOCODE FOR MASTER

Randomly pick two tasks, one in task[0] and one in task[1]
Send task[] to the slave module
Send task[0] to COM (slave will send task[1] to COM)
Wait for ok[] to come back or the timer to run out
If ok[0] or ok[1] is 'n':
	Give a task-appropriate penalty
	Update either one or both tasks
If ok[0] is 'y':
	Give a task-appropriate reward
	Update task[0] to a new random task
	Send task[new_task, '\0'] to slave module
If ok[1] is 'y'
	Give a task-appropriate reward
	Update task[1] to a new random task
	Send task['\0', new_task] to slave module


*/

/* PSEUDOCODE FOR SLAVE
Begin
	Loop forever:
		Scan keypad once
		If key pressed:
			Send back the character of the pressed key
		If switch flipped
			Save the state of the switch
			Send back 'a'
		If photoresistor 1 input goes low
			Send back 'b'
		If green button input goes low
			Send back 'c'
		If red button input goes low
			Send back 'd'
		If yellow button input goes low
			Send back 'e'
		If blue button input goes low
			Send back 'f'
		If black button 1 input goes low
			Send back 'g'
		If black button 2 input goes low
			Send back 'h'
		If tilt switch input goes low
			Send back 'i'
		If photoresistor 2 input goes low
			Send back 'j'
		If infrared sensor input goes high
			Send back 'k'
		If potentiometer input goes toggle
			Save the state of potentiometer input
			Send back 'l'
	Endloop
End	
*/