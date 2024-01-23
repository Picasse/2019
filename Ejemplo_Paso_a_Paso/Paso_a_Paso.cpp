#include "LCD.h"

using namespace std;

float dato = 0;

int main(void)
{
//	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC -> AHB1ENR |= 0xE;
//	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	
	RCC -> APB2ENR |= 0x100;
	
	GPIOC -> MODER |= 0xC0;  // 11 00 00 00
	
	ADC1 -> CR1 |= 0x0;
	ADC1 -> CR2 |= 0x1;
	ADC1 -> SMPR1 |= 0x7FFFFFF;
	ADC1 -> SMPR2 |= 0x37777777;
	ADC1 -> SQR3 = 13; 
	
//	GPIOG -> MODER |= 0x55;
//	GPIOG -> OTYPER = 0x0;
//	GPIOG -> OSPEEDR |= 0x55;
//	GPIOG -> PUPDR |= 0x55;
	
	LCD_InicializarLCD();
	
  LCD_MostrarUnaCadenaChar(" Voltaje: ");
	
	int vector[4] = {0,0,0,1};
	int contador = 0; 
	
	while(1)
	{
		ADC1 -> CR2 |= 0x40000000;
    dato = ADC1->DR;
		LCD_posicionarCursor(1,11);
		dato = (dato*8050)/10000000;	
		LCD_MostrarFlotante(dato);
    LCD_InsetarComando(0x80);	
	}
}