#include "stm32f10x.h"
#include "main.h"

void myPWM_Init(void)
{   //PB8,9引脚有问题,先试试取消重映射
    
    //打开GPIO
    // Motor_A_Pin0 PA2 TIM5_CH3
    // Motor_A_Pin1 PA3 TIM5_CH4
    // Motor_B_Pin0 PA6 TIM3_CH1
    // Motor_B_Pin0 PA7 TIM3_CH2
    // Motor_C_Pin0 PC6 TIM8_CH1
    // Motor_C_Pin0 PC7 TIM8_CH2
    // Motor_D_Pin0 PC8 TIM8_CH3
    // Motor_D_Pin0 PC9 TIM8_CH4
    // Buzzer PA8 TIM1_CH1
    //LED_R:PB5 TIM4_CH1
    //LED_B:PB1 TIM3_CH4

    
    /*在TIM4,TIM8上,TIM3  LED_R跳线到PB6的TIM4_CH1上*/
    //Motor的GPIO初始
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
     
     GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
     
     GPIO_InitStructure.GPIO_Pin=Motor_C_Pin_0|Motor_C_Pin_1|Motor_D_Pin_0|Motor_D_Pin_1;
     GPIO_Init(Motor_GPIO_1,&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin=Motor_B_Pin_0|Motor_B_Pin_1|Motor_A_Pin_0|Motor_A_Pin_1;
     GPIO_Init(MOtor_GPIO_2,&GPIO_InitStructure);   
    
    
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=100-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler=360-1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_Prescaler=2900-1;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);
    
    
    TIM_Cmd(TIM1,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
    TIM_Cmd(TIM5,ENABLE);
    TIM_Cmd(TIM8,ENABLE);
    
    
  
    
    
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse=0;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OutputState=ENABLE;
    //LED的PMW
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);
    TIM_OC4Init(TIM3,&TIM_OCInitStructure);
    //电机A
    TIM_OC3Init(TIM5,&TIM_OCInitStructure);
    TIM_OC4Init(TIM5,&TIM_OCInitStructure);
    //电机B
    TIM_OC1Init(TIM3,&TIM_OCInitStructure);
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);

    //电机C,D连接TIM8,要反过来装不然会抽风
    TIM_OC1Init(TIM8,&TIM_OCInitStructure);
    TIM_OC2Init(TIM8,&TIM_OCInitStructure);
    TIM_OC3Init(TIM8,&TIM_OCInitStructure);
    TIM_OC4Init(TIM8,&TIM_OCInitStructure);
    //buzzer的PWM
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    TIM_CtrlPWMOutputs(TIM8,ENABLE);    

}
