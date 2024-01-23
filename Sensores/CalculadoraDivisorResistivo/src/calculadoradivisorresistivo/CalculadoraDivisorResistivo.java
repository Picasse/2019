
package calculadoradivisorresistivo;

import static java.lang.Math.sqrt;
import java.util.Scanner;

public class CalculadoraDivisorResistivo {
    
    
    public static void main(String[] args) {
        int operacion;
        
        while(true){
        Scanner s =new Scanner(System.in); 
        double vcc,r1,r2,vr2,relacion,division,vAbsDif,mejor=1,error=0,porError=0;
        double R[]={0,0};
        double Res[][]={{10,100,1000,10000,100000,1000000},
                       {0 ,  0,   0,    0,     0,      0},
                       {12,120,1200,12000,120000,1200000},
                       {0 ,130,   0,    0,130000,      0},
                       {15,150,1500,15000,150000,1500000},
                       {0 ,  0,   0,    0,     0,      0},
                       {18,180,1800,18000,180000,1800000},
                       {20,200,2000,20000,200000,2000000},
                       {22,220,2200,22000,220000,2200000},
                       {24,240,2400,24000,240000,      0},
                       {27,270,2700,27000,270000,2700000},
                       {30,300,3000,30000,300000,3000000},
                       {33,330,3300,33000,330000,3300000},
                       {0 ,  0,   0,    0,     0,      0},
                       {39,390,3900,39000,390000,3900000},
                       {0 ,  0,   0,    0,     0,      0},
                       {47,470,4700,47000,470000,4700000},
                       {51,510,5100,51000,510000,      0},
                       {56,560,5600,56000,560000,5600000},
                       {62,620,6200,62000,620000,      0},
                       {68,680,6800,68000,680000,6800000},
                       {75,750,7500,75000,750000,7500000},
                       {82,820,8200,82000,820000,8200000},//1 o if saltar
                       {91,910,9100,91000,910000,      0},
                       };
        System.out.println("----CALCULADORA ELECTRONICA-----");
        System.out.println("1. Divisor Resistivo");   
        System.out.println("2. Ganancia Opamp"); 
        operacion=s.nextInt();
        
        switch(operacion){
            
        case 1:
        System.out.println("USE COMA, NO PUNTO");
        System.out.println("INGRESE VCC: ");
        vcc=s.nextDouble();
        System.out.println("INGRESE EL VALOR DE VOLTAJE QUE DESEA OBTENER EN R2: ");
        vr2=s.nextDouble();
        relacion=vr2/vcc;//relacion de resistencias perfecto
        
        if(relacion<1){
        for (int fila=0;fila<23;fila++){
            for(int col=0;col<6;col++){
                    r2=Res[fila][col];
                    for (int fila1=0;fila1<23;fila1++){
                    for(int col1=0;col1<6;col1++){
                        r1=Res[fila1][col1];
                        division=((r2)/(r1+r2));//relacion de resistencias que buscamos
                        vAbsDif=sqrt((division-relacion)*(division-relacion));
                        if(vAbsDif<mejor){
                            mejor=vAbsDif;
                            R[0]=Res[fila][col];
                            R[1]=Res[fila1][col1];
                            error=division;
                            }
                        }
                    }
                }
            }
        }//Fin relacion
        porError=(100-(error*100/relacion));
        porError=sqrt((porError)*(porError));
        System.out.println("El mejor es: "+mejor+" y son R1= "+R[1]+" y R2= "+R[0]+" Error: "+porError);
        System.out.println("");
        System.out.println("");
        break;
            
        case 2:
        double Rfsr;
        System.out.println("Digite la relacion Rf/R usando coma");
        Rfsr = s.nextDouble();
            for (int fila=0;fila<23;fila++){
            for(int col=0;col<6;col++){
                    r2=Res[fila][col];
                    for (int fila1=0;fila1<23;fila1++){
                    for(int col1=0;col1<6;col1++){
                        r1=Res[fila1][col1];
                        division=r2/r1;
                        vAbsDif=sqrt((division-Rfsr)*(division-Rfsr));
                        if(vAbsDif<mejor){
                            mejor=vAbsDif;
                            R[0]=Res[fila][col];
                            R[1]=Res[fila1][col1];
                            error=division;
                            }
                        }
                    }
                }
            }
        porError=(100-(error*100/Rfsr));
        porError=sqrt((porError)*(porError));
        System.out.println("El mejor es: "+mejor+" y son RF= "+R[0]+" y R= "+R[1]+" Error: "+porError);
        System.out.println("");
        System.out.println("");
        break;
            
        default:System.out.println("DIGITO INVALIDO.");
        }//fin del switch
        }//Fin loop while
    }//fin main 
}//fin programa
/*
for (int fila=0;fila<23;fila++){
            for(int col=0;col<6;col++){
                System.out.print(" "+Res[fila][col]);
                }System.out.println("");
            }
*/
