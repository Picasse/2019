#include "Pin.h"

  //  Creación objetos para display de unidades
	PIN* LEDA = new PIN('E',1,0,0,1,1);
	PIN* LEDB = new PIN('E',1,1,0,1,1);
	PIN* LEDC = new PIN('E',1,2,0,1,1);
	PIN* LEDD = new PIN('E',1,3,0,1,1);
	PIN* LEDE = new PIN('E',1,4,0,1,1);
	PIN* LEDF = new PIN('E',1,5,0,1,1);
  PIN* LEDG = new PIN('E',1,6,0,1,1);
	//  Creación objetos para display de decenas
  PIN* LEDA2 = new PIN('E',1,7,0,1,1);
	PIN* LEDB2 = new PIN('E',1,8,0,1,1);
	PIN* LEDC2 = new PIN('E',1,9,0,1,1);
	PIN* LEDD2 = new PIN('E',1,10,0,1,1);
	PIN* LEDE2 = new PIN('E',1,11,0,1,1);
	PIN* LEDF2 = new PIN('E',1,12,0,1,1);
  PIN* LEDG2 = new PIN('E',1,13,0,1,1);	

	//  Crecion objetos 
	// Arreglo de la clase PIN, para display
	PIN* ARR_PIN_DISPLY_UNI [7] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG};
	PIN* ARR_PIN_DISPLY_DEC [7] = {LEDA2, LEDB2, LEDC2, LEDD2, LEDE2, LEDF2, LEDG2};

void display_7_segmentos( PIN* ARREGLO, int n) // función que permite visualizar el numero 'n' en el display
{
	  int arreglo_dislay[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67}; // vector con las diferentes configuraciones para los numeros (0-9)
		int prueba = 0;
		PIN* ARREGLO_PRUEBA[7];
		
		for(int i=0; i<7; i++)
		{
			ARREGLO_PRUEBA[i] = &ARREGLO[i];
		}
		
		if((n>=0) && (n<=9))
		{
				for(int i=0; i<7; i++)
				{
						prueba = pow(2,(float)i);
						if( (arreglo_dislay[n] & prueba) == prueba)
						{
								ARREGLO_PRUEBA[i]->cambiar_salida(1);
						}
						else
						{
								ARREGLO_PRUEBA[i]->cambiar_salida(0);
						}
				}
		}	
}

int main(void){	
	  
		int contador_op_total = 0;
		int resultado = 0;
		int base = 16;
	  int potencia = 0;
	  int rescate = 0;
	  int operacion_total[4];
	  int teclado[4][4] = {{10,3,2,1},{11,6,5,4},{12,9,8,7},{15,14,0,13}}; 
			
		RCC -> AHB1ENR = 0x6;
			
		GPIOB -> MODER = 0x0;
		GPIOB -> OTYPER = 0x0;
		GPIOB -> OSPEEDR = 0x55;
		GPIOB -> PUPDR = 0xAA;
	
		GPIOC-> MODER = 0x55;
		GPIOC -> OTYPER = 0x0;
		GPIOC -> OSPEEDR = 0x55;
		GPIOC -> PUPDR = 0x55;
			
		while(1)
		{

		  for(int i =0; i<4; i++)
			{
				
				potencia = pow (2,(float)i);
				GPIOC->ODR = (potencia);
				rescate = base;
				for(int j=0; j<4; j++)
				{
				   base += pow(2, (float)j);
					 if((GPIOB->IDR & 0xFF) == base)
					 {
					   if(contador_op_total == 0)
						 {
							 if(teclado[i][j]<10)
							 {
								 operacion_total[contador_op_total] = teclado[i][j];
								 display_7_segmentos(ARR_PIN_DISPLY_UNI[6],teclado[i][j]);
								 contador_op_total++;
							 }
						 }else if(contador_op_total == 1)
						 {
							 
               if(teclado[i][j]<10)
							 {
								 contador_op_total--;
								 
								 display_7_segmentos(ARR_PIN_DISPLY_DEC[6],operacion_total[contador_op_total]);
								 operacion_total[contador_op_total] = (operacion_total[contador_op_total]*10) + teclado[i][j];
								 display_7_segmentos(ARR_PIN_DISPLY_UNI[6],teclado[i][j]);
								 
								 contador_op_total++;
								 
							 } else
								{
									operacion_total[contador_op_total] = teclado[i][j];
									
									contador_op_total++;
								}

						 }else if(contador_op_total == 2)
							{
								 if(teclado[i][j]<10)
								 {
									 operacion_total[contador_op_total] = teclado[i][j];
									 display_7_segmentos(ARR_PIN_DISPLY_UNI[6],teclado[i][j]);
									 contador_op_total++;
								 }
							}else if(contador_op_total == 3)
								{
									 if(teclado[i][j]<10)
									 {
										 contador_op_total--;
										 
										 display_7_segmentos(ARR_PIN_DISPLY_DEC[6],operacion_total[contador_op_total]);
										 operacion_total[contador_op_total] = (operacion_total[contador_op_total]*10) + teclado[i][j];
										 display_7_segmentos(ARR_PIN_DISPLY_UNI[6],teclado[i][j]);
										 
										 contador_op_total++;
										 
									 }else
										{
											if(teclado[i][j] == 13)
												switch(operacion_total[1])
												{
													case 10: 
														resultado = operacion_total[0] + operacion_total[2];
													  if(resultado>9)
														{ 
															display_7_segmentos(ARR_PIN_DISPLY_DEC[6],resultado/10);
															display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado%10);
															
														}else
															{
																display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado);
															}
														break;
													case 11: 
														resultado = operacion_total[0] - operacion_total[2];
													  if(resultado>9)
														{ 
															display_7_segmentos(ARR_PIN_DISPLY_DEC[6],resultado/10);
															display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado%10);
															
														}else
															{
																display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado);
															}
														break;
													case 12:
														resultado = operacion_total[0] * operacion_total[2];
													  if(resultado>9)
														{ 
															display_7_segmentos(ARR_PIN_DISPLY_DEC[6],resultado/10);
															display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado%10);
															
														}else
															{
																display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado);
															}														
														break;
													case 14:
														resultado = operacion_total[0] / operacion_total[2];
													  if(resultado>9)
														{ 
															display_7_segmentos(ARR_PIN_DISPLY_DEC[6],resultado/10);
															display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado%10);
															
														}else
															{
																display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado);
															}														
														break;
													case 15: 
														resultado = pow(operacion_total[0], (float)operacion_total[2]);
													  if(resultado>9)
														{ 
															display_7_segmentos(ARR_PIN_DISPLY_DEC[6],resultado/10);
															display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado%10);
															
														}else
															{
																display_7_segmentos(ARR_PIN_DISPLY_UNI[6],resultado);
															}
														break;
												}
										}
								}
						 
					 }
					 base = rescate;
				}
        base *=2;				
		  }
			
			potencia = 0;
			base = 16;
			rescate = 0;
			
			
		}
		
}