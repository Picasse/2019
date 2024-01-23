#include "Display_7_segmentos.h"

DISPLY::DISPLY(){}
	
vector<int> DISPLY::devolver_vector_numero(int n)
{
	 int prueba = 0;
   vector <int> vector_leds(8);
	
	 switch(n)
   {
		 case 0: 
			  for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_cero() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}
        return vector_leds;
			 break;
		 case 1: 
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_uno() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}
			 break;
		 case 2: 
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_dos() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}
			 break;
		 case 3:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_tres() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 4:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_cuatro() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 5:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_cinco() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 6:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_seis() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 7:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_siete() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 8:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_ocho() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 case 9:
			 	for(int i=0; i<8; i++)
				{
						prueba = pow(2,(float)i);
						if(get_nueve() & prueba)
						{
								vector_leds[i] = 1;
						}
						else
						{
								vector_leds[i] = 0;
						}
				}			 
			 break;
		 default:
			 break;
	 }
}

