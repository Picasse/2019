#include <stdio.h>
#include "stm32f7xx.h"

int main(void){	
	
	RCC -> AHB1ENR = 0x4; // LEDS AHORA EN EL PERTO C
	GPIOC -> MODER = 0x55; // COLOCAR LOS 4 PINES DE SALDA 
	GPIOC -> OTYPER = 0x0; // PUSH PULL
	GPIOC -> OSPEEDR = 0x55; // VELOCIDAD MEDIA 
	GPIOC -> PUPDR = 0x55; // PULL-UP
	
	int time = 0;
	
	while(1){
		
		for(int i= 0; i<16; i++){
			GPIOC -> ODR = i;
			for(time = 0; time<50000; time++);
		}
		
	}

}