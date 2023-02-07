#ifndef __LCD_ILI9325_H
#define __LCD_ILI9325_H
/**
@file 
@brief основные функции для прорисовки 
*/
#include <stdint.h>
#include "AsciiLib.h"

/**
@brief ширина экрана 
*/
#define LCD_WIDTH 240 
/**
@brief высота экрана 
*/
#define LCD_HEIGTH 320

/**
@brief no comment
*/
void gpio_lcd_init(void);
/**
@brief no comment
*/
void init_lcd_ili9325(void);

/**
@brief заполнить область экрана, определенным цветом
@param x1, x2, y1, y2 - координаты для заполняемой области
@param colors_data - цвет области 
*/
void lcd_fill_region(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t *colors_data);
/**
@brief заполнить область экрана, определенным цветом
@param x1, x2, y1, y2 - координаты для заполняемой области
@param colors_data - цвет области !!!???
*/
void lcd_fill_color(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
/**
@brief заполнить пиксель на экране определенным цветом
@param x, y - координаты пикселя
@param color - цвет пикселя
*/
void lcd_set_pixel(int16_t x, int16_t y, uint16_t color);
/**
@brief вывод символа на экран по координатам 
@param x, y - координаты символа
@param color - цвет символа
*/
void prein_ascii(uint8_t ascii_simble, int x, int y, uint16_t color);

/**
@brief no comment
*/
inline uint16_t lcd_rgb565_convert(uint8_t red, uint8_t green, uint8_t blue)
{
    return (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3));
}

#define        LCD_RGB565_CONVERT_M(red, green, blue) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))


#define LCD_COLOR_BLACK 	LCD_RGB565_CONVERT_M(0x00, 0x00, 0x00)
#define LCD_COLOR_MAROON    LCD_RGB565_CONVERT_M(0x80, 0x00, 0x00)
#define LCD_COLOR_GREEN     LCD_RGB565_CONVERT_M(0x00, 0x80, 0x00)
#define LCD_COLOR_OLIVE     LCD_RGB565_CONVERT_M(0x80, 0x80, 0x00)
#define LCD_COLOR_NAVY      LCD_RGB565_CONVERT_M(0x00, 0x00, 0x80)
#define LCD_COLOR_PURPLE    LCD_RGB565_CONVERT_M(0x80, 0x00, 0x80)
#define LCD_COLOR_TEAL      LCD_RGB565_CONVERT_M(0x00, 0x80, 0x80)
#define LCD_COLOR_SILVER    LCD_RGB565_CONVERT_M(0xC0, 0xC0, 0xC0)
#define LCD_COLOR_GRAY      LCD_RGB565_CONVERT_M(0x80, 0x80, 0x80)
#define LCD_COLOR_RED       LCD_RGB565_CONVERT_M(0xFF, 0x00, 0x00)
#define LCD_COLOR_LIME      LCD_RGB565_CONVERT_M(0xFF, 0xFF, 0x00)
#define LCD_COLOR_BLUE      LCD_RGB565_CONVERT_M(0x00, 0x00, 0xFF)
#define LCD_COLOR_FUCHSIA   LCD_RGB565_CONVERT_M(0xFF, 0x00, 0xFF)
#define LCD_COLOR_AQUA      LCD_RGB565_CONVERT_M(0x00, 0xFF, 0xFF)
#define LCD_COLOR_WHITE     LCD_RGB565_CONVERT_M(0xFF, 0xFF, 0xFF)
#define LCD_COLOR_DARK_GREEN LCD_RGB565_CONVERT_M(0x00, 0x4A, 0x01)
#define LCD_COLOR_BACKGROUND LCD_RGB565_CONVERT_M(0xE1, 0xDC, 0xB5)
#define LCD_COLOR_YELLOW 		 LCD_RGB565_CONVERT_M(0xE1, 0xD6, 0x0D)

#endif
