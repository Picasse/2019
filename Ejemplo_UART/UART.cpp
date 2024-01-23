#include "Pin.h"
#include "stdint.h"

int i,cont,Bit_paridad;
char dato[5] = {0}, numero[4] = {0}, Rx; 
float valor;

PIN *BTN = new PIN(GPIOC, 0, 13, 0, 1, 2);
PIN *SENPIR = new PIN(GPIOC, 0, 12, 0, 1, 2);
PIN *SENIR = new PIN(GPIOC, 0, 11, 0, 1, 2);

void Enviar_Dato (char dato);
	
int main(void)
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOAEN;
	
	RCC -> APB1ENR |= RCC_APB1ENR_UART4EN;
	
	RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	GPIOC -> MODER |= 0x55;
	GPIOC -> OTYPER = 0x0;
	GPIOC -> OSPEEDR |= 0x55;
	GPIOC -> PUPDR |= 0x55;
	
	GPIOA -> MODER |= 0xA;
	GPIOA -> AFR[0] = 0x88;
	
	UART4 -> BRR |= 0x683;
	UART4->CR1|=0X2C;
	
	UART4->CR1 |= 0X1;
	
	NVIC_EnableIRQ(UART4_IRQn);
	
	while(1)
	{
		if(BTN->verificar_entrada())
		{
			Enviar_Dato('a');
			for(int delay = 0; delay <10000; delay++){}
		}else if( SENPIR -> verificar_entrada())
		{
			Enviar_Dato('c');
			for(int delay = 0; delay <10000; delay++){}
		}else if( (SENIR -> verificar_entrada()) == 0)
		{
			Enviar_Dato('d');
			for(int delay = 0; delay <10000; delay++){}
		}else
		{
			Enviar_Dato('b');
			for(int delay = 0; delay <10000; delay++){}
		}
	}
}

void Enviar_Dato (char dato)
{
	UART4 -> TDR = dato;
	while((UART4->ISR&=0X80)==0);
}

extern "C"
{
	void UART4_IRQHandler(void)
	{
		if(UART4->ISR & 0X20)
		{
			Rx=UART4->RDR;
			dato[cont]=Rx;
			if(dato[cont]=='a'){
				GPIOC -> ODR |= (1ul<<0);
				cont=0;
			}else if(dato[cont]=='b')
			{
				GPIOC -> ODR &= ~(1ul<<0);
				cont=0;
			}else{
				cont++;
					if(cont>5){
						cont=0;
						for(int j=0;j<5;j++){
							dato[j]=0;
						}
					}
				}
		}
	}
}