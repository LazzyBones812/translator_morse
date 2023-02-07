#include "Render.h"

unsigned short int SCREEN_HEIGHT = 320;
unsigned short int SCREEN_WIDTH = 240;

void fill_screen(uint16_t color){
		int x = 0;
		for (x = 0; x < SCREEN_WIDTH; x++ ){
			int y;
			for(y = 0; y < SCREEN_HEIGHT; y++){
				lcd_set_pixel(x,y,color);
			}
		}
}


uint16_t color(char code){
	switch (code) {
		case 0 : return LCD_COLOR_BACKGROUND;
		case 3 : return LCD_COLOR_RED;
		case 2 : return LCD_COLOR_WHITE;
		case 4 : return LCD_COLOR_BLACK;
		case 1 : return LCD_COLOR_GRAY;
		case 5 : return LCD_COLOR_DARK_GREEN;
		case 6 : return LCD_COLOR_YELLOW;
		case 7 : return LCD_COLOR_LIME;
	}
	
	return ERROR_COLOR;
}


void render_message(char* message,int leftSpace,int y, int spacing,uint16_t color)
{
	size_t size=strlen(message);
	for (int i=0;i<size;i++)
	{
		prein_ascii(message[i], leftSpace,y,color);
		leftSpace=spacing+leftSpace;
	}
}
void render_button(char* message,int leftSpace,int y, int spacing,uint16_t textColor, uint16_t backColor)
{
	int sizeButton = strlen(message) * spacing + 20;
	
	for(int x = leftSpace; x < sizeButton + leftSpace; x++)
	{
		for(int _y = y-5; _y < 20 + y; _y++)
		{
			lcd_set_pixel(x, _y, backColor);
		}
	}
	
	size_t size=strlen(message);
	for (int i=0;i<size;i++)
	{
		prein_ascii(message[i], leftSpace + 10,y, textColor);
		leftSpace=spacing+leftSpace;
	}
}
