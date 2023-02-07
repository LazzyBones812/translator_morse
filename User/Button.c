#include "Button.h"

Button* CreateButton(char* name, int x, int y, int back_color, int text_color, void (*event)())
{
	Button* button = (Button*) malloc((sizeof(Button)));
	button->x = x;
	button->y = y;
	button->text_color = text_color;
	button->back_color = back_color;
	button->name = name;
	button->on_click = event;
	return button;
}