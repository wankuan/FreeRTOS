#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	 
    __GPIOI_CLK_ENABLE(); 	
    GPIO_Initure.Pin = LED_G_PIN; 
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_NOPULL;        
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LED_G_GPIO_PORT,&GPIO_Initure);
    LED_G_OFF();

}

