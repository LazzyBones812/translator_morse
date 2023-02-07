#ifndef __AsciiLib_H
#define __AsciiLib_H  

/**
@file 
@brief заголовочный шрифты LCD
*/

/**
@brief заголовочные шрифты LCD
*/
#include <string.h>

/**
@brief Готический шрифт
*/
#define  ASCII_8X16_MS_Gothic 
//#define  ASCII_8X16_System  ///<Системный шрифт	

void GetASCIICode(unsigned char* pBuffer,unsigned char ASCII);

#endif 
