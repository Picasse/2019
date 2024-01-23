#include <stdio.h>
#include "stm32f7xx.h"
#include "LCD.h"

int main(void)
{
	RCC -> AHB1ENR = 0x6;
	RCC -> APB2ENR = 0x100;
	
//	GPIOB -> MODER |= 0x10004001;
//	GPIOB -> OTYPER = 0x0;
//	GPIOB -> OSPEEDR |= 0x10004001;
//	GPIOB -> PUPDR |= 0x10004001;
	
	GPIOC -> MODER |= 0x4;
	
	ADC2 -> CR1 |= 0x0;
	ADC2 -> CR2 |= 0x201;
	ADC2 -> SQR3 = 10;
	
//	int temp = 0;
	
	while(1)
	{
		ADC2 -> CR2 |= 0x40000000;
		if(((ADC2 -> DR &= 0x4) <= 1)&&((ADC2 -> DR &= 0x4) >= 5))
		{
			LCD_InsertarDato('A');
		}else if(((ADC2 -> DR &= 0x4) <= 1)&&((ADC2 -> DR &= 0x4) >= 5))
		{
			
		}else if(((ADC2 -> DR &= 0x4) <= 1)&&((ADC2 -> DR &= 0x4) >= 5))
		{
			
		}else if(((ADC2 -> DR &= 0x4) <= 1)&&((ADC2 -> DR &= 0x4) >= 5))
		{
			
		}else if(((ADC2 -> DR &= 0x4) <= 1)&&((ADC2 -> DR &= 0x4) >= 5))
		{
			
		}else if(((ADC2 -> DR &= 0x4) == 1)&&((ADC2 -> DR &= 0x4) == 5))
		{
			
		}else if(((ADC2 -> SR &= 0x4) == 1)&&((ADC2 -> DR &= 0x4) == 5))
		{
			
		}else if(((ADC2 -> DR &= 0x4) == 1)&&((ADC2 -> DR &= 0x4) == 5))
		{
			
		}
	}
}