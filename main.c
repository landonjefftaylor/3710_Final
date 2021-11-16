#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "TIM.h"

int main(void){
	USART2_Init();
	//ADC1_Init();
	Timer_Init();
	
	uint8_t buffer[2];
	
	set_timer(120);
	
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
			//float temp = Get_Temp();
			//char tempstr[80];
			//sprintf(tempstr, "temp is %f degrees. ", temp);
			USART_Write(USART2, (uint8_t*) "start wind ", 50);
			penalty_time(3);
			USART_Write(USART2, (uint8_t*) "wind 3 seconds. ", 50);
		}
	}
	
	while(1);

}


