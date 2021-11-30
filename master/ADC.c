#include "stm32l412xx.h"
#include "ADC.h"
#include "USART.h"

void ADC_Init(void) {
	return;
}

short get_cal(void) {
	//short* address = 0x1FFF75A8;
	//return *address;
	return 0;
}

void ADC1_Wakeup(void){
	volatile int wait_time;
	
	if((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD){
		ADC1->CR &= ~ADC_CR_DEEPPWD;
	}
	
	ADC1->CR |= ADC_CR_ADVREGEN;
	
	wait_time = 20 * (160000000 / 1000000);
	while(wait_time != 0){
		wait_time--;
	}
}

/*void ADC1_IRQHandler(void){
	if((ADC1->ISR & ADC_ISR_EOC) == AOC_ISR_EOC){
		temp = ADC1->DR;
	}
}*/

void ADC1_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN; // enable the clk
	ADC1->CR &= ~ADC_CR_ADEN; //s2
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN; //s3 //////////////////////////////////////////////////////////////
	ADC12_COMMON->CCR |= ADC_CCR_VREFEN; //s4
	
	ADC12_COMMON->CCR &= ~ADC_CCR_CKMODE; //set by us //s5
	ADC12_COMMON->CCR &= ~ADC_CCR_PRESC; //set precaler to 0, s5
	
	ADC12_COMMON->CCR |= ADC_CCR_CKMODE_0; //s6 should be mode 01
	
	ADC12_COMMON->CCR &= ~ADC_CCR_DUAL; //s7
	
	ADC1_Wakeup(); //s8
	
	ADC1->CFGR &= ~ADC_CFGR_RES; //s9, res is 12
	
	ADC1->CFGR &= ~ADC_CFGR_ALIGN; //s10 right align
	
	ADC1->SQR1 &= ~ADC_SQR1_L; //s11
	
	ADC1->SQR1 |= ADC_SQR1_SQ1_0; //s12
	ADC1->SQR1 |= ADC_SQR1_SQ1_4;
	ADC1->SQR1 &= ~ADC_SQR1_SQ1_1;
	ADC1->SQR1 &= ~ADC_SQR1_SQ1_2;
	ADC1->SQR1 &= ~ADC_SQR1_SQ1_3;
	
	//s13 skipped, already read only
	
	ADC1->SMPR2 |= ADC_SMPR2_SMP17; //s14 //fixed, was smpr1
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP17_1;
	
	ADC1->CFGR &= ~ADC_CFGR_CONT; //s15
	
	ADC1->CFGR &= ~ADC_CFGR_EXTEN; //s16
	
	ADC1->CR |= ADC_CR_ADEN; //s17
	
	ADC12_COMMON->CCR |= 0x00800000; // wake up, turn on ch 17
	
	while (ADC1->ISR & ADC_ISR_ADRDY); //s18
	
	//while (1);
}

float Get_Temp(void) {
	ADC1->CR |= ADC_CR_ADSTART; //s1
	while ((ADC12_COMMON->CSR & ADC_CSR_EOC_MST) == 0); //s2	
	volatile int wait_time = 20 * (160000000 / 1000000);
	while(wait_time != 0){
		wait_time--;
	}
	unsigned int temp = ADC1->DR;
	float calibrated_temp;
	unsigned short * ts_cal1 = 0x1FFF75A8;
	unsigned short * ts_cal2 = 0x1FFF75CA;
	
	/*char tempstr[80];
	sprintf(tempstr, "ts_cal1 is %d\n", *ts_cal1);	
	USART_Write(USART2, (uint8_t*) tempstr, 16);
	
	sprintf(tempstr, "ts_cal2 is %d\n", *ts_cal2);	
	USART_Write(USART2, (uint8_t*) tempstr, 16);
	
	sprintf(tempstr, "temp dr is %d\n", temp);	
	USART_Write(USART2, (uint8_t*) tempstr, 16);
	*/
	calibrated_temp = ((80.0) / ((float)*ts_cal2 - (float)*ts_cal1)) * ((float)temp - (float)*ts_cal1) + 80.0;
	return calibrated_temp;
}













