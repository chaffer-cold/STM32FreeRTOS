#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "USART.h"
void LED_Init(void)
{
    /*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOC的时钟
														//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			//GPIO引脚，赋值为第13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;														//函数内部会自动根据结构体的参数配置相应寄存器
	GPIO_Init(GPIOB,&GPIO_InitStructure);				//实现GPIOC的初始化
	
	/*设置GPIO引脚的高低电平*/
	/*若不设置GPIO引脚的电平，则在GPIO初始化为推挽输出后，指定引脚默认输出低电平*/
	//GPIO_SetBits(GPIOB,GPIO_Pin_0);						//将PC13引脚设置为高电平
	

}
void LED_Task(void *pvParameters)
{
    static int light=0;
    static int light_state=0;
    
    while (1)
    {
        
        if(!light_state)
        {
            light++;
            if(light>100)
            light_state=1;

        }   
        else
        {
            light--;
            if(light==0)
            light_state=0;
        } 
        TIM_SetCompare4(TIM3,light);
        TIM_SetCompare1(TIM4,light);
        vTaskDelay(10);
            /* code */
    }
}