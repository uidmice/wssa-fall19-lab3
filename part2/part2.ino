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
  sensor.readMagData();
  SerialUSB.print("\nMagnetometer:\n X = ");
  SerialUSB.print(sensor.magData.x*0.1, 1);
  SerialUSB.println(" uT");
  SerialUSB.print(" Y = ");
  SerialUSB.print(sensor.magData.y*0.1, 1);
  SerialUSB.println(" uT");
  SerialUSB.print(" Z = ");
  SerialUSB.print(sensor.magData.z*0.1, 1);
  SerialUSB.println(" uT");

  delay(10);
}
