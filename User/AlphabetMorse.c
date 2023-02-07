#include "AlphabetMorse.h"

Button** morse_buttons = NULL;

char supported_characters[26] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
    'P','Q','R','S','T','U','V','W','X','Y','Z'
};
char morse_code[26][5] = {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---", "-.-",
    ".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
};

int x_for_input_word = 0;
int y_for_input_word = 230;
char word_for_translator_Morse[512];


int morse_last_color_button = LCD_COLOR_LIME;
int morse_buttons_count = 26;
int morse_selected_button = 0;

void morse_input_symbol_on_display()
{
	x_for_input_word+=10;
	render_message(morse_buttons[morse_selected_button]->name, x_for_input_word, y_for_input_word, 10, LCD_COLOR_BLACK);
	strcat(word_for_translator_Morse, morse_buttons[morse_selected_button]->name);
}

void morse_init_buttons()
{
	if(morse_buttons != NULL)
		return;
	morse_buttons = (Button**) malloc((sizeof(Button) * morse_buttons_count));
	morse_buttons[0] = CreateButton("A", 30, 60, LCD_COLOR_RED, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[1] = CreateButton("B", 60, 60, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[2] = CreateButton("C", 90, 60, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[3] = CreateButton("D", 120, 60, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[4] = CreateButton("E", 150, 60, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[5] = CreateButton("F", 180, 60, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[6] = CreateButton("G", 30, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[7] = CreateButton("H", 60, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[8] = CreateButton("I", 90, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[9] = CreateButton("J", 120, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[10] = CreateButton("K", 150, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[11] = CreateButton("L", 180, 80, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[12] = CreateButton("M", 30, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[13] = CreateButton("N", 60, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[14] = CreateButton("O", 90, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[15] = CreateButton("P", 120, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[16] = CreateButton("Q", 150, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[17] = CreateButton("R", 180, 100, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[18] = CreateButton("S", 30, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[19] = CreateButton("T", 60, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[20] = CreateButton("U", 90, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[21] = CreateButton("V", 120, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[22] = CreateButton("W", 150, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[23] = CreateButton("X", 180, 120, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[24] = CreateButton("Y", 30, 140, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
	morse_buttons[25] = CreateButton("Z", 60, 140, LCD_COLOR_LIME, LCD_COLOR_BLACK, morse_input_symbol_on_display);
}
void morse_render_buttons()
{
	morse_init_buttons();
	
	for(int i = 0; i < morse_buttons_count; i++)
		render_button(
			morse_buttons[i]->name, morse_buttons[i]->x, morse_buttons[i]->y, 10, morse_buttons[i]->text_color, morse_buttons[i]->back_color);
}

void morse_start()
{	
	fill_screen(color(7));
	
	render_message("ALPHABET", 10, 20, 10, LCD_COLOR_BLACK);
	render_message("---------------------", 10, 40, 10, LCD_COLOR_BLACK);
	
	morse_render_buttons();
	
	render_message("---------------------", 10, 190, 10, LCD_COLOR_BLACK);
	render_message("INPUT WORD: ", 10, 210, 10, LCD_COLOR_BLACK);
}

void morse_select_button(int step)
{
	morse_buttons[morse_selected_button]->back_color = morse_last_color_button;
	
	morse_selected_button += step;
	if(morse_selected_button >= morse_buttons_count)
		morse_selected_button = 0;
	if(morse_selected_button < 0)
		morse_selected_button = morse_buttons_count-1;
	
	morse_last_color_button = morse_buttons[morse_selected_button]->back_color;
	morse_buttons[morse_selected_button]->back_color = LCD_COLOR_RED;
	
	morse_render_buttons();
}

void translate_sound()
{
	for(int i=0;i<strlen(word_for_translator_Morse);i++)
	{
		for(int j=0;j<36;j++)
		{
			if(word_for_translator_Morse[i] != supported_characters[j])
				continue;
			for(int k=0;k<strlen(morse_code[j]);k++)
			{
				if(morse_code[j][k] == '.')
				{
					speaker_squeak_hz(0.01f, 10000);
					my_delay(1000000);
				}
				else if(morse_code[j][k] == '-')
				{
					speaker_squeak_hz(0.03f, 7000);
					my_delay(1000000);
				}
			}
			my_delay(2000000);
		}
	}
}

void morse_input(uint32_t code)
{
	switch (code) {
		case 6: morse_select_button(-1); break;
		case 8: morse_select_button(1); break;
		case 3: morse_select_button(1); break;
		case 11: morse_select_button(-1); break;
		case 7: morse_buttons[morse_selected_button]->on_click(); break;
		
		case 13:translate_sound(); break;
	}
}
