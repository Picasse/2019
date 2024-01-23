#include "Pin.h"

PIN::PIN()
{
	    reloj_registro = ' ';
			moder_registro = 0;
	    pin_registro = 0;
			otyper_registro = 0; 
			ospeedr_registro = 0;
			pupdr_registro = 0;
			//salida_entrada_registro = 0;
}

PIN::PIN(char R, short MO, short N, bool OTY, short OSP, short PUP)
{
			reloj_registro = R;
			moder_registro = MO;
	    pin_registro = N;
			otyper_registro = OTY; 
			ospeedr_registro = OSP;
			pupdr_registro = PUP;
			//salida_entrada_registro = S;
	
	switch (R) // verifica que puerto quiero (del A hasta el H) y enmascara segun: MODER(MO), PIN(N), OTYPER(OTY), OSPEEDR(OSP) y PUPDR(PUP)
			{
				case 'A': 
					RCC->AHB1ENR |= (1UL<<0);
					GPIOA -> MODER |= (MO<<2*N);
			    GPIOA -> OTYPER = (1*OTY<<N);
			    GPIOA -> OSPEEDR |= (OSP<<2*N);
				  GPIOA -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'B': 
					RCC->AHB1ENR |= (1UL<<1);
					GPIOB -> MODER |= (MO<<2*N);
			    GPIOB -> OTYPER = (1*OTY<<N);
			    GPIOB -> OSPEEDR |= (OSP<<2*N);
				  GPIOB -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'C': 
					RCC->AHB1ENR |= (1UL<<2);
					GPIOC -> MODER |= (MO<<2*N);
			    GPIOC -> OTYPER = (1*OTY<<N);
			    GPIOC -> OSPEEDR |= (OSP<<2*N);
				  GPIOC -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'D': 
					RCC->AHB1ENR |= (1UL<<3);
					GPIOD -> MODER |= (MO<<2*N);
			    GPIOD -> OTYPER = (1*OTY<<N);
			    GPIOD -> OSPEEDR |= (OSP<<2*N);
				  GPIOD -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'E': 
					RCC->AHB1ENR |= (1UL<<4);
					GPIOE -> MODER |= (MO<<2*N);
			    GPIOE -> OTYPER = (1*OTY<<N);
			    GPIOE -> OSPEEDR |= (OSP<<2*N);
				  GPIOE -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'F': 
					RCC->AHB1ENR |= (1UL<<5);
					GPIOF -> MODER |= (MO<<2*N);
			    GPIOF -> OTYPER = (1*OTY<<N);
			    GPIOF -> OSPEEDR |= (OSP<<2*N);
				  GPIOF -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'G': 
					RCC->AHB1ENR |= (1UL<<6);
					GPIOG -> MODER |= (MO<<2*N);
			    GPIOG -> OTYPER = (1*OTY<<N);
			    GPIOG -> OSPEEDR |= (OSP<<2*N);
				  GPIOG -> PUPDR |= (PUP<<2*N);
					break;
					
				case 'H': 
					RCC->AHB1ENR |= (1UL<<7);
					GPIOH -> MODER |= (MO<<2*N);
			    GPIOH -> OTYPER = (1*OTY<<N);
			    GPIOH -> OSPEEDR |= (OSP<<2*N);
				  GPIOH -> PUPDR |= (PUP<<2*N);
					break;
					
				default:
					break;
			}
			
}

void PIN::cambiar_salida(bool S) // función que permite cambiar la salida (1/0) del puerto
{     
		switch(get_reloj())
				{
					case 'A':
						 if(S==1)
						 {
								GPIOA -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOA -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'B':
						 if(S==1)
						 {
								GPIOB -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOB -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'C':
						 if(S==1)
						 {
								GPIOC -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOC -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'D':
						 if(S==1)
						 {
								GPIOD -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOD -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'E':
						 if(S==1)
						 {
								GPIOE -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOE -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'F':
						 if(S==1)
						 {
								GPIOF -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOF -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'G':
						 if(S==1)
						 {
								GPIOG -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOG -> ODR &= ~(1UL<<get_pin());
						 }

						break;
					case 'H':
						 if(S==1)
						 {
								GPIOH -> ODR |= (1UL<<get_pin());
						 }else
						 {
								GPIOH -> ODR &= ~(1UL<<get_pin());
						 }
						break;			
					default:
						break;
				}

};

bool PIN::verificar_entrada() // función que permite verificar la entrada (1/0) del puerto
{
	  int j = pow( 2 , (float)get_pin()); // número de potencias de dos, segun el número de pin

	  switch(get_reloj())
		{
			case 'A':
				if(GPIOA -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOA ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'B':
				if(GPIOB -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOB ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'C':
				if(GPIOC -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOC ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'D':
				if(GPIOD -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOD ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'E':
				if(GPIOE -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOE ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'F':
				if(GPIOF -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOF ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'G':
				if(GPIOG -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOG ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;
			case 'H':
				if(GPIOH -> IDR & j )
				{
						for(int i =0; i<50000; i++){};
							
						if(GPIOH ->IDR & j )
						{
								return 1;
						}

				}else
				{
					return 0;
				}
				break;			
			default:
				break;
		}
    
}


PIN::~PIN(){}
