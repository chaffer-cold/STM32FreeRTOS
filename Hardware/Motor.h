#pragma once
#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"
//单独驱动电机ABCD 

typedef struct 
{
    TIM_TypeDef* TIMx;
    int oc;
}Motor_TypeDef;
extern Motor_TypeDef MotorA;
extern Motor_TypeDef MotorB;
extern Motor_TypeDef MotorC;
extern Motor_TypeDef MotorD;
extern int is_turn;
extern int turn_num;

// void set_Motor_A(int speed);
// void set_Motor_B(int speed);
// void set_Motor_C(int speed);
// void set_Motor_D(int speed);
void car_straight(int speed);       //小车前进
void Motor_Speed(Motor_TypeDef Motorx,int speed);
void Rotate_to_the_left(void); //小车向左自转


void Rotate_to_the_right(void);  //向右自转
void Translate_to_the_left(void);  //向左平移
void Translate_to_the_right(void); //向右平移
void Translate_to_the_left_and_forward(void); //左上平移
void Translate_to_the_right_and_forward(void); //右上平移 

void car_self_drive(void);            //自动循迹
#endif
