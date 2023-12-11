#include "stm32f10x.h"
#include "main.h"
#include "Motor.h"
void TIM1_CallBack(void*para)
{

}


void TIM2_CallBack(void*para)
{
    if(is_turn>=10)
    {
        turn_num++;
    }
    is_turn=0;
}