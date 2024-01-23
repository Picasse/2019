#include <stdio.h>
#include "STM32F7xx.h"

//

int time=500000;

int main(void)
{
	int i=0;
	int j = 0,k=0;
	int vec[3] = {0,7,14};
	//***********************
	// CONFIGURACIÓN DEL CLOCK
	RCC->AHB1ENR |= (1UL << 1); // prender el clock del puerto PTB
	
	//***********************
	// CONFIGURACION DE PINES
	GPIOB->MODER = 0X10004001;
	GPIOB->OTYPER = 0;
	GPIOB->OSPEEDR = 0X10004001;
	GPIOB->PUPDR = 0X10004001;
	
	//************************
	
	while(true) // bucle infinito
	{
		for(k=0; k<3; k++)
		{
			for(j=0; j<10; j++)
			{ 
				GPIOB->ODR |= (1UL << vec[k]); // enciende LED
				for(i=0; i<time; i++); // delay
				GPIOB->ODR &= ~(1UL << vec[k]); // apaga LED
				for(i=0; i<time; i++); // delay
				
			}

    }
		
	} // cierre while
	
} // cierre main

