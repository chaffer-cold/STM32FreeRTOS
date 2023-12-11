#include "stm32f10x.h"
#include "main.h"
#include "USART.h"







//黑线亮,出0,全亮出4个0

void Sensor_Init(void)
{   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructrue;
    GPIO_InitStructrue.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructrue.GPIO_Pin=Sensor_Pin_0|Sensor_Pin_1|Sensor_Pin_2|Sensor_Pin_3;
    GPIO_InitStructrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(Sensor_GPIO,&GPIO_InitStructrue);
}
int get_Sensor_Pin_0(void)
{
    return GPIO_ReadInputDataBit(Sensor_GPIO,Sensor_Pin_0);
}
int get_Sensor_Pin_1(void)
{
    return GPIO_ReadInputDataBit(Sensor_GPIO,Sensor_Pin_1);
}
int get_Sensor_Pin_2(void)
{
    return GPIO_ReadInputDataBit(Sensor_GPIO,Sensor_Pin_2);
}
int get_Sensor_Pin_3(void)
{
    return GPIO_ReadInputDataBit(Sensor_GPIO,Sensor_Pin_3);
}
int get_Sensor_state(void)
{
    static int Sensor_state=0;
    Sensor_state=(get_Sensor_Pin_1()<<3)|(get_Sensor_Pin_0()<<2)|(get_Sensor_Pin_2()<<1)|(get_Sensor_Pin_3()<<0);
    //Sensor_state=(get_Sensor_Pin_1()<<1)|(get_Sensor_Pin_3()<<0);

    return Sensor_state;
}

void vSensor_getTask(void*para)
{   static int Sensor_state=0;
    while(1)
    {
        Sensor_state=(get_Sensor_Pin_1()<<3)|(get_Sensor_Pin_0()<<2)|(get_Sensor_Pin_2()<<1)|(get_Sensor_Pin_3()<<0);
        xTaskNotify(MotorHandler,Sensor_state,eSetValueWithOverwrite);
        vTaskDelay(4);
    }
    
}

void send_Sensor_bit(void)
{
    sendByte(get_Sensor_Pin_1()+'0');
    sendByte(get_Sensor_Pin_0()+'0');
    sendByte(get_Sensor_Pin_2()+'0');
    sendByte(get_Sensor_Pin_3()+'0');
    sendByte('\n');

}



