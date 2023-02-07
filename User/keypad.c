/*keypad.c*/
#include "keypad.h"
#include "main.h"

#define BT_TREPEAT 7   //время повторения символа при зажатой кнопки через 20 опросов
/**
@brief состояния кнопки
*/
typedef enum
{		/**начальное*/
    Key_init      = (0x00),
	  /**включена*/
    Key_down      = (0x01),
	  /**отключена*/
    Key_up        = (0x02),
	  /**переход от включена до отключена*/
    Key_dntoup    = (0x04),
	  /**переход от отключена до включена*/
    Key_uptodn    = (0x08),
	  /**долгое нажатие*/
    Key_dnlong    = (0x10),
    
} KEY_state;
/**
@brief УЗНАТЬ!!!
*/
typedef struct 
{
	KEY_state state;
    unsigned int downlongtick;
} KEY_type;

static KEY_type masKey[16];
static unsigned int kpd_pollcnt;


void Init_keypad() 
{
	kpd_pollcnt=0;
	for(uint32_t i=0;i<16;i++) {
		masKey[i].state=Key_init;
		masKey[i].downlongtick=0;
	}
	SET_BIT(RCC -> AHBENR, RCC_AHBENR_GPIOCEN);  //GPIOC
    
    CLEAR_BIT(GPIOC->MODER,0x0000FF00);	//PC4,5,6,7 In
	SET_BIT(GPIOC->PUPDR,0x00005500);//Pull up PC4,5,6,7
    
    SET_BIT(GPIOC->MODER,0x00000055);//PC0,1,2,3 Out
    SET_BIT(GPIOC->OTYPER,0x0000000F); //режим с открытым стоком
    SET_BIT(GPIOC->BSRR,0x0000000F);//z состояние
}
unsigned int keypad_poll()
{
	kpd_pollcnt++;
	uint32_t retcode=0;
	KEY_type* pcurKey;
	uint32_t i,j;
	for(i=0;i<4;i++) { /*столбцы*/
		SET_BIT(GPIOC->BRR,1<<i);
		for(j=0;j<4;j++) {/*строки*/
            for(int tmp=0;tmp<50;tmp++)
                __nop();
			pcurKey=&masKey[j*4+i];
			if(GPIOC->IDR&(1<<(4+j))) {/*up*/
				switch(pcurKey->state) {
					case Key_dntoup: 
						retcode|=1<<(j*4+i+16);//возвращаем флаг отжатия кнопки в старших 16 битах
					case Key_init:
					case Key_up:
					case Key_uptodn: 
						pcurKey->state=Key_up;
					break;
					case Key_down:
					case Key_dnlong: 
						pcurKey->state=Key_dntoup;
					break;
				}
			   
			}
			else {/*down*/
				switch(pcurKey->state) {
					case Key_init:
					case Key_dntoup: 
						pcurKey->state=Key_down;
					break;
					case Key_up:
						pcurKey->state=Key_uptodn;
					break;
					case Key_uptodn: 
						pcurKey->state=Key_down;
						retcode|=1<<(j*4+i);//возвращаем флаг нажатия кнопки в младших 16 битах
					break;
					case Key_down:
						pcurKey->state=Key_dnlong;
						pcurKey->downlongtick=kpd_pollcnt;
					break;
					case Key_dnlong:
						if((kpd_pollcnt-pcurKey->downlongtick)%BT_TREPEAT==0)
							retcode|=1<<(j*4+i);//возвращаем флаг нажатия кнопки
					break;
				}
			}
		}
		SET_BIT(GPIOC->BSRR,1<<i);
	}
	return retcode;
}
