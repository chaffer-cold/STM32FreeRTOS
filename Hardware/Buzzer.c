#include "stm32f10x.h"
#include "main.h"
#include "USART.h"

//初始化蜂鸣器
void Buzzer_Init(void)

{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=Buzzer_Pin;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(Buzzer_GPIO,&GPIO_InitStructure);
    
}


void myvoice(enum yinjie yj,int percent)
 {
    //要判断当前是否继续输出   
     TIM_CtrlPWMOutputs(TIM1,ENABLE);
     TIM_PrescalerConfig(TIM1,yj,TIM_PSCReloadMode_Immediate);
     TIM_SetCompare1(TIM1,percent-1);
     
     
 }
 void MusicPlay(void*para)
 {  static int voice;
    static int buzzer_state=0;
    static int jiepai=750;
    static int p_now=0;
    int time=0;
    static int yuepu[]=

    {

 	    dio,1,dio,1,so,1,so,1,la,1,la,1,so,2,fa,1,fa,1,mi,1,mi,1,ra,1,ra,1,dio,2,so,1,so,1,fa,1,fa,1,mi,1,mi,1,ra,2,
 	    so,1,so,1,fa,1,fa,1,mi,1,mi,1,ra,2,dio,1,dio,1,so,1,so,1,la,1,la,1,so,2,fa,1,fa,1,mi,1,mi,1,la,1,la,1,dio,2		
    };
    voice=*((int*)para);
    while (1)
    {
        sendByte('B');
        xQueuePeek(buzzer_statemail,&buzzer_state,0);
        sendByte('C');
        if(buzzer_state==1)
        {
            TIM_CtrlPWMOutputs(TIM1,ENABLE);
            TIM_PrescalerConfig(TIM1,yuepu[p_now],TIM_PSCReloadMode_Immediate);
            TIM_SetCompare1(TIM1,voice);
            vTaskDelay(jiepai*yuepu[p_now+1]);
            TIM_CtrlPWMOutputs(TIM1,DISABLE);
            p_now=(p_now+2)%42;
            vTaskDelay(50);            
        }
        vTaskDelay(0);
        /* code */
    }
    
 }











