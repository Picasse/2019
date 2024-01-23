#include "Pin.h"

PIN::PIN()
{
			moder_registro = 0;
	    pin_registro = 0;
			otyper_registro = 0; 
			ospeedr_registro = 0;
			pupdr_registro = 0;
}

PIN::PIN(GPIO_TypeDef *Puerto, short MO, short N, bool OTY, short OSP, short PUP)
{
	    reloj = Puerto;
			moder_registro = MO;
	    pin_registro = N;
			otyper_registro = OTY; 
			ospeedr_registro = OSP;
			pupdr_registro = PUP;
      
			if(Puerto == GPIOA)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
			}
			if(Puerto == GPIOB)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
			}
			if(Puerto == GPIOC)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 
			}
			if(Puerto == GPIOD)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN; 
			}
			if(Puerto == GPIOE)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOEEN; 
			}
			if(Puerto == GPIOF)
			{
				RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOFEN; 
			}
			
			Puerto -> MODER |= (MO<<2*N);
			Puerto -> OTYPER = (1*OTY<<N);
			Puerto -> OSPEEDR |= (OSP<<2*N);
			Puerto -> PUPDR |= (PUP<<2*N);
			
}

void PIN::cambiar_salida(bool S) // función que permite cambiar la salida (1/0) del puerto
{     
	if(S==1)
	 {
			reloj -> ODR |= (1UL<<get_pin());
	 }else
	 {
			reloj -> ODR &= ~(1UL<<get_pin());
	 }
};

bool PIN::verificar_entrada() // función que permite verificar la entrada (1/0) del puerto
{
	int j = pow( 2 , (float)get_pin()); // número de potencias de dos, segun el número de pin

  if(reloj -> IDR & j )
		{
				for(int i =0; i<50000; i++){};
					
				if(reloj ->IDR & j )
				{
						return 1;
				}

		}else
		{
			return 0;
		} 
}


PIN::~PIN(){}
