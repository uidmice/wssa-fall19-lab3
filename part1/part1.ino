// I2C interface by default
//
#include "Wire1.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

/*
   define DEBUG 1 in SparkFunLSM303C.cpp turns on debugging statements.
   Redefine to 0 to turn them off.
*/

/*
   SPI pins defined in SparkFunLSM303C.h for Pro Mini
   D10 -> SDI/SDO
   D11 -> SCLK
   D12 -> CS_XL
   D13 -> CS_MAG
*/

LSM303C myIMU;

void setup() {

  Wire1.begin();//set up I2C bus, comment out if using SPI mode
  Wire1.setClock(400000L);//clock stretching, comment out if using SPI mode

  SerialUSB.begin(57600);//initialize SerialUSB monitor, maximum reliable baud for 3.3V/8Mhz ATmega328P is 57600

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
      ) != IMU_SUCCESS)
  {
    SerialUSB.println("Failed setup.");
    while (1);
  }
}

void loop()
{
  float value;

  value = myIMU.readAccelX();

  // Assume that if X is not activated then none are (poor assumption, but demo)
  if ( !isnan(value) )
  {
    SerialUSB.print("\nAccelerometer:\n X = ");
    SerialUSB.println(value, 4);
    SerialUSB.print(" Y = ");
    SerialUSB.println(myIMU.readAccelY(), 4);
    SerialUSB.print(" Z = ");
    SerialUSB.println(myIMU.readAccelZ(), 4);
  }

  value = myIMU.readGyroX();
  // Not supported by hardware, so will return NAN
  if ( !isnan(value) )
  {
    SerialUSB.print("\nGyroscope:\n X = ");
    SerialUSB.println(value, 4);
    SerialUSB.print(" Y = ");
    SerialUSB.println(myIMU.readGyroY(), 4);
    SerialUSB.print(" Z = ");
    SerialUSB.println(myIMU.readGyroZ(), 4);
  }

  value = myIMU.readMagX();
  if ( !isnan(value) )
  {
    SerialUSB.print("\nMagnetometer:\n X = ");
    SerialUSB.println(value, 4);
    SerialUSB.print(" Y = ");
    SerialUSB.println(myIMU.readMagY(), 4);
    SerialUSB.print(" Z = ");
    SerialUSB.println(myIMU.readMagZ(), 4);
  }

  value = myIMU.readTempC();
  if ( !isnan(value) )
  {
    SerialUSB.print("\nThermometer:\n");
    SerialUSB.print(" Degrees C = ");
    SerialUSB.println(value, 4);
    SerialUSB.print(" Degrees F = ");
    SerialUSB.println(myIMU.readTempF(), 4);
  }

  delay(1000);//slow down output to make it easier to read, adjust as necessary
}
