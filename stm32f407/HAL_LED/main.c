#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

#define GREEN_LED GPIO_PIN_12
#define ORANGE_LED GPIO_PIN_13
#define RED_LED GPIO_PIN_14
#define BLUE_LED GPIO_PIN_15

void GPIO_Init(void);


int main(void)	
{
		int i;

	GPIO_Init();
	
while(1)
{			
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_14|GPIO_PIN_15,GPIO_PIN_SET);

	for (i=0;i<500000;i++)
	{
		
	}
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_14|GPIO_PIN_15,GPIO_PIN_RESET);
			for (i=0;i<500000;i++){}

}
}

void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_conf;

	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_14|GPIO_PIN_15,GPIO_PIN_RESET);
	
	GPIO_conf.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_conf.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_conf.Pull = GPIO_NOPULL;
	GPIO_conf.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOD,&GPIO_conf);

}