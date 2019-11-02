#include <SPI.h>
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;


void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  while(!SerialUSB);
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();

}

void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  SerialUSB.println("start");
  for (int i = 0; i < 10000; i ++){
      sensor.readReg(FXOS8700CQ_WHO_AM_I);

  }
    SerialUSB.println("end");

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);


  delay(3000);
}
