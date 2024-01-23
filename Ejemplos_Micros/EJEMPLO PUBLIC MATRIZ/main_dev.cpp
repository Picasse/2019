#include <stdio.h>
#include "STM32F7xx.h"

int time=1000;      //n ciclos de maquina
int dato=0, cont=0, cont1=0, cont2=0;
bool display=0;
bool res=0;
int i=0,j=0,l=0;

int FRASE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x4B,0x4B,0x4B,0x4B,0x7F,0,0,0x7F,0x18,0x18,0x18,0x7F,0,0,
	             0x43,0x43,0x43,0x43,0x7F,0,0,0x73,0x53,0x53,0x53,0x5F,0,0,0x5F,0x33,0x13,0x13,0x7F,0,0,
	             0x7F,0x43,0x43,0x43,0x7F,0,0,0x1F,0x13,0x13,0x13,0x7F,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pub_lic=0;
	
int dato1=0;
	


extern "C" {
		 
		void SysTick_Handler ( void )
		{
			  display=1;
			  cont1++;    //visualizacion dinamica matrices
			  cont2++;
			
 		if(cont1>19){
					cont1=0;
			}
			
			
			if(cont2>99){
				  cont2=0;
					dato1++;
				  pub_lic++;
						if(pub_lic>60){
							pub_lic=0;
						}
			}
			
		}

		
}



int main(void)
{
	//***********************************************************************************************
	//CONFIGURACION "CLOCK"
	RCC->AHB1ENR = 0xFF;           //CLOCK PTA a PTH HABILITADOS
	
	//************************************************************************************************
	//CONFIGURACION DE PINES
				
	//HABILITADORES DISPLAY 1 (PC12 A PC15)
	//HABILITADORES MATRIZ 1 y 2 (PC0 a PC9)
			GPIOC->MODER   = 0x55055555;      //PC12 A PC15 -> OUTPUT
			GPIOC->OTYPER  = 0;               //PUSH PULL -> PC12 A PC15
			GPIOC->OSPEEDR = 0x55055555;      //MEDIUM SPEEED -> PC12 A PC15
			GPIOC->PUPDR   = 0x55055555;      //PULL-UP -> PC12 A PC15
	
	//HABILITADORES DISPLAY 2 (PE12 A PE15)        
	//FILAS DE LAS MATRICES (PE0 a PE6)
			GPIOE->MODER   = 0x55501555;      //PE12 A PE15 -> OUTPUT
			GPIOE->OTYPER  = 0;               //PUSH PULL -> PE12 A PE15
			GPIOE->OSPEEDR = 0x55501555;      //MEDIUM SPEEED -> PE12 A PE15
			GPIOE->PUPDR   = 0x55501555;      //PULL-UP -> PE12 A PE15

	//HABILITADORES MATRIZ 3 y 4 (PF6 a PF15)
			GPIOF->MODER   = 0x55555000;      //(PF6 a PF15) -> OUTPUT
			GPIOF->OTYPER  = 0;               //PUSH PULL -> (PF6 a PF15)
			GPIOF->OSPEEDR = 0x55555000;      //MEDIUM SPEEED -> (PF6 a PF15)
			GPIOF->PUPDR   = 0x55555000;      //PULL-UP -> (PF6 a PF15)
	
	//********************************************************************************************
	//CONFIGURACION SYSTICK
			SystemCoreClockUpdate();
			SysTick_Config(SystemCoreClock/1000);         //1ms  
	
	//********************************************************************************************
	
	//********************************************************************************************	
	GPIOC->ODR = 0xF3FF;
	GPIOE->ODR = 0xF000;
	GPIOF->ODR = 0xFFC0;
	
	GPIOE->ODR |=  (1UL << 0);             
	GPIOE->ODR |=  (1UL << 1);
	GPIOE->ODR |=  (1UL << 2);
	GPIOE->ODR |=  (1UL << 3);
	GPIOE->ODR |=  (1UL << 4);
	GPIOE->ODR |=  (1UL << 5);
	GPIOE->ODR |=  (1UL << 6);
	
		
	while(true){        //bucle infinito

			if (display==1){  
								
				//VISUALIZACION DINAMICA MATRICES
				switch (cont1)                 
				{
						case 0:  GPIOF->ODR |= (1UL<<15); GPIOC->ODR &= ~(1UL<<0);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+19]; break;
						case 1:  GPIOC->ODR |= (1UL<<0);  GPIOC->ODR &= ~(1UL<<1);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+18];	break;
						case 2:  GPIOC->ODR |= (1UL<<1);  GPIOC->ODR &= ~(1UL<<2);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+17]; break;
						case 3:  GPIOC->ODR |= (1UL<<2);  GPIOC->ODR &= ~(1UL<<3);  GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+16]; break;
						case 4:  GPIOC->ODR |= (1UL<<3);  GPIOC->ODR &= ~(1UL<<4);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+15]; break;
						case 5:  GPIOC->ODR |= (1UL<<4);  GPIOC->ODR &= ~(1UL<<5);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+14]; break;
					  case 6:  GPIOC->ODR |= (1UL<<5);  GPIOC->ODR &= ~(1UL<<6);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+13]; break;
						case 7:  GPIOC->ODR |= (1UL<<6);  GPIOC->ODR &= ~(1UL<<7);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+12];	break;
						case 8:  GPIOC->ODR |= (1UL<<7);  GPIOC->ODR &= ~(1UL<<8);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+11]; break;
						case 9:  GPIOC->ODR |= (1UL<<8);  GPIOC->ODR &= ~(1UL<<9);  GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+10]; break;
						case 10: GPIOC->ODR |= (1UL<<9);  GPIOF->ODR &= ~(1UL<<6);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+9]; break;
						case 11: GPIOF->ODR |= (1UL<<6);  GPIOF->ODR &= ~(1UL<<7);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+8]; break;
						case 12: GPIOF->ODR |= (1UL<<7);  GPIOF->ODR &= ~(1UL<<8);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+7]; break;
					  case 13: GPIOF->ODR |= (1UL<<8);  GPIOF->ODR &= ~(1UL<<9);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+6];	break;
						case 14: GPIOF->ODR |= (1UL<<9);  GPIOF->ODR &= ~(1UL<<10);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+5]; break;
						case 15: GPIOF->ODR |= (1UL<<10); GPIOF->ODR &= ~(1UL<<11); GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+4]; break;
						case 16: GPIOF->ODR |= (1UL<<11); GPIOF->ODR &= ~(1UL<<12);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+3]; break;
						case 17: GPIOF->ODR |= (1UL<<12); GPIOF->ODR &= ~(1UL<<13);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+2]; break;
						case 18: GPIOF->ODR |= (1UL<<13); GPIOF->ODR &= ~(1UL<<14);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic+1]; break;
						case 19: GPIOF->ODR |= (1UL<<14); GPIOF->ODR &= ~(1UL<<15);	GPIOE->ODR = (GPIOE->ODR & 0xFF80)| FRASE[pub_lic];	break;
						default:  break;
				}//cierra switch
				
				display=0;
			}
			
				
	}//cierra while
	
}//cierra main