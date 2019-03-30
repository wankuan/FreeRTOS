#include "main.h"


//�������ȼ�
#define START_TASK_PRIO		2
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		1
//�����ջ��С	
#define LED0_STK_SIZE 		100  
//������
TaskHandle_t LED0Task_Handler;
//������
void led_task(void *pvParameters);

//�������ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		128
//������
TaskHandle_t FLOATTask_Handler;
//������
void float_task(void *pvParameters);




int main(void)
{
BSP_Init();
LED_Init();
UART_Init();
//HAL_Delay(1000);
//������ʼ����
xTaskCreate((TaskFunction_t )start_task,            //������
          (const char*    )"start_task",          //��������
          (uint16_t       )START_STK_SIZE,        //�����ջ��С
          (void*          )NULL,                  //���ݸ��������Ĳ���
          (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
          (TaskHandle_t*  )&StartTask_Handler);   //������              
vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led_task,     	
                (const char*    )"led_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
                    //�����������
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 
void led_task(void *pvParameters)
{
    while(1)
    {
     LED_G_ON();
     DEBUG("LED_G_ON\r\n");
     vTaskDelay(500);
     LED_G_OFF();
     DEBUG("LED_G_OFF\r\n");
     vTaskDelay(500);
    }
}   

//�����������
void float_task(void *pvParameters)
{
	static float float_num=0.00;
	while(1)
	{
		float_num+=0.01f;
		printf("float_num��ֵΪ: %.4f\r\n",float_num);
    vTaskDelay(1000);
	}
}

