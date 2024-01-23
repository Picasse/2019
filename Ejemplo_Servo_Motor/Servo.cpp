#include "LCD.h"

int pasos = 0; 
float dato = 0; 
double grados = 0;

int main(void)
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
//	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	
	RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00
	//   0     0     0     0     0     0     0     4

	GPIOC -> MODER |= 0x7;
	GPIOC -> OTYPER = 0x0;
	GPIOC -> OSPEEDR |= 0x55;
	GPIOC -> PUPDR |= 0x4;
	
	ADC1 -> CR1 |= 0x0;
	ADC1 -> CR2 |= 0x1;
	ADC1 -> SMPR1 |= 0x7FFFFFF;
	ADC1 -> SMPR2 |= 0x37777777;
	ADC1 -> SQR3 = 10; 
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10);
	
	LCD_InicializarLCD();
	
  LCD_MostrarUnaCadenaChar(" Voltaje: ");
	LCD_posicionarCursor(2,0);
	LCD_MostrarUnaCadenaChar(" Grados: ");
	
	while(1)
	{
		ADC1 -> CR2 |= 0x40000000;
    dato = ADC1->DR;
		grados = ADC1->DR;
		pasos = (ADC1->DR*75)/256;
		
		LCD_posicionarCursor(1,11);
		dato = (dato*8050)/10000000;	
		LCD_MostrarFlotante(dato);
    LCD_InsetarComando(0x80);	
		LCD_posicionarCursor(2,10);
		grados = (dato*180)/3.3;	
		LCD_MostrarFlotante(grados);
    LCD_InsetarComando(0x80);		
	}
}

extern "C"
{
	void SysTick_Handler(void)
	{
		while((ADC1->SR &= 0x2)==1){}
		GPIOC -> ODR |= (1UL<<1);
		for(int i = 0; i<pasos; i++){}
		GPIOC -> ODR &= ~(1UL<<1);
	}
}