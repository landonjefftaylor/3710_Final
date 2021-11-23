#include "stm32l476xx.h"
#include "USART.h"
//#include "ADC.h"

int main(void){
	uint8_t nbuffer[BUFFER_SIZE];
	USART2_Init();
	USART3_Init();
	copy_buff(nbuffer);
	//ADC1_Init();
	
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
		// Should read to the buffer automagically
		USART_PWrite(USART2, nbuffer, 12);
		usart_delay();
	}
}


