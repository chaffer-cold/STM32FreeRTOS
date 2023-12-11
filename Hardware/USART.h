#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"

void Serial_Init(void);                 //别动
uint8_t get_usart1_rx_flag(void);       //获得usart1串口标志位
uint8_t get_usart1_data(void);         //获得usart1串口数据
void sendByte(uint8_t data);            //发送一个字节
void sendString(char* data);            //发送字符串






#endif
