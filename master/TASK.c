#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"
static uint8_t* player1[16] = {
	"Press the 0 key",
	"Press the 1 key",
	"Press the 2 key",
	"Press the 3 key",
	"Press the 4 key",
	"Press the 5 key",
	"Press the 6 key",
	"Press the 7 key",
	"Press the 8 key",
	"Press the 9 key",
	"Press the A key",
	"Press the B key",
	"Press the C key",
	"Press the D key",
	"Press the # key",
	"Press the * key",
};

void taskMaster(void){
	uint8_t task1 = get_rand(15);
	uint8_t task2 = get_rand(15);
	
	uint8_t buffer[2]; //= {48 + task1, 48 + task2}; // convert random nuymbers to tasks and storre them, in buffer
	
	usart_delay();
	USART_Write(USART3, (uint8_t*) "$0", 2); // Send over the two instructions to scan
	USART_Read(USART3, buffer, 2);
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
