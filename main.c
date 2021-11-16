#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "TIM.h"

int main(void){
	USART2_Init();
	//ADC1_Init();
	Timer_Init();
	
	uint8_t buffer[2];
	uint8_t b[50];
	
	set_timer(120);
	
	USART_Write(USART2, (uint8_t*) "Type your name: ", 100);
	USART_Read(USART2, b, 6);
	if (b[0] == 'l' && b[1] == 'a' && b[2] == 'n' && b[3] == 'd' && b[4] == 'o' && b[5] == 'n') {
		USART_Write(USART2, (uint8_t*) "Correct. 5 second reward. ", 100);
		USART_Write(USART2, b, 10);
		reward_time(5);
	}
	else {
		USART_Write(USART2, (uint8_t*) "Incorrect. 5 second penalty. ", 100);
		USART_Write(USART2, b, 10);
		penalty_time(5);
	}
		
	while(1) {
		USART_Read(USART2, buffer, 1);
		if (buffer[0] == 'r' || buffer[0] == 'T') {
			//float temp = Get_Temp();
			//char tempstr[80];
			//sprintf(tempstr, "temp is %f degrees. ", temp);
			USART_Write(USART2, (uint8_t*) "start wind ", 50);
			reward_time(4);
			USART_Write(USART2, (uint8_t*) "wind 4 seconds. ", 50);
		}
		if (buffer[0] == 'p' || buffer[0] == 'P') {
			USART_Write(USART2, (uint8_t*) "start wind ", 50);
			penalty_time(3);
			USART_Write(USART2, (uint8_t*) "wind 3 seconds. ", 50);
		}
	}
	
	while(1);

}


