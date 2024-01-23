#include "Pin.h"
#include "LCD.h"

char matriz_mario[8][8] = {{0x6,0xF,0x1C,0x18,0x18,0x1C,0xF,0x6},
													 {0x0,0x7,0xF,0xC,0xC,0xF,0x7,0x0},
													 {0x1,0x3,0x3,0x3,0x5,0x5,0x5,0x2},
													 {0x1F,0x1F,0x1F,0x19,0x11,0x18,0x1,0x3},
													 {0x10,0x10,0x1F,0x8,0xE,0x11,0x1E,0x1C},
													 {0X1,0X0,0X7,0X9,0X11,0X15,0X15,0X15},
													 {0X0,0X10,0X1F,0X11,0X11,0X1F,0X0,0X0},
													 {0X8,010,0X1C,0X12,0X11,0X15,0X15,0X15},
													};

char Frase_pacman_grande[9] = {'P','a','c','-','M','a','n','-','G'};
char Frase_pacman_chiquito[9] = {'P','a','c','-','M','a','n','-','C'};
//char Frase_mario1[5] = {'S','U','P','E','R'};
//char Frase_mario[5] = {'M','A','R','I','O'};
													
void Mostrar_Logos();

int main(void)
{
	LCD_InicializarLCD();
	
	LCD_CaracterEspecial(matriz_mario);
	
	while(1)
	{
		Mostrar_Logos();
		for(int m=0; m<200000; m++){};
	}
}

void Mostrar_Logos ()
{
 for(int j= 0; j<8; j++)
	{
		
	   if(j<1)
		 {
			for(int m = 0; m<1500000; m++){};
			LCD_InsetarComando(0x81);
			LCD_InsertarDato(j);
			LCD_InsetarComando(0x83);
			LCD_MostrarUnaCadenaChar(Frase_pacman_grande);
			for(int m = 0; m<1500000; m++){};
			LCD_InsetarComando(0x1);
		 }else if(j==1)
		 {
			LCD_InsetarComando(0x84);
			LCD_InsertarDato(j);
			LCD_InsetarComando(0x85);
			LCD_MostrarUnaCadenaChar(Frase_pacman_chiquito);
			for(int m = 0; m<1500000; m++){};
			LCD_InsetarComando(0x1);
		 } else
		 {
			 if(j<5)
			 {
					LCD_InsetarComando(0x84+j);
					LCD_InsertarDato(j);
			 }else
			 {
				  LCD_InsetarComando(0xC1+j);
					LCD_InsertarDato(j);
			 }
		 }
	}
}