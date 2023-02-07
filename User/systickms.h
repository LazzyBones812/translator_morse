/*systickms.h*/
#ifndef Systickms_H
#define Systickms_H

#include <stdint.h>

void Init_systickms(void);
typedef struct
{
	uint8_t (*readflag25ms)(void); 
	uint8_t (*readflag50ms)(void);
	void (*delayms)(uint16_t delaytime_t);	
	void (*cnt1ms)(void);
	uint32_t (*readcounter)(void);
}	
systickms_t;

extern systickms_t systickms;
#endif 
