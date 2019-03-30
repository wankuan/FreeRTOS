#include "USART_DMA.h"
///串口DMA笔记
/**
*@brief : 使用DMA进行串口接收
1.串口初始化配置
2.DMA初始化配置（每次DMA初始化配置前需要进行反初始化Deinit）
3.__HAL_LINKDMA(&USART_Handler,hdmarx,USARTRxDMA_Handler);
4.HAL_UART_Receive_DMA(&UART1_Handler,RX_BUF,Uart_size);打开串口DMA接收
5.HAL_DMA_IRQHandler(&USARTRxDMA_Handler);	//调用HAL库中断处理公用函数
6.void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)

__HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//清除DMA2_Steam7传输完成标志
HAL_UART_DMAStop(&UART1_Handler);      //传输完成以后关闭串口DMA


会调用串口完全接收数据中断  而不是调用DMA自带的函数映射
**/

UART_HandleTypeDef USART_Handler; //UART句柄


void UART_Init(void)
{
	USART_Handler.Instance=USART1;					   
	USART_Handler.Init.BaudRate=115200;				    //波特率
	USART_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	USART_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	USART_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	USART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	USART_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&USART_Handler);					    //HAL_UART_Init()会使能UART1
}

 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();					//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;			//PA2-U2_TX  PA3-U2_RX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
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
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}





