#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"
#include "TIM.h"

int main(void){
	USART2_Init();
	//ADC1_Init();
	Timer_Init();
	
	uint8_t buffer[2];
	
	set_timer(30);
	
	while(1) {
		USART_Read(USART2, buffer, 1);
		if (buffer[0] == 't' || buffer[0] == 'T') {
			//float temp = Get_Temp();
			//char tempstr[80];
			//sprintf(tempstr, "temp is %f degrees. ", temp);
			USART_Write(USART2, (uint8_t*) "start wind ", 50);
			wind(10);
			USART_Write(USART2, (uint8_t*) "wind 10 seconds. ", 50);
		}
	}
	
	
	
	while(1);

}


