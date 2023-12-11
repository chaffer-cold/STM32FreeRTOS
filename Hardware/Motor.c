#include "Motor.h"
#include "stm32f10x.h"
#include "main.h"
#include "Sensor.h"
#include "USART.h"
#include "TIM.h"


Motor_TypeDef MotorA={ .oc = 3,.TIMx=TIM5};
Motor_TypeDef MotorB={ .oc = 1,.TIMx=TIM3};
Motor_TypeDef MotorC={ .oc = 1,.TIMx=TIM8};
Motor_TypeDef MotorD={ .oc = 3,.TIMx=TIM8};
int is_turn=0;  //is_turn判断是不是传感器抽风,turn_num用来判断转弯时间
int turn_num=0;



//控制电动机A的转速,speed从-100到100
//A,B,C,D分别是右下右上左上，左下

//set_Motorcompare和set_Motorcompareback别动
static void set_Motorcompare(Motor_TypeDef Motorx,int speed)
{   
    if (speed==0)
        speed=1;
    if(Motorx.oc==1)
        {
            TIM_SetCompare1(Motorx.TIMx,speed-1);
            TIM_SetCompare2(Motorx.TIMx,0);
        }
    
    else if(Motorx.oc==3)
        {
            TIM_SetCompare3(Motorx.TIMx,speed-1);
            TIM_SetCompare4(Motorx.TIMx,0);
        }
   
}
//电机后退
static void set_Motorcompareback(Motor_TypeDef Motorx,int speed)
{   
    if (speed==0)
        speed=1;
    if(Motorx.oc==1)
        {
            TIM_SetCompare2(Motorx.TIMx,speed-1);
            TIM_SetCompare1(Motorx.TIMx,0);
        }
 
    else if(Motorx.oc==3)
        {
            TIM_SetCompare4(Motorx.TIMx,speed-1);
            TIM_SetCompare3(Motorx.TIMx,0);
        }
    
}


void Motor_Speed(Motor_TypeDef Motorx,int speed)
{
    if(speed>30)
    {
        set_Motorcompare(Motorx,speed);
        
    }
    else if(speed<30&&speed>-30)
    {
        set_Motorcompare(Motorx,0);
    }
    else 
    {
        set_Motorcompareback(Motorx,-speed);
    }
       

}
void car_straight(int speed)
{
    Motor_Speed(MotorA,speed);
    Motor_Speed(MotorB,speed);
    Motor_Speed(MotorC,speed);
    Motor_Speed(MotorD,speed);
}
//向左自转
void Rotate_to_the_left(void)
{
    Motor_Speed(MotorA,100);
    Motor_Speed(MotorB,100);
    Motor_Speed(MotorC,-100);
    Motor_Speed(MotorD,-100);
}
//向右自转
void Rotate_to_the_right(void)
{
    Motor_Speed(MotorA,-100);
    Motor_Speed(MotorB,-100);
    Motor_Speed(MotorC,100);
    Motor_Speed(MotorD,100);
}
//向左平移
void Translate_to_the_left(void)
{
    Motor_Speed(MotorA,-100);
    Motor_Speed(MotorB,100);
    Motor_Speed(MotorC,-100);
    Motor_Speed(MotorD,100);
}
//向右平移
void Translate_to_the_right(void)
{
    Motor_Speed(MotorA,100);
    Motor_Speed(MotorB,-100);
    Motor_Speed(MotorC,100);
    Motor_Speed(MotorD,-100);
}
//左上平移
void Translate_to_the_left_and_forward(void)
{
    Motor_Speed(MotorA,0);
    Motor_Speed(MotorB,100);
    Motor_Speed(MotorC,0);
    Motor_Speed(MotorD,100);
}
//右上平移
void Translate_to_the_right_and_forward(void)
{
    Motor_Speed(MotorA,100);
    Motor_Speed(MotorB,0);
    Motor_Speed(MotorC,100);
    Motor_Speed(MotorD,0);
}
void left_turn_small(void)
{
    Motor_Speed(MotorA,100);
    Motor_Speed(MotorB,100);
    Motor_Speed(MotorC,50);
    Motor_Speed(MotorD,50);

}
void right_turn_small(void)
{
    Motor_Speed(MotorA,50);
    Motor_Speed(MotorB,50);
    Motor_Speed(MotorC,100);
    Motor_Speed(MotorD,100);
    
}
void car_self_drive(void)
{   //不要动的东西
    static int control_mode=0;
    static int flag=0;
    static int car_state=0;
    static int Sensor_state=0;
    static uint32_t t_start=0;
    //可以调的东西以ms为单位
    static int time1=5000;
    static int time2=1500;
    static int time3=1600;
    while(1)
    {   
        xTaskNotifyWait(0,0,&Sensor_state,0);
        xQueuePeek(car_statemail,&car_state,0);
        //sendByte(car_state+'0');     //人工避障程序
        //sendByte(car_state+'0');
        //send_Sensor_bit();
        if(control_mode==1)
        {
            Translate_to_the_left_and_forward();
            vTaskDelay(time2);
            Translate_to_the_right_and_forward();
            vTaskDelay(time3);
            control_mode=0;
        }
        if(control_mode==0)
        {   
            if((flag==1)&&(xTaskGetTickCount()>(t_start+time1)%4294967295))
            {
                control_mode=1;
                flag+=1;
            }
            if(turn_num>=1&&!flag)
            {

                t_start=xTaskGetTickCount();
                flag=1;
            }

            if(car_state==0)            //最高优先级判断是否停止
            {
                car_straight(0);
            }
            else
            {

                    /*自动驾驶*/
                if(Sensor_state==0xD)                  //1101 13右小转
                {
                    right_turn_small();
                }                   
                else if(Sensor_state==0xB)                   //1011 11左小转
                {
                    left_turn_small();
                }
                else if(Sensor_state==0x0)
                {
                    car_state=0;
                    xQueueOverwrite(car_statemail,&car_state);
                    
                    
                }                                         //0000停止
                else if((Sensor_state&(1<<3|1<<0))==0x9) //1xx1走直线
                {
                    car_straight(100);
                }
            
                
                
                //牛马情况
                 else if((Sensor_state&(1<<3|1<<0))==0x0)  //0xx0停止 或者直走
                
                 {                                           //TIM&没用
                    
                     is_turn++;
                     xTimerReset(TIM2_Handler,0);
                     car_straight(100);
                 }
                else if((Sensor_state&(1<<3|1<<0))==0x8)  //1xx0右转
                {

                    Rotate_to_the_right();
                }
                else if((Sensor_state&(1<<3|1<<0))==0x1 ) //0xx1左转
                {   
                    
                    Rotate_to_the_left();
                }  
            }


           

        
        }   
        vTaskDelay(2);
    }

    
}













































// void set_Motor_A(int speed)
// {   
//     if(speed>0)
//     {
//         TIM_SetCompare1(TIM4,speed-1);
//         TIM_SetCompare2(TIM4,0);
        
//     }
//     else if(speed==0)
//     {
//         TIM_SetCompare3(TIM4,0);
//         TIM_SetCompare4(TIM4,0);
//     }
//     else 
//     {
//         TIM_SetCompare1(TIM4,0);
//         TIM_SetCompare2(TIM4,(-speed)-1);
//     }
        
// }

// void set_Motor_B(int speed)
// {
//     if(speed>0)
//     {
//         TIM_SetCompare1(TIM3,speed-1);
//         TIM_SetCompare2(TIM3,0);
//     }
//     else if(speed==0)
//     {
//         TIM_SetCompare1(TIM3,0);
//         TIM_SetCompare2(TIM3,0);
//     }
//     else 
//     {
//         TIM_SetCompare1(TIM3,0);
//         TIM_SetCompare2(TIM3,(-speed)-1);
//     }
        
// }
// void set_Motor_C(int speed)
// {
//     if(speed>0)
//     {
//         TIM_SetCompare1(TIM8,speed-1);
//         TIM_SetCompare2(TIM8,0);
//     }
//     else if(speed==0)
//     {
//         TIM_SetCompare3(TIM8,0);
//         TIM_SetCompare4(TIM8,0);
//     }
//     else 
//     {
//         TIM_SetCompare1(TIM8,0);
//         TIM_SetCompare2(TIM8,(-speed)-1);
//     }
        
// }
// void set_Motor_D(int speed)
// {
//     if(speed>0)
//     {
//         TIM_SetCompare3(TIM8,speed-1);
//         TIM_SetCompare4(TIM8,0);
        
//     }
//     else if(speed==0)
//     {
//         TIM_SetCompare3(TIM8,0);
//         TIM_SetCompare4(TIM8,0);
//     }
//     else 
//     {
//         TIM_SetCompare3(TIM8,0);
//         TIM_SetCompare4(TIM8,(-speed)-1);
//     }
        
// }
