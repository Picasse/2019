#include <stdio.h>
#include "STM32F7xx.h"

int RXdat;
int val = 102;
int c=0;

 //Función de Configuración de Reloj de Sistema a 168MHz //
void SYSCLK_Conf() {
	RCC->CR				&=~(1UL << 24);				// OFF PLL //
	
	/* F_VCO 					= 8MHz * (PLLN / PLLM)	-> 336MHz = 8MHz * (336 / 8) 
		 F_PLL 					= F_VCO / PLLP					-> 168MHz = 336MHz / 2
		 F_USB_SDIO_RNG = F_VCO / PLLQ					-> 168MHz = 336MHz / 2 */
	RCC->PLLCFGR	 = 0x0240540;
	RCC->CR				|= (1UL << 24);				// ON PLL //
	
+
	/* AHB  = SYSCLK  	-> AHB   = 168MHz
		 APB1 = AHB / 4		-> 42MHz = 168MHz / 4
		 APB2 = AHB / 2		-> 84MHz = 168MHz / 2 */
	RCC->CFGR			 = 0x00029402;
}

extern "C" {
	
	void UART4_IRQHandler(void) {
		RXdat = UART4->RDR;
		
		switch(RXdat) {
			case '0':
			GPIOD->ODR &=~(1UL << 15);
			c=1009;//60%
			TIM3->CCR3	 = c;
			break;
			case '1':
			GPIOD->ODR |= (1UL << 15);
			c=1175;// 70%
			TIM3->CCR3	 = c;
			break;
			case '2':
			GPIOD->ODR &=~(1UL << 15);
			c=1343;//80%
			TIM3->CCR3	 = c;
			break;
			case '3':
			GPIOD->ODR &=~(1UL << 15);
			c=1511;//90%
			TIM3->CCR3	 = c;
			break;
			case '4':
			GPIOD->ODR &=~(1UL << 15);
			c=1679;//100%
			TIM3->CCR3	 = c;
			break;
			case '5':
			GPIOD->ODR &=~(1UL << 15);
			c=121;//7.2%
			TIM4->CCR3	 = c;
			break;
			case '6':
			GPIOD->ODR |=(1UL << 12);
			c=213;//13%
			TIM4->CCR3	 = c;
			break;
			case '7':
			GPIOD->ODR &=~(1UL << 12);
			c=305;//%
			TIM4->CCR3	 = c;
			break;
			case '8':
			GPIOD->ODR |=(1UL << 14);
			c=398;//%
			TIM4->CCR3	 = c;
			break;
			case '9':
			GPIOD->ODR &=~(1UL << 14);
			c=488;//100%
			TIM4->CCR3	 = c;
			break;
		}
	}
	
}

int main(void) {
	
	SYSCLK_Conf();
	
	RCC->AHB1ENR		|= (1UL << 3) | (1UL << 2) | (1UL << 0) | (1UL << 1);
	
	// Configuración de salida PWM TIM3 //
	GPIOB->MODER		|= (2UL << 2 * 0);
	GPIOB->OTYPER		&=~(1UL << 0);
	GPIOB->OSPEEDR	|= (2UL << 2 * 0);
	GPIOB->PUPDR		&=~(3UL << 2 * 0);
	GPIOB->AFR[0]   |= (2UL << 4 * 0);
	
	// Configuración de salida PWM TIM4//
	GPIOB->MODER		|= (2UL << 2 * 8);
	GPIOB->OTYPER		&=~(1UL << 0);
	GPIOB->OSPEEDR	|= (2UL << 2 * 0);
	GPIOB->PUPDR		&=~(3UL << 2 * 0);
	GPIOB->AFR[1]   |= (2UL << 4 * 0);
	
	//UART Configuracion pines de salida PC10 y PC11
	GPIOC->MODER		|= (2UL << 2 * 11) | (2UL << 2 * 10);
	GPIOC->OTYPER		&=~(1UL << 11) | (1UL << 10);
	GPIOC->OSPEEDR	|= (2UL << 2 * 11) | (2UL << 2 * 10);
	GPIOC->PUPDR		&=~(3UL << 2 * 11) | (2UL << 2 * 10);
	GPIOC->AFR[1]		|= (8UL << 12) | (8UL << 8);
	
	//Configuracion salida de los Leds de la tarjeta
	GPIOD->MODER		= 0x55000000;
//	GPIOD->OTYPER		&=~(1UL << 15);
//	GPIOD->OSPEEDR	|= (2UL << 2 * 15);
//	GPIOD->PUPDR		&=~(3UL << 2 * 15);
	
	// Configuración PWM  para un Servo SG90//
	RCC->APB1ENR		|= (1UL << 1);
	TIM3->CR1				|= (1UL << 7) | (1UL << 0);
	TIM3->CCMR2			|= (7UL << 4);
	TIM3->CCER			|= (1UL << 9) | (1UL << 8);
	TIM3->PSC				 = 499;
	TIM3->ARR				 = 1679;
	TIM3->EGR				|= (1UL << 0);

	// Configuración PWM  para un Motor dc//
	RCC->APB1ENR		|= (1UL << 2);
	TIM4->CR1				|= (1UL << 7) | (1UL << 0);
	TIM4->CCMR2			|= (7UL << 4);
	TIM4->CCER			|= (1UL << 9) | (1UL << 8);
	TIM4->PSC				 = 499;
	TIM4->ARR				 = 1679;
	TIM4->EGR				|= (1UL << 0);
	
	//Configuracion UART4
	RCC->APB1ENR		|= (1UL << 19);
	UART4->BRR			 = 0x1120;
	UART4->CR1			 = 0x2024;
	NVIC_EnableIRQ(UART4_IRQn);

	while(true) 
		{
		
		}
}
