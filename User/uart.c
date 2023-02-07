/*uart.c*/
#include "main.h"
#include <string.h>
#include "uart.h"
#include "systickms.h"

#define RX_TIMEOUT_MS 20

typedef enum
{/*состояние передачи*/
	TX_idle		= (0x00),/*бездействие*/
    TX_activ    = (0x01),/*активна*/
	TX_error	= (0x02),/*ошибка*/
} TX_state;
typedef enum
{/*состояние приёма*/
    RX_wait		= (0x00),/*ожидание*/
    RX_activ    = (0x01),/*приём*/
    RX_error	= (0x02),/*ошибка*/
} RX_state;

/* Buffer used for transmission */
__IO uint8_t Txbuf[TX_BUFSZ];
__IO uint8_t Txcnt = 0;
__IO TX_state TXstate = TX_idle;
__IO uint16_t TxIndex = 0;
/* Buffer used for reception */
__IO uint8_t Rxbuf[RX_BUFSZ]="\r\nUSART Example : Enter characters to fill reception buffers.\r\n";
__IO uint8_t Rxcnt = 62;
__IO RX_state RXstate = RX_wait;
__IO uint16_t RxIndex = 0;
__IO uint32_t Timeout = 0; /* Variable used for Timeout management */


static void transmitRxbuf()
{
	for(int i=0;i<Rxcnt;i++)
		Txbuf[i]=Rxbuf[i];
	Txcnt=Rxcnt;
	Rxcnt=0;
	/* Initiate transfers */
	/* Start USART transmission : Will initiate TXE interrupt after TDR register is empty */
	LL_USART_TransmitData8(USART2, Txbuf[TxIndex++]); 
	/* Enable TXE interrupt */
	LL_USART_EnableIT_TXE(USART2); 
	TXstate=TX_activ;
}

void transmitStr(unsigned char* poll)
{
	if(TXstate == TX_idle){
		int klen=strlen((char*)poll);
		if(klen>0){
			for(int i=0;i<klen;i++)
				Txbuf[i]=poll[i];
			Txcnt=klen;
			LL_USART_TransmitData8(USART2, Txbuf[TxIndex++]); 
			/* Enable TXE interrupt */
			LL_USART_EnableIT_TXE(USART2); 
			TXstate=TX_activ;
		}
	}
}

unsigned char rxstate(void)
{
	if(RXstate == RX_activ)
	{
		if( (systickms.readcounter()-Timeout) > RX_TIMEOUT_MS)
		{
			Rxcnt=RxIndex;
			RxIndex=0;
			RXstate=RX_wait;
			/* Disable RXNE interrupt */
			//LL_USART_DisableIT_RXNE(USART2);
			return 1;
		}
	}
	if(RXstate == RX_error || TXstate == TX_error)
	{
		//очищаем флаги ошибок
	}
	return 0;
}

unsigned short getRxpoll(unsigned char* buf)
{
	unsigned short retsz=0;
	if(Rxcnt>0){
		for(int i=0;i<Rxcnt;i++){
			buf[i]=Rxbuf[i];
		}
		retsz=Rxcnt;
		Rxcnt=0;
	}
	return retsz;
}
void Init_UART2(void)
{
	/* (1) Enable GPIO clock and configures the USART2 pins ********************/
	/* Enable the peripheral clock of GPIOC */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	/* Configure TX Pin connected to pin PA2 */
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_7);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_DOWN);
	
	/* Configure RX Pin connected to pin PA3 */
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, LL_GPIO_AF_7);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);
	
	/* (2) NVIC Configuration for USART2i interrupts */
	/*  - Set priority for USART2_IRQn */
	/*  - Enable USART2_IRQn           */
	NVIC_SetPriority(USART2_IRQn, 0);  
	NVIC_EnableIRQ(USART2_IRQn);

	/* (3) Enable the USART2 peripheral clock and clock source ****************/
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	/* (4) Configure USART2 functional parameters ********************************/

	/* Disable USART prior modifying configuration registers */
	/* Note: Commented as corresponding to Reset value */
	LL_USART_Disable(USART2);

	/* TX/RX direction */
	LL_USART_SetTransferDirection(USART2, LL_USART_DIRECTION_TX_RX);

	/* 8 data bit, 1 start bit, 1 stop bit, no parity */
	LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

	/* Configure transfer bit order : MSB first */
	LL_USART_SetTransferBitOrder(USART2, LL_USART_BITORDER_LSBFIRST);

	/* Clock configuration : Phase 2 edges, Polarity Low, Last Bit Clock output enabled */
	LL_USART_ConfigClock(USART2, LL_USART_PHASE_2EDGE, LL_USART_POLARITY_LOW, LL_USART_LASTCLKPULSE_OUTPUT);

	/* Oversampling by 16 : To be forced to 16 in USART mode */
	LL_USART_SetOverSampling(USART2, LL_USART_OVERSAMPLING_16);

 
  /* Set Baudrate to 9600 using APB1 frequency set to 32000000 Hz */
  /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
  /* Ex :
      Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance
  
      In this example, Peripheral Clock is expected to be equal to 32000000 Hz => equal to SystemCoreClock/2
  */
 	LL_USART_SetBaudRate(USART2, SystemCoreClock/2, LL_USART_OVERSAMPLING_16, 9600); 

	/* Enable USART2 RX Interrupt */
	LL_USART_EnableIT_RXNE(USART2);
	/* (5) Enable USART2 **********************************************************/
	LL_USART_Enable(USART2);

	/* Polling USART initialisation */
	while((!(LL_USART_IsActiveFlag_TEACK(USART2))) || (!(LL_USART_IsActiveFlag_REACK(USART2))))
	{ 
	}
	/* Enable USART2 ERROR Interrupt */
	LL_USART_EnableIT_ERROR(USART2);
	transmitRxbuf();
}

void USART_TXEmpty_Callback(void)
{
	if( TxIndex == ( Txcnt - 1))
	{
		/* Disable TXE interrupt */
		LL_USART_DisableIT_TXE(USART2);

		/* Enable TC interrupt */
		LL_USART_EnableIT_TC(USART2);
	}

	/* Fill TDR with a new char */
	LL_USART_TransmitData8(USART2, Txbuf[TxIndex++]);
}

void USART_CharTransmitComplete_Callback(void)
{
	if(TxIndex == Txcnt)
	{
		/* Disable TC interrupt */
		LL_USART_DisableIT_TC(USART2);

		/* Set USART2 End of transmission flag */
		TXstate  = TX_idle;
        TxIndex=0;
        Txcnt=0;
	}
}

void USART_CharReception_Callback(void)
{
	/* Read Received character. RXNE flag is cleared by reading of RDR register */
	RXstate = RX_activ;
	if( RxIndex < RX_BUFSZ)
		Rxbuf[RxIndex++] = LL_USART_ReceiveData8(USART2);
	else
		LL_USART_ReceiveData8(USART2);
	Timeout=systickms.readcounter();
}

void USART_TransferError_Callback(void)
{
	/* Disable USART2_IRQn */
	NVIC_DisableIRQ(USART2_IRQn);
	TXstate = TX_error;
    RXstate = RX_error;
}
