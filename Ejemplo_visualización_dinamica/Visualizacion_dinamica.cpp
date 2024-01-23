#include "Pin.h"

	PIN* HABC1 = new PIN('C',1,6,0,1,2);
	PIN* HABC2 = new PIN('C',1,5,0,1,2);
	PIN* HABC3 = new PIN('C',1,4,0,1,2);
	PIN* HABC4 = new PIN('F',1,5,0,1,2);
	PIN* LEDA = new PIN('C',1,11,0,1,2);
	PIN* LEDB = new PIN('D',1,2,0,1,2);
	PIN* LEDC = new PIN('C',1,10,0,1,2);
	PIN* LEDD = new PIN('C',1,12,0,1,2);
	PIN* LEDE = new PIN('F',1,4,0,1,2);
	PIN* LEDF = new PIN('F',1,6,0,1,2);
	PIN* LEDG = new PIN('F',1,7,0,1,2);
	
	PIN* ARRAY_HAB[4]={HABC1,HABC2,HABC3,HABC4};
	PIN* ARRAY_LEDS_DISPLY[7]={LEDA,LEDB,LEDC,LEDD,LEDE,LEDF,LEDG};

void habilitadores(int hab) // Función para habilitar la posición del display
{
	 ARRAY_HAB[hab] -> cambiar_salida(1);
	 for(int i=0; i<40000; i++){};
   ARRAY_HAB[hab] -> cambiar_salida(0);
}

int main (void)
{
	
	int S = 0x12, I = 0x79;
	int array_si[2] = {S,I};
	
	while(1)
	{
		for(int i=0; i<2; i++)
		{
			habilitadores(i);
			for(int j=0; j<7; j++)
					{
			      int prueba = pow(2,(float)i);
						if( (array_si[i] & prueba) == prueba)
						{
								ARRAY_LEDS_DISPLY[j]->cambiar_salida(0);
						}
						else
						{
								ARRAY_LEDS_DISPLY[j]->cambiar_salida(1);
						}
					}
		}
	}
	
}