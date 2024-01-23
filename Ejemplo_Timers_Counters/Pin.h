#ifndef PIN_H
#define PIN_H 

#include <stdio.h>
#include "stm32f7xx.h"
#include "stm32f746xx.h"
#include <math.h>

class PIN
{ 
		
  private: 
		// variables delos pines
	  GPIO_TypeDef *reloj;
	  short moder_registro; // entrada, salida, analogo o altenante 
	  short pin_registro; // numero de pin que queremos activar.
	  bool otyper_registro; // push-pull o open drain.
	  short ospeedr_registro; // velocidad alt, media o baja.
		short pupdr_registro; // pull-up o pull-down.
		
	public:
    
	 // setters
		void set_pin (short N)
		{
			pin_registro = N;
		}
		void set_moder (short MO)
		{
			moder_registro = MO;
		}
		void set_otyper (bool OTY)
		{
		  otyper_registro = OTY;
		}
		void set_ospeedr (short OSP) 
		{
			ospeedr_registro = OSP;
		}
		void set_pupdr (short PUP)
		{
			pupdr_registro = PUP;
		}
		
		// metodos
    void cambiar_salida(bool S);
		bool verificar_entrada();
		
		//getters
		short get_moder () { return moder_registro; }
    short get_pin () { return pin_registro; }		
		bool get_otyper () { return otyper_registro; }
		short get_ospeedr () { return ospeedr_registro; }
		short get_pupdr () { return pupdr_registro; }
		//bool get_salida_entrada () { return salida_entrada_registro; }
		
		//constructores
		PIN();
		PIN(GPIO_TypeDef *p, short MO, short N, bool OTY, short OSP, short PUP);
		~PIN();
		
};

#endif