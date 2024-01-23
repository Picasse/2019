#include <stdio.h>
#include "stm32f7xx.h"
#include "math.h"

int tiempo_systick = 0;
int indice_vector = 0;

int main(void)
{
	RCC -> AHB1ENR |= 3;
	
	GPIOA -> MODER |= 0x55;
	GPIOA -> OTYPER = 0;
	GPIOA -> OSPEEDR |= 0x55;
	GPIOA -> PUPDR |= 0x55;
	
	GPIOB -> MODER |= 0x2555;
	GPIOB -> OTYPER = 0;
	GPIOB -> OSPEEDR |= 0x5555;
	GPIOB -> PUPDR |= 0x5555;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	// para un reloj
	int vector_filas[7] = {0x1F, 0x1F, 0xE, 0x4, 0xE, 0x1F, 0x1F};
	
	while(1)
	{
		for(int i=0; i<5; i++)
		{
			GPIOA -> ODR = (1UL<<i);
			GPIOB -> ODR = vector_filas[indice_vector];
		}
	}
	
}
extern "C"{
	void SysTick_handler(void)
	{
		tiempo_systick++;
		if(tiempo_systick > 20)
		{
			tiempo_systick = 0; 
			indice_vector++;
		}
		
		if(indice_vector > 6)
		{
			indice_vector =0;
		}
	}
}