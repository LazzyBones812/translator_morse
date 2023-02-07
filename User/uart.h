/*uart.h*/
#ifndef __UART_H
#define __UART_H

// UART Receiver buffer
#define RX_BUFSZ 350
// UART Transmitter buffer
#define TX_BUFSZ 350

void Init_UART2(void);
void transmitStr(unsigned char* poll);
unsigned short getRxpoll(unsigned char* buf);
void USART_TXEmpty_Callback(void); 
unsigned char rxstate(void);
void USART_CharTransmitComplete_Callback(void); 
void USART_CharReception_Callback(void); 
void USART_TransferError_Callback(void);


#endif
