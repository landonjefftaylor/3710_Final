#ifndef ADC_H
#define ADC_H

void ADC_Init(void);
short get_cal(void);
void ADC1_Wakeup(void);
void ADC1_IRQHandler(void);
void ADC1_Init(void);
float Get_Temp(void);

#endif
