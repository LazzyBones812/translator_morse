/*display.h*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f3xx_it.h"

void Init_display(void);
void draw_handler(void);
void presskey(unsigned short numkey);
void upkey(unsigned short numkey);
void printrecvstr(void);
void LCDlinestr(char* str, int16_t,uint16_t, uint16_t);

#endif
