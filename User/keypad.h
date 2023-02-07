/*keypad.h*/
#ifndef KEYPAD_H
#define KEYPAD_H
/**
@file
@brief обработка нажатий на кнопки
*/

/**
@brief инициализация кнопок для обработки нажатий
*/
void Init_keypad(void);
/**
@brief определяем на какую кнопку нажали
*/
unsigned int keypad_poll(void);

#endif
