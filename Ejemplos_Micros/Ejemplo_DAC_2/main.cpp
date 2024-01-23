#include <stdio.h>
#include "stm32f7xx.h"

int tiempo;
int Valores_Eje_X, Valores_Eje_Y;
int Pendiente;

int main (void)
{
	
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOFEN; // enciendo reloj del GPIOA y GPIOB
	
	RCC -> APB1ENR |= RCC_APB1ENR_DACEN; // Enciendo el reloj del DAC
	
	GPIOA -> MODER |= 0xF00;
	GPIOF -> MODER |= 0x1;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock);
	
	DAC -> CR |= 0x10001;
	DAC -> DHR12R1 |= 500; 
	
	while(1)
	{
		
	}
}

extern "C"
{
	void SysTick_HandlerIRQ(void)
	{
		
	}
	
	
}