#include <AD7887.h>

//=================================================================
//
//  The adc instance
//
#define SELPIN 10   //Selection Pin 
#define DATAOUT 9   //MOSI 
#define DATAIN  8   //MISO 
#define SPICLOCK 7  //Clock 
AD7887 powerSensor = AD7887(SELPIN, DATAOUT, DATAIN, SPICLOCK);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int currVal = powerSensor.readADC();
  Serial.println(currVal);
}

