#include <stdio.h>
#include "stm32f7xx.h"
#include "math.h"

void display_7_segmentos(int n) // función que permite visualizar el numero 'n' en el display
{
	  int BCD[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71}; // vector con las diferentes configuraciones para los numeros (0-9)
		int prueba = 0;
		
		if((n>=0) && (n<=9))
		{
				for(int i=0; i<7; i++)
				{
						prueba = pow(2,(float)i);
						if( (BCD[n] & prueba) == prueba)
						{
								GPIOA->ODR |= (1UL<<i);
						}
						else
						{
								GPIOA->ODR &= ~(1UL<<i);
						}
				}
		}	
}

int main(void)
{
	RCC -> AHB1ENR = 0x7;
  RCC -> APB2ENR = 0x4000;
	
	GPIOA -> MODER |= 0x3F;
	GPIOA -> OSPEEDR |= 0x55555555;
	GPIOA -> OTYPER = 0x0;
	GPIOA -> PUPDR |= 0X55555555;
	
	GPIOB -> MODER |= 0x10004001;
	GPIOB -> OSPEEDR |= 0x55555555;
	GPIOB -> OTYPER = 0x0;
	GPIOB -> PUPDR |= 0X55555555;
	
	SYSCFG -> EXTICR[3] |= 0x20;
	EXTI -> IMR |= 0x2000;
	EXTI -> RTSR |= 0x2000;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	
	
	while(1)
	{
		//GPIOB -> ODR |= 0x1;
	}
	
}

extern "C"
{
	void EXTI15_10_IRQHandler(void)
	{
		EXTI -> PR = 0x2000;
		GPIOB -> ODR = 0x1;
		for(int i = 0; i<20000000; i++);
		GPIOB -> ODR = 0x80;
		for(int i = 0; i<10000000; i++);
		GPIOB -> ODR = 0x4000;
		for(int i = 0; i<25000000; i++);
		GPIOB -> ODR = 0x0;
	}
}