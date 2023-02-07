#include "Speaker.h"

inline void speaker_init() {
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER4_0;
}
inline void speaker_reset(void) {
    GPIOA->ODR &= GPIO_ODR_0;
}
extern inline void my_delay(volatile uint32_t count)
{
	while(count>0)
	{
		count--;
		__NOP();
	}
}
inline void speaker_squeak_hz(double sec, double hz) {
    uint32_t t = SECOND * sec;
    uint32_t T = (double)SECOND / hz;// * 7.19;
    uint32_t loops = (double)t / T;
    T /= 2;
    while(loops--) {
        GPIOA->ODR |= GPIO_ODR_4;
     my_delay(T);
     GPIOA->ODR &= GPIO_ODR_0;
     my_delay(T);
    }
}