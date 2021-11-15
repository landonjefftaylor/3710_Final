#ifndef __STM32L476R_NUCLEO_KEY_H
#define __STM32L476R_NUCLEO_KEY_H

void key_delay(void);
void key_init(void);
unsigned char scan_key(void);
unsigned char key_detect(void);
void scan_row(unsigned int* row, unsigned int* col, unsigned int btns, unsigned int colnum, unsigned int i);
unsigned char get_time(void);
void wait_for_pound(void);

#endif
