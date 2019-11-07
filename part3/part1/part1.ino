#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
#include <FreeRTOS_ARM.h>

LSM303C myIMU;

void setup() {
  //set up I2C bus
  Wire1.begin();
  Wire1.setClock(400000L);//set up I2C bus clock to 400kHz
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

  //Set up serial
  SerialUSB.begin(57600);//initialize SerialUSB monitor, maximum reliable baud for 3.3V/8Mhz ATmega328P is 57600
  while(!SerialUSB);

  //Set up IMU
  if (myIMU.begin(
        MODE_I2C,
        MAG_DO_40_Hz,
        MAG_FS_16_Ga,
        MAG_BDU_ENABLE,
        MAG_OMXY_HIGH_PERFORMANCE,
        MAG_OMZ_HIGH_PERFORMANCE,
        MAG_MD_CONTINUOUS,
        ACC_FS_2g,
        ACC_BDU_ENABLE,
        ACC_X_ENABLE | ACC_Y_ENABLE | ACC_Z_ENABLE,
        ACC_ODR_100_Hz
      ) != IMU_SUCCESS || myIMU.WHO_AM_I())
  {
    SerialUSB.println("Failed setup.");
    while (1);
  }

}


void loop(){
   digitalWrite(6, HIGH);

  //  SerialUSB.println("start");
  for (int i = 0; i < 10000; i ++) {
    myIMU.MAG_ReadReg(MAG_WHO_AM_I);

  }
  //    SerialUSB.println("end");

  digitalWrite(6, LOW);

  

  delay(3000);
}
