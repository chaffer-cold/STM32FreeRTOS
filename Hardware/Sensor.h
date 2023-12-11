#ifndef __SENSOR_H
#define __SENSOR_H

void Sensor_Init(void);         //别动


int get_Sensor_Pin_0(void);     //获得第n个光电传感器的值
int get_Sensor_Pin_1(void);
int get_Sensor_Pin_2(void);
int get_Sensor_Pin_3(void);
int get_Sensor_state(void);     //获得总的值如果1,3量返回值为1001(2进制)
void send_Sensor_bit(void);   //串口获得传感器数值
void vSensor_getTask(void*para);  //给FreeRTOS用的函数








#endif
