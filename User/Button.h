#ifndef BUTTON_H
#define BUTTON_H

#include <cstdlib>
#include <string.h>

typedef struct {
	int x;
	int y;
	int back_color;
	int text_color;
	char* name;
	void (*on_click) ();
} Button;

extern Button* CreateButton(char* name, int x, int y, int back_color, int text_color, void (*event)());

#endif
