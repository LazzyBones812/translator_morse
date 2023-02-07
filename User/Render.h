#ifndef RENDER_H
#define RENDER_H

#include "LCD_ILI9325.h"
#include "display.h"
#include <stdio.h>
#include <cstdlib>
#include "stm32f3xx_it.h"


#define BACKGROUND_COLOR LCD_COLOR_BLACK
#define ERROR_COLOR LCD_COLOR_AQUA
#define GRAY LCD_COLOR_GRAY

uint16_t color(char code);

void fill_screen(uint16_t);
void render_message(char* message,int leftSpace,int y, int spacing,uint16_t color);
void render_button(char* message,int leftSpace,int y, int spacing,uint16_t textColor, uint16_t backColor);

#endif
