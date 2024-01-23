#include <stdio.h>
#include "stm32f7xx.h"




int main(void)
{
		RCC -> AHB1ENR = 0x6;
	RCC -> APB2ENR = 0x4000;

	GPIOB -> MODER |= 0;
	GPIOB -> OTYPER = 0x0;
	GPIOB -> OSPEEDR |= 0x55;
	GPIOB -> PUPDR |= 0x55;

	GPIOC -> MODER |= 0x55;
	GPIOC -> OTYPER = 0x0;
	GPIOC -> OSPEEDR |= 0x55;
	GPIOC -> PUPDR |= 0x55;

	SYSCFG -> EXTICR[0] &= 0x1;
	EXTI -> IMR |= 0x1;
	EXTI -> FTSR |= 0x1;
		
	
	
	while(1)
	{
		
	}
	
}