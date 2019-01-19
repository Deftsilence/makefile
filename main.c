#include "main.h"
#include "stm32f10x_usart.h"

int _write(int file, char *ptr, int len);

void delay(int millis) {
    while (millis-- > 0) {
        volatile int x = 5971;
        while (x-- > 0) {
            __asm("nop");
        }
    }
}

float i=100.880;

int main(void) {

    // GPIO structure for port initialization
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // enable clock on APB2
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,  ENABLE);

    // configure port A1 for driving an LED
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // output push-pull mode
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // highest speed
//    GPIO_Init(GPIOC, &GPIO_InitStructure) ;             // initialize port

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);	
    USART_Cmd(USART1, ENABLE);

    // main loop
    while(1) {
//        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // turn the LED on
//        delay(DELAY);
//        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // turn the LED off
//        delay(DELAY);
//	USART_SendData(USART1, 0x08);
	printf("i= %f \r\n",i);
	printf("\r\n");
    }
}

int _write(int file, char *ptr, int len)
{
	int i;

	for (i=0; i<len; i++)
	{
		while(!(USART1->SR & USART_SR_TXE))
		{

		}
		USART_SendData(USART1, ptr[i]);
	}
//	if (file == 1) {
//		for (i = 0; i < len; i++)
//			USART_SendData(USART1, ptr[i]);
//		return i;
//	}

//	errno = EIO;
	return len;
}

