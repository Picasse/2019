#include <stdio.h>
#include "stm32f746xx.h"
#include "Math.h"


int main()
{
	
	RCC -> APB1ENR |= RCC_APB1ENR_DACEN;

	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA -> MODER |= 0xF00; // 11 11 00 00 00 00 PA4 Y PA5 ANALOGO
	
// Configuración del dac antes de activarlo

  DAC -> SWTRIGR |= DAC_SWTRIGR_SWTRIG2; // Activamos la generación del trigger 0x2
	DAC -> DHR12R2 |= DAC_DHR12R2_DACC2DHR; // Configuramos a 12 bits con alineación derecha 
	DAC -> CR |= DAC_CR_TEN2;
	DAC -> CR |= DAC_CR_WAVE2;
  DAC -> CR |= 0x380000; // 00 00 00 00 00 00 00 00 00 00 00 00 TEN
	DAC -> CR |= DAC_CR_DMAEN2; // 

	while(1)
	{
		
		DAC -> CR |= 0x1000;
	}
}