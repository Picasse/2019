#include <LiquidCrystal.h>
#include <Math.h>
//variables globales
float Vdistancia =0,Vcorriente =0,Corriente=0, ADCcorriente=0, ADCRL=0, Voltaje=0, Potencia = 0,
  PotenciaRequerida =0, resta =0, denominador=0,CopiaSensDistADCValue=0,
  VMicro1=0,Vout=0,R=0,Num=0,Den=0,Distancia=0,base=0,VoltD=0,OnOff=0;
int bloc=0,PWM=0;
  
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  // open a serial connection
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(6,OUTPUT);
}

void loop() {
  OnOff = analogRead(A3);
  
  
  Vdistancia = analogRead(A0); //lee el sensor de distancia
  
  
  if(bloc=0){
    CopiaSensDistADCValue=Vdistancia;
    bloc=1;
    }
  if(bloc=1){
    
    if(CopiaSensDistADCValue=!Vdistancia){//si el sharp cambia
      CopiaSensDistADCValue=Vdistancia;
      analogWrite(A3, 1023);//manda 5v por vout micro
      leeCVcalcP(); //lee v & i y calcula P leida en la resistencia y Calcula la resistencia que hay
      CalPreq();//calcula la potencia requerida
      }//fin sharp si cambia
      
      if(CopiaSensDistADCValue=Vdistancia){//si el sharp no cambia
        leeCVcalcP();
        CalPreq();//calcula la potencia requerida
        MandePotencia();
        
      }//fin shap no cambia
    }//fin del bloc =1


  if(OnOff!=0){
  CalcDist();
  lcd.setCursor(0, 0);
  lcd.print("D:");
  lcd.setCursor(2, 0);
  lcd.print(Distancia);
  
  lcd.setCursor(8, 0);
  lcd.print("PR:");
  lcd.setCursor(11, 0);
  lcd.print(PotenciaRequerida);
  
  lcd.setCursor(0, 1);
  lcd.print("P.Med:");
  lcd.setCursor(6, 1);
  lcd.print(Potencia);

  lcd.setCursor(11, 1);
  lcd.print("On.");
    }else{
      lcd.setCursor(0, 0);
       lcd.print("               ");
       lcd.setCursor(0, 1);
       lcd.print("           ");
      lcd.setCursor(11, 1);
      lcd.print("Off");}
  //muestra la informacion
  

}
//**********FUNCIONES******
  void leeCVcalcP(){
  int sensorVal = analogRead(A0);
  
    
    //*******lee Corriente, voltaje y calcula potencia medida en la resistencia 
    ADCcorriente = analogRead(A1); //lee corriente de la resistencia
    ADCRL = analogRead(A2);  //lee voltaje de la resistencia
    Corriente= (0.0500611*ADCcorriente)-25.04865922+0.018;
    Voltaje=(0.00651773*ADCRL)-0.00098417;
    Potencia = Corriente*Voltaje; //calcula la potencia actual
    R=Voltaje/Corriente; //calcula que resistencia hay actualmente
    }
  void CalPreq(){//*******Potencia requerida sharp (depende solo del sharp)
    resta = ((0.0048883*Vdistancia)-0.00073183);
    denominador = pow(resta,1.192);
    PotenciaRequerida=(6.26715/denominador)-1.25; //Calcula la potencia que se requiere segun el sharp
    }
  void MandePotencia(){
    Num=PotenciaRequerida*R;
    Den=1.2*(sqrt(R*PotenciaRequerida)); 
    VMicro1=Num/Den; //Calcula el voltaje que debe mandar
    //Vout=(204.57*(VMicro1))+0.151; //convierte a adc el Voutmicro
    PWM = ( (256*VMicro1)/(5) )-1; //convierte el Vmicro en pwm
    analogWrite(6, PWM);
    }
  void CalcDist(){
    VoltD=(Vdistancia-0.151)/(204.57); //lee el valor adc y lo pasa a voltaje
    base=VoltD;  //base de la ecuacion de abajo
    Distancia=27.854*(pow(base,-1.192)); //Voltaje en distancia
    }
