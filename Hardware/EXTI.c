#include "stm32f10x.h"
#include "main.h"
#include "FreeRTOS.h"   
#include "task.h"
#include "queue.h"
#include "USART.h"
//配置key1为外部中断
void key_1Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=key_1_Pin;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(key_1_GPIO,&GPIO_InitStructure);
    //配置GPIO为外部中断
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    //设置中断优先级
    
}

void key_2Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=key_2_Pin;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(key_2_GPIO,&GPIO_InitStructure);
    //配置GPIO为外部中断
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line13;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    //设置中断优先级
    
}

    //key1的中断
void EXTI0_IRQHandler(void)
{   
    static int car_state=0;
    if(EXTI_GetITStatus(EXTI_Line0)==SET)
    {
        xQueuePeekFromISR(car_statemail,&car_state);  
        sendByte(car_state+'0');
        car_state=(car_state+1)%2;
        sendByte(car_state+'0');
        xQueueOverwriteFromISR(car_statemail,&car_state,NULL);
       
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
   
}

    //key2的中断
void EXTI15_10_IRQHandler(void)
{   
    static int buzzer_state=0;
    if (EXTI_GetITStatus(EXTI_Line13))
    {
        sendByte('A');
        buzzer_state=(buzzer_state+1)%2;

        xQueueOverwriteFromISR(buzzer_statemail,&buzzer_state,NULL);
        sendByte('F');
    }
    EXTI_ClearITPendingBit(EXTI_Line13);
}
