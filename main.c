#include "stm32l476xx.h"
#include "USART.h"
//#include "ADC.h"

int main(void){
	USART2_Init();
	USART3_Init();
	//ADC1_Init();
	
	uint8_t buffer[20];
	
	/*while(1) {
		USART_Read(USART2, buffer, 1);
		if (buffer[0] == 't' || buffer[0] == 'T') {
			float temp = Get_Temp();
			
			char tempstr[80];
			sprintf(tempstr, "temp is %f degrees. ", temp);
			
			USART_Write(USART2, (uint8_t*) tempstr, 50);
		}
	}*/
	
	
	
	while(1){ // Only reading/sending one at a time to the console
		USART_Read(USART3, buffer, 12);
		USART_Write(USART2, buffer, 12);
		usart_delay();
	}
}


