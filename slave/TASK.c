#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"
#include "KEY.h"

/*
void taskMaster(void) {
	unsigned int task1 = get_rand(27);
	unsigned int task2 = get_rand(25) + 2;
	while (1) {
		uint8_t task2_send[1];
		task2_send[0] = (uint8_t) task2;
		USART_Write(USART3, task2_send, 1);
		while (task2_send[0] != ':') USART_Read(USART3, task2_send, 1); // wait for slave to confirm receipt
		uint8_t response[2];
		response[0] = 0; // 0 means no input gotten yet
		response[1] = 0;
		USART_Read(USART3, response, 2);
		if (response[0] == 'n') { // failed action 0
			// give a penalty
			task1 = get_rand(27);
			task2 = get_rand(25) + 2;
		}
		if (response[0] == 'y') {
			// give a reward
			task1 = get_rand(27);
		}
		if (response[1] == 'y') {
			// give a reward
			task2 = get_rand(25) + 2;
		}
	}
}

void taskSlave(void) {
	uint8_t task2_number[1];
	while (1) {
		USART_Clear(USART2); //clear the console
		USART_Read(USART3, task2_number, 1);
		USART_Write(USART2, inputs[game_id][task2_number], 100);
		// need to set up input strings based on game ids
	}
	while (1) {
		scan_key();
	}
}
*/

// READ 27.3 Random Number Genrateor RNG

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

/* TASK LIST
PB0-9
Key 0
Key 1
Key 2
Key 3
Key 4
Key 5
Key 6
Key 7
Key 8
Key 9
Key A (10)
Key B (11)
Key C (12)
Key D (13)
Key # (14)
Key * (15)
a: Switch (16)
b: Photoresistor 1 (17)
PC0-9
c: Green button (18)
d: Red button (19)
e: Yellow button (20)
f: Blue button (21)
g: Black button 1 (22)
h: Black button 2 (23)
i: Tilt switch (24)
j: Photoresistor 2 (25)
k: Infrared wand ??? (26)
l: Potentiometer (27)

*/
