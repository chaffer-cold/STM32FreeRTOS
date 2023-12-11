
#include "stm32f10x.h"
#include "LED.h"
#include "USART.h"
#include "Sensor.h"
#include "Motor.h"
#include "Buzzer.h"
#include "EXTI.h"
#include "NVIC.h"
#include "TIM.h"



/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
//STM32变量
int voice=3;

//FreeRTOS变量
void TaskTestFunction(void *pvParameters);
void TaskCreate(void);
void System_Init(void);
TaskHandle_t MotorHandler;
TaskHandle_t BuzzerHandler;
TimerHandle_t TIM1_Handler;
TimerHandle_t TIM2_Handler;
QueueHandle_t car_statemail;
QueueHandle_t buzzer_statemail;
int main(void)
{
	System_Init();
	TaskCreate();
	vTaskStartScheduler();
	
}





void TaskCreate(void)
{
	car_statemail=xQueueCreate(1,sizeof(int));
	buzzer_statemail=xQueueCreate(1,sizeof(int));
	TIM1_Handler=xTimerCreate("TIM for Buzzer",750,pdTRUE,"TIM1",TIM1_CallBack);
	TIM2_Handler=xTimerCreate("TIM for Motor",50,pdFALSE,"TIM2",TIM2_CallBack);
	xTaskCreate(LED_Task,"LED",100,NULL,2,NULL);
	xTaskCreate(vSensor_getTask,"Sensor",40,NULL,4,NULL);
	xTaskCreate(car_self_drive,"Motor",100,NULL,5,&MotorHandler);
	xTaskCreate(MusicPlay,"Buzzer_Task",300,&voice,2,NULL);
	
	
	//xTaskCreate(TaskTestFunction,"TaskTest",100,NULL,3,NULL);

}


void System_Init(void)
{
	Serial_Init();
	LED_Init();
	key_1Init();
	key_2Init();
	Buzzer_Init();
	myNVIC_Init();
	myPWM_Init();
	
}
void TaskTestFunction(void *pvParameters)
{
	while(1)
	{
		sendString("TaskTest is running");
		vTaskDelay(1000);	
	}
	
}