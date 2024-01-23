#ifndef LCD_H
#define LCD_H 

#include "Pin.h"

// constantes para los pines D0 - D7 de la LCD
#define LCD_PIN_0 0
#define LCD_PIN_1 1
#define LCD_PIN_2 2
#define LCD_PIN_3 11
#define LCD_PIN_4 12
#define LCD_PIN_5 5
#define LCD_PIN_6 6
#define LCD_PIN_7 7
// constantes para los puertos D0 - D7 de la LCD
#define LCD_PRT_0 GPIOB
#define LCD_PRT_1 GPIOB
#define LCD_PRT_2 GPIOB
#define LCD_PRT_3 GPIOB
#define LCD_PRT_4 GPIOB
#define LCD_PRT_5 GPIOB
#define LCD_PRT_6 GPIOB
#define LCD_PRT_7 GPIOB
// constantes para los pines de E RS y RW
#define LCD_PIN_E 9
#define LCD_PIN_RS 8
#define LCD_PIN_RW 10
// constantes para los puertos de E RS y RW
#define LCD_PRT_E GPIOB
#define LCD_PRT_RS GPIOB
#define LCD_PRT_RW GPIOB

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
	LCD_Delay(5000);
	LCD_PE ->cambiar_salida(0);
}

void LCD_InsertarDato (unsigned char Dato)
{
	LCD_InicializarUnCaracteroComando(Dato);
	LCD_PRS ->cambiar_salida(1);
	LCD_PRW ->cambiar_salida(0);
	LCD_PE ->cambiar_salida(1);
	LCD_Delay(5000);
	LCD_PE ->cambiar_salida(0);
}

void LCD_MostrarUnaCadenaChar (const char *Cadena_Char)
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

void LCD_MostrarEntero(int numero )
{
	char buffer[20];
	sprintf(buffer,"%d", numero);
	LCD_MostrarUnaCadenaChar(buffer);
}

void LCD_MostrarFlotante (float Numero)
{
	char buffer[5];
	snprintf(buffer,6,"%f", Numero);
	LCD_MostrarUnaCadenaChar(buffer);
}

void LCD_posicionarCursor(short fila, short Posicion)
{
	if(fila == 1)
	{
		LCD_InsetarComando(0x80+(Posicion-1));
		
	}else if(fila == 2)
	{
		LCD_InsetarComando(0xC0+(Posicion-1));
	}else
	{
		char Cadena_Alert[] = {'F','i','l','a',' ','o',' ','P','o','s',' ','E','r','r','o','r'};
		LCD_MostrarUnaCadenaChar(Cadena_Alert);
	}
	
	
}
#endif