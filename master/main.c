#include "stm32l476xx.h"
#include "USART.h"
#include "ADC.h"

int main(void){
	USART2_Init();
	USART3_Init();
	//ADC1_Init();
	
	USART_Write(USART3, (uint8_t*) "h", 50);
	
	/*
	
	USART_Clear(USART2);
	
	USART_Write(USART2, (uint8_t*) "WELCOME TO SPACE THINGY\r\n", 80);
	USART_Write(USART2, (uint8_t*) "***********************\r\n", 80);
	USART_Write(USART2, (uint8_t*) "ENTER YOUR GAME NUMBER:\r\n\n", 80);
	
	uint8_t game_id[1];
	USART_Read(USART2, game_id, 1);
	
	USART_Clear(USART2);
	
	//USART_Write(USART2, command, 1);
	//USART_Write(USART2, (uint8_t*) "[2J", 20);
	//USART_Write(USART2, command, 1);
	//USART_Write(USART2, (uint8_t*) "[H", 20);
	
	USART_Write(USART2, (uint8_t*) "PRESS ANY KEY TO START.\r\n", 80);
	
	USART_Read(USART2, buffer, 1);
	USART_Clear(USART2);
	
	USART_Write(USART2, (uint8_t*) "GAME WILL COMMENCE NOW.\r\n", 80);
	*/
	
	/*
	usart_delay();
	USART_Write(USART3, (uint8_t*) "aaaaaaaaaaaa", 12);
	usart_delay();
	USART_Write(USART3, (uint8_t*) "bbbbbbbbbbbb", 12);
	usart_delay();
	USART_Write(USART3, (uint8_t*) "cccccccccccc", 12);
	usart_delay();
	USART_Write(USART3, (uint8_t*) "dddddddddddd", 12);
	usart_delay();
	USART_Write(USART3, (uint8_t*) "eeeeeeeeeeee", 12);
	
	while (1) {
		//USART_Read(USART3, buffer, 12);
		usart_delay();
		USART_Write(USART3, (uint8_t*) "Hello uart\n", 12);
	}*/

		
		/*if (buffer[0] == 't' || buffer[0] == 'T') {
			float temp = Get_Temp();
			
			char tempstr[80];
			sprintf(tempstr, "temp is %f degrees. ", temp);
			
			unsigned char ones = (unsigned char) (temp % 10 + 0x30);
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
			tempstr[5] = '\n';
			
			USART_Write(USART2, (uint8_t*) tempstr, 50); 
		}*/	
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


