#include "LCD.h"

//void SystemIn()
//{
// int a=0;
// RCC->CR |= 0x10000;                         
// while((RCC->CR & 0x20000)==0);              
// RCC->APB1ENR = 0x10000000;                  
// RCC->CFGR = 0x00009400;                     
// RCC->PLLCFGR = 0x07405408;                  
// RCC->CR |= 0x01000000;                      
// while((RCC->CR & 0x02000000)==0);           
// FLASH->ACR = (0x00000605);                  
// RCC->CFGR |= 2;                             
// for (a=0;a<=500;a++);
//}

void Set_GPIO() 
{
	 RCC->AHB1ENR |=  0xFF; // Open Clock GPIOD

	 GPIOD->MODER |=   GPIO_MODER_MODER15_1|GPIO_MODER_MODER14_1|
										GPIO_MODER_MODER13_1|GPIO_MODER_MODER12_1;

	 GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0|GPIO_OSPEEDER_OSPEEDR14_0|
										GPIO_OSPEEDER_OSPEEDR13_0|GPIO_OSPEEDER_OSPEEDR12_0;
	 GPIOD->PUPDR  |= 0x55000000;	
	GPIOB->MODER =0XF;
	GPIOB->PUPDR=0;
	 GPIOD->AFR[0] |= 0;
	 GPIOD->AFR[1] |= 0x22220000;	
				
}

void delay(long signed int sn)
{
    while(sn--);
}
void adc1(void)
{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN|RCC_APB2ENR_ADC2EN;
		RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
		ADC->CCR =ADC_CCR_ADCPRE_1;
		ADC1->CR2 = ADC_CR2_ADON|ADC_CR2_EXTSEL|ADC_CR2_EXTEN;
		ADC2->CR2 = ADC_CR2_ADON|ADC_CR2_EXTSEL|ADC_CR2_EXTEN;
}


int main(void)
{
								int pot;
//		            SystemIn();
								Set_GPIO();
                adc1();		
	             	ADC1->SQR3 = 8;      //adc por pb0								 
	              RCC->APB1ENR |=  RCC_APB1ENR_TIM4EN ;  //Enable CLK TIM4
		           	TIM4->EGR |= 1;         // Up Counter
								 
								TIM4->CCMR1 |= 0x6060;  // Set PWM channel 1 and PWM Channel 2
								 
								TIM4->PSC = 15;        // Prescale Fs/100 (Set Frequency PWM)
		            TIM4->ARR = 20000;       // Counter/Resolution/(Set Frequency PWM)
								 
								

		            TIM4->CCER |= 0x1111;   // Enable PWM1,PWM2,PWM3,andPWM4
                TIM4->CR1 |= 1;         // Enable TIM4
		while(1)
    {
//				ADC1->CR2 |= ADC_CR2_SWSTART;

//				while((ADC1->SR & ADC_SR_EOC)==0);
//				ADC1->SR =0;
      
        pot += 110;
        if(pot > 2400)
				{
					pot = 0;
				}			
				
				TIM4->CCR1 = pot;      
		}																
}

