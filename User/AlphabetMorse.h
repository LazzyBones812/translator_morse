#ifndef ALPHABET_MORSE_H
#define ALPHABET_MORSE_H

#include "Render.h"
#include "Button.h"
#include "Speaker.h"

void morse_start();
void morse_input(uint32_t code);

void morse_init_buttons();
void morse_render_buttons();
void morse_select_button(int step);

#endif
