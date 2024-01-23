#include <stdio.h>
#include <stm32f7xx.h>

bool bandera = 0;
int conteo_timer = 0;
	
int main()
{
		
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// Configuración de registros para cada puerto
	                                 // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	GPIOA -> MODER |= 0xAA;          // 00 00 00 00 00 00 00 00 00 00 00 00 10 10 10 10
                                   //   0     0     0     0     0     0     A     A
   
					                         // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	GPIOA -> PUPDR |= 0x55;          // 00 00 00 00 00 00 00 00 00 00 00 00 01 01 01 01
                                   //   0     0     0     0     0     0     5     5
																	 
			                             // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	GPIOB -> MODER |= 0x0;           // 00 00 00 00 10 10 00 00 00 10 00 00 00 00 00 00
                                   //   0	    0     A     0     2     0     0     0
	
						                       // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	GPIOB -> PUPDR |= 0xAA;          // 00 00 00 00 00 00 00 00 00 00 00 00 01 01 01 01
                                   //   0     0     0     0     0     0     5     5
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	// Configuración de las interrupciones EXTI'S 
	
	SYSCFG -> EXTICR[0] = 0x1;  // para el vector 0 activo los pin 1

	EXTI->IMR |= 0x1; // desenmascaro 0
	
	EXTI->RTSR |= 0x1; // evento con un flanco de subida
	
	NVIC_EnableIRQ(EXTI0_IRQn); // habilito la Interrupción EXTI0
	
	// Configuración para TIM 2
	
	RCC->APB1ENR |=  RCC_APB1ENR_TIM2EN ;  //Enable CLK TIM2
	
	TIM2->EGR |= 0;         // Up Counter
	 
//	TIM2->CCMR1 |= 0x6060;  // Set PWM channel 1 and PWM Channel 2
//	TIM2->CCMR2 |= 0x6060;  // Set PWM channel 3 and PWM Channel 4
	
	TIM2->PSC = 15;        // Prescale Fs/100 (Set Frequency PWM)
	TIM2->ARR = 10000;       // Counter/Resolution/(Set Frequency PWM)
	
	while(1)
	{
		if(bandera)
		{
			bandera = 0;
			conteo_timer = TIM2 -> CNT;
		}
	}
}

extern "C"
{
	void EXTI0_IRQHandler(void)
	{
		TIM2->EGR |= 1;
		bandera = 1;
	}
}
