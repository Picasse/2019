#ifndef LCD_H
#define LCD_H 

#include "Pin.h"

// constantes para los pines D0 - D7 de la LCD
#define LCD_PIN_0 0
#define LCD_PIN_1 1
#define LCD_PIN_2 2
#define LCD_PIN_3 3
#define LCD_PIN_4 4
#define LCD_PIN_5 5
#define LCD_PIN_6 6
#define LCD_PIN_7 7
// constantes para los puertos D0 - D7 de la LCD
#define LCD_PRT_0 GPIOD
#define LCD_PRT_1 GPIOD
#define LCD_PRT_2 GPIOD
#define LCD_PRT_3 GPIOD
#define LCD_PRT_4 GPIOD
#define LCD_PRT_5 GPIOD
#define LCD_PRT_6 GPIOD
#define LCD_PRT_7 GPIOD
// constantes para los pines de E RS y RW
#define LCD_PIN_E 9
#define LCD_PIN_RS 8
#define LCD_PIN_RW 10
// constantes para los puertos de E RS y RW
#define LCD_PRT_E GPIOD
#define LCD_PRT_RS GPIOD
#define LCD_PRT_RW GPIOD

// Inicializar los objetos PIN para la LCD 
//  Pines configurados para datos
PIN* LCD_D0 = new PIN(LCD_PRT_0, 1, LCD_PIN_0, 0, 1, 1);
PIN* LCD_D1 = new PIN(LCD_PRT_1, 1, LCD_PIN_1, 0, 1, 1);
PIN* LCD_D2 = new PIN(LCD_PRT_2, 1, LCD_PIN_2, 0, 1, 1);
PIN* LCD_D3 = new PIN(LCD_PRT_3, 1, LCD_PIN_3, 0, 1, 1);
PIN* LCD_D4 = new PIN(LCD_PRT_4, 1, LCD_PIN_4, 0, 1, 1);
PIN* LCD_D5 = new PIN(LCD_PRT_5, 1, LCD_PIN_5, 0, 1, 1);
PIN* LCD_D6 = new PIN(LCD_PRT_6, 1, LCD_PIN_6, 0, 1, 1);
PIN* LCD_D7 = new PIN(LCD_PRT_7, 1, LCD_PIN_7, 0, 1, 1);
//  Pines configurador para E, RS y RW
PIN* LCD_PE = new PIN(LCD_PRT_E, 1, LCD_PIN_E, 0, 1, 1);
PIN* LCD_PRS = new PIN(LCD_PRT_RS, 1, LCD_PIN_RS, 0, 1, 1);
PIN* LCD_PRW= new PIN(LCD_PRT_RW, 1, LCD_PIN_RW, 0, 1, 1);
//  Creación de arreglo para pines de datos
PIN* ARRAY_PDATOS[8] = {LCD_D0,LCD_D1,LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};
// Arreglo para guardar las posiciones especiales
char CGRAM [8] = {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47};

void LCD_Delay (int tiempo_delay) // Función para un retraso
{
  volatile int delay = 0;
	
	for(delay = 0; delay<tiempo_delay; delay++);
}

void LCD_InicializarUnCaracteroComando(unsigned char ch) // Función para poner unos en los teminales D0 - D7
{
  volatile int Prueba_con_potencias =0;
	
	for(int i=0; i<8; i++)
	{
		Prueba_con_potencias = pow(2,(float)i);
		
		if((ch & Prueba_con_potencias)== Prueba_con_potencias)
		{
			ARRAY_PDATOS[i] ->cambiar_salida(1);
		}else
		{
			ARRAY_PDATOS[i] ->cambiar_salida(0);
		}
	}
}

void LCD_InsetarComando (unsigned char Comando)
{
	LCD_InicializarUnCaracteroComando(Comando);
	LCD_PRS ->cambiar_salida(0);
	LCD_PRW ->cambiar_salida(0);
	LCD_PE ->cambiar_salida(1);
	LCD_Delay(40000);
	LCD_PE ->cambiar_salida(0);
}

void LCD_InsertarDato (unsigned char Dato)
{
	LCD_InicializarUnCaracteroComando(Dato);
	LCD_PRS ->cambiar_salida(1);
	LCD_PRW ->cambiar_salida(0);
	LCD_PE ->cambiar_salida(1);
	LCD_Delay(40000);
	LCD_PE ->cambiar_salida(0);
}

void LCD_MostrarUnaCadenaChar (char *Cadena_Char)
{
	while(*Cadena_Char)
	{
		LCD_InsertarDato(*Cadena_Char++);
	}
}

void LCD_InicializarLCD () 
{
	LCD_InsetarComando(0x1); 
	LCD_InsetarComando(0x2);
	LCD_InsetarComando(0x3C); 
	LCD_InsetarComando(0xC); 
	LCD_InsetarComando(0x6); 
  LCD_InsetarComando(0x80);	
}

void LCD_CaracterEspecial(char Arreglo_Caracter_Especial[8][8])
{
	LCD_InsetarComando(CGRAM[0]);
	for(int in1 = 0; in1<8; in1++)
	{
		for(int in2 = 0; in2<8; in2++)
		{
			 LCD_InsertarDato(Arreglo_Caracter_Especial[in1][in2]);
		}
	}
}
#endif