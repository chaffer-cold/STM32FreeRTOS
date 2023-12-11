#pragma once
#ifndef __MAIN_H
#define __MAIN_H
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
enum yinjie{dio=2900,ra=2585,mi=2303,fa=2178,so=1939,la=1727,xi=1538};
extern int test;


//FreeRTOS引出
extern TaskHandle_t MotorHandler;
extern TaskHandle_t BuzzerHandler;
extern TimerHandle_t TIM1_Handler;
extern TimerHandle_t TIM2_Handler;

extern QueueHandle_t car_statemail;
extern QueueHandle_t buzzer_statemail;
/*屏幕:PB8,PB9*/


/*GPIO口占用情况:
LED_R:PB5 TIM4_CH1
LED_B:PB1 TIM3_CH4
USART1_RX PA10
USART1_TX PA9
Sensor_0  PC2
Sensor_1  PC3
Sensor_2  PC4
Sensor_3  PC5
Motor_A_Pin0 PA2 TIM5_CH3
Motor_A_Pin1 PA3 TIM5_CH4
Motor_B_Pin0 PA6 TIM3_CH1
Motor_B_Pin0 PA7 TIM3_CH2
Motor_C_Pin0 PC6 TIM8_CH1
Motor_C_Pin0 PC7 TIM8_CH2
Motor_D_Pin0 PC8 TIM8_CH3
Motor_D_Pin0 PC9 TIM8_CH4
Buzzer PA8 TIM1_CH1
key_1 PA0
key_2 PC13
*/



/*Sesnor PC2,PC3,PC4,PC5*/
#define Sensor_GPIO     GPIOC
#define Sensor_Pin_0    GPIO_Pin_2
#define Sensor_Pin_1    GPIO_Pin_3
#define Sensor_Pin_2    GPIO_Pin_4
#define Sensor_Pin_3    GPIO_Pin_5

/*A:TIM5_CH3 TIM5_CH4 PA2,PA3 B:TIM3_CH1 TIM3_CH2 PA6,PA7*/

/*C:TIM8_CH1 TIM8_CH2 PC6,PC7 D:TIM8_CH3 TIM8_CH4 PC8,PC9
电机3,4的pin要反装*/

                                       


#define Motor_GPIO_1      GPIOC
#define Motor_C_Pin_0     GPIO_Pin_6
#define Motor_C_Pin_1     GPIO_Pin_7
#define Motor_D_Pin_0     GPIO_Pin_8
#define Motor_D_Pin_1     GPIO_Pin_9
#define MOtor_GPIO_2       GPIOA
#define Motor_B_Pin_0     GPIO_Pin_6
#define Motor_B_Pin_1     GPIO_Pin_7
#define Motor_A_Pin_0     GPIO_Pin_2
#define Motor_A_Pin_1     GPIO_Pin_3
/*USART1PB5,PB6*/

#define USART1_GPIO         GPIOA
#define USART1_RX_Pin       GPIO_Pin_10
#define USART1_TX_Pin       GPIO_Pin_9


//key
#define key_1_GPIO GPIOA
#define key_1_Pin GPIO_Pin_0
#define key_2_GPIO GPIOC
#define key_2_Pin GPIO_Pin_13

//rgb
#define RGB_R_GPIO GPIOB
#define RGB_R_Pin  GPIO_Pin_6
#define RGB_G GPIO GPIOB
#define RGB_G_Pin  GPIO_Pin_0
#define RGB_B_GPIO GPIOB
#define RGB_B_Pin  GPIO_Pin_1
//buzzer
#define Buzzer_GPIO GPIOA
#define Buzzer_Pin  GPIO_Pin_8




#endif
