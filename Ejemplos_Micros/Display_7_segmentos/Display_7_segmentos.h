#ifndef DISPLY_S
#define DISPLY_S

#include <stdio.h>
#include <vector>
#include "math.h"
#include "stm32f7xx.h"

using namespace std;

class DISPLY
{
	private:
		static const int cero = 0b0111111; //0
		static const int uno = 0b0000110;  //1
	  static const int dos = 0b1011011; // 2
	  static const int tres = 0b1001111;  //3
    static const int cuatro = 0b1100110; //4
	  static const int cinco = 0b1101101;  //5
	  static const int seis = 0b1111100;  //6
	  static const int siete = 0b1000111;  //7
    static const int ocho = 0b1111111;  //8
	  static const int nueve = 0b1100111; //9
	
	public: 
		
	// metodos getters
	  int get_cero() { return cero; };
		int get_uno(){ return uno; };
		int get_dos(){ return dos;};
		int get_tres(){ return tres; };
		int get_cuatro(){ return cuatro; };
		int get_cinco(){ return cinco; };
		int get_seis(){ return seis; };
		int get_siete(){ return siete; };
		int get_ocho(){ return ocho; };
		int get_nueve(){ return nueve; };
	
	// metodos 
		vector<int> devolver_vector_numero (int n);
		
	// constructores
		
		DISPLY();
		~DISPLY();
	
};

#endif