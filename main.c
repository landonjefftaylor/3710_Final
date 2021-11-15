#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"

int main(void){
	USART2_Init();
	ADC1_Init();
	
	uint8_t buffer[2];
	
	while(1) {
		USART_Read(USART2, buffer, 1);
		if (buffer[0] == 't' || buffer[0] == 'T') {
			float temp = Get_Temp();
			
			char tempstr[80];
			sprintf(tempstr, "temp is %f degrees. ", temp);
			
			/*unsigned char ones = (unsigned char) (temp % 10 + 0x30);
			temp /= 10;
			unsigned char tens = (unsigned char) (temp % 10 + 0x30);
			temp /= 10;
			unsigned char hnds = (unsigned char) (temp % 10 + 0x30);
			temp /= 10;
			unsigned char thsn = (unsigned char) (temp % 10 + 0x30);
			temp /= 10;
			unsigned char tthn = (unsigned char) (temp % 10 + 0x30);
			
			unsigned char tempstr[6];	
			tempstr[0] = tthn;
			tempstr[1] = thsn;
			tempstr[2] = hnds;
			tempstr[3] = tens;
			tempstr[4] = ones;
			tempstr[5] = '\n';*/
			
			USART_Write(USART2, (uint8_t*) tempstr, 50);
		}
	}
	
	
	
	while(1);
	
	/*while (1) {
		USART_Read(USART2, buffer, 1);
		//usart_delay();
		USART_Write(USART2, (uint8_t*) buffer, 1);
	}*/
	
	//TS_CAL1 0x 18 04
	//TS_CAL2 0x 1E 05
	
	//while(1) {
		
		//USART_Read(USART2, buffer, 8);
		
		//if (buffer[0] == 'x') {
			//USART_Write(USART2, "hello", 8);
		//}
		
	//}
}


