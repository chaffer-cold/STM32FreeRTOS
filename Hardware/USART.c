#include "stm32f10x.h"                  // Device header
#include "main.h"
#include "string.h"


/*要将USART1重映射到PB5,PB6*/
uint8_t data;
uint8_t flag=0; //flag:收到数据标志位

//TX:PA9 RX:PA10
void Serial_Init(void)
{   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStructure);


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate=115200;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);
    USART_Cmd(USART1,ENABLE);
    
    //USART_ITConfig(USART1,USART_IT_TXE,ENABLE);

}



uint8_t get_usart1_data(void)
{
    return data;
}
    


uint8_t get_usart1_rx_flag(void)
{
    if(flag)
    {  
        flag=0;
        return 1;
    }
    return 0;
}



//发送一个字节
void sendByte(uint8_t data)
{
    USART_SendData(USART1,data);
     while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}


//发送字符串
void sendString(char* data)
{   char*p=data;
    while(*p++!='\0')
    {
        sendByte(*p);
    }
}




void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE))         //收到东西了
    {
        data=USART_ReceiveData(USART1);
        flag=1;        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}