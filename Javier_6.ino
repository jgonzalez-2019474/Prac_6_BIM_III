 /*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: 
 * CARNE: 
 * Proyecto:
*/
//Librerias
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_ADXL345.h>
#include <LedControl.h>

//Directivas
#define ancho_matriz 8 
#define alto_matriz 8
#define DIN 12 
#define CLK 11
#define CS 10

//Variables
float xg,yg,zg;
float soh;
float tilt;
float angulo;

const byte Desnivel_Negativo5[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11111101,
  B11111101,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Negativo4[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11111001,
  B11111001,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Negativo3[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11111011,
  B11111011,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Negativo2[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11110011,
  B11110011,
  B11111111,
  B00000000,
  B00000000
  };

const byte Desnivel_Negativo1[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11110111,
  B11110111,
  B11111111,
  B00000000,
  B00000000
  };

const byte Centro[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11100111,
  B11100111,
  B11111111,
  B00000000,
  B00000000};

const byte Desnivel_Positivo1[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11101111,
  B11101111,
  B11111111,
  B00000000,
  B00000000};

const byte Desnivel_Positivo2[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11001111,
  B11001111,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Positivo3[8] = {
  B00000000,
  B00000000,
  B11111111,
  B11011111,
  B11011111,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Positivo4[8] = {
  B00000000,
  B00000000,
  B11111111,
  B10011111,
  B10011111,
  B11111111,
  B00000000,
  B00000000
};

const byte Desnivel_Positivo5[8] = {
  B00000000,
  B00000000,
  B11111111,
  B10111111,
  B10111111,
  B11111111,
  B00000000,
  B00000000
};

//Constructores
LedControl ledMatrix = LedControl(DIN,CLK,CS,1);
ADXL345 NIVEL = ADXL345();
void setup() {
   Serial.begin(9600);    
   ledMatrix.shutdown(0,false);    
   ledMatrix.setIntensity(0,15);  //Brilo a la mitad 
   ledMatrix.clearDisplay(0);    //limpio el display
   NIVEL.powerOn();           
   NIVEL.setRangeSetting(8);       //Definir el rango

}

void loop() {
   nivelacion();
   animacion();
   
}

void nivelacion(){
  int sumax = 0;
  int x, y, z;
  NIVEL.readAccel(&x, &y, &z);
     xg = x*0.0039;
     yg = y*0.0039;
     zg = z*0.0039;
     soh = xg/zg;

     tilt = atan(soh)*57.296;
}

void animacion(){
  Serial.println(tilt);
  if((abs(tilt) > 90)){  
    for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo5[i]);
      }
    for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo5[i]);
      }
  }
  
  if((tilt < -60) && ( tilt >= -90) ){  
    for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo5[i]);
      }
  }
  
  if((tilt < -45) && (tilt >= -60 )){ 
    for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo4[i]);
      }
  }
  if((tilt < -30) && (tilt >= -45 )){  
    for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo3[i]);
      }
  }

  if((tilt < -15) && (tilt >= -30 )){
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo2[i]);
      }
  }
  
  if((tilt < -5) && (tilt >= -15 )){ 
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Negativo1[i]);
      }
  }
  
  if(tilt >= -5 && tilt <= 5){  
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Centro[i]);
      }
  }

  if((tilt > 5) && (tilt <= 15 )){  
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo1[i]);
      }
  }
  
  if((tilt > 15) && (tilt <= 30 )){  
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo2[i]);
      }
  }

  if((tilt > 30) && (tilt <= 45 )){  
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo3[i]);
      }
  }
  
  if((tilt > 45) && (tilt <= 60 )){  
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo4[i]);
      }
  }
  if((tilt > 60) && (tilt <= 90 )){ 
   for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, Desnivel_Positivo5[i]);
      }
  }
  }
