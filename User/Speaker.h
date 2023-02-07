#ifndef SPEAKER_H
#define SPEAKER_H
#include "main.h"

#define SECOND 72000000


extern inline void my_delay(volatile uint32_t count);
extern inline void delay_sec(double sec);
void speaker_init();
void speaker_squeak_hz(double sec, double hz);
void speaker_reset(void);
#endif
