#include "USART_DMA.h"
///����DMA�ʼ�
/**
*@brief : ʹ��DMA���д��ڽ���
1.���ڳ�ʼ������
2.DMA��ʼ�����ã�ÿ��DMA��ʼ������ǰ��Ҫ���з���ʼ��Deinit��
3.__HAL_LINKDMA(&USART_Handler,hdmarx,USARTRxDMA_Handler);
4.HAL_UART_Receive_DMA(&UART1_Handler,RX_BUF,Uart_size);�򿪴���DMA����
5.HAL_DMA_IRQHandler(&USARTRxDMA_Handler);	//����HAL���жϴ����ú���
6.void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)

__HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//���DMA2_Steam7������ɱ�־
HAL_UART_DMAStop(&UART1_Handler);      //��������Ժ�رմ���DMA


����ô�����ȫ���������ж�  �����ǵ���DMA�Դ��ĺ���ӳ��
**/

UART_HandleTypeDef USART_Handler; //UART���


void UART_Init(void)
{
	USART_Handler.Instance=USART1;					   
	USART_Handler.Init.BaudRate=115200;				    //������
	USART_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	USART_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	USART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	USART_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&USART_Handler);					    //HAL_UART_Init()��ʹ��UART1
}

 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();					//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;			//PA2-U2_TX  PA3-U2_RX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	 
		
		
    HAL_NVIC_EnableIRQ(USART1_IRQn);		
    HAL_NVIC_SetPriority(USART1_IRQn,0,1);
	}	
}


struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}





