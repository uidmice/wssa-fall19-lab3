#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
#include <FreeRTOS_ARM.h>

#define INT_ms 1000/40

LSM303C myIMU;
SemaphoreHandle_t sem;
QueueHandle_t xQueue;

void setup() {
  //set up I2C bus
  Wire1.begin();
  Wire1.setClock(400000L);//set up I2C bus clock to 400kHz

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

  sem = xSemaphoreCreateBinary();  
  xSemaphoreGive(sem);
  xQueue = xQueueCreate(3, sizeof(float)); //10 colors in a sequence max
  portBASE_TYPE s1 = xTaskCreate(ReadData, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  portBASE_TYPE s2 = xTaskCreate(PrintData, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  
  // check for creation errors
  if ( sem==NULL || s1 != pdPASS || s2 != pdPASS ||  xQueue==NULL) {
     SerialUSB.println(F("Creation problem"));
     while(1);
  }
  // start scheduler
  vTaskStartScheduler();
  SerialUSB.println("Insufficient RAM");
  while(1);

}

static void ReadData(void* arg){
  float vX, vY, vZ;
  while (1){
    xSemaphoreTake( sem, 0 );
    vX = myIMU.readMagX();
    vY = myIMU.readMagY();
    vZ = myIMU.readMagZ();
    xQueueReset (xQueue);
    xQueueSend(xQueue, &vX, 0 );
    xQueueSend(xQueue, &vY, 0 );
    xQueueSend(xQueue, &vZ, 0 );
    
    xSemaphoreGive( sem );
    vTaskDelay((INT_ms * configTICK_RATE_HZ) / 1000L);

  }

    
}

static void PrintData(void* arg){
  float vX, vY, vZ;
  BaseType_t xStatus1, xStatus2, xStatus3;

  while(1){
    xSemaphoreTake( sem, portMAX_DELAY );
    if (xQueueReceive(xQueue, &vX, 0)==pdPASS && xQueueReceive(xQueue, &vY, 0)==pdPASS && xQueueReceive(xQueue, &vZ, 0)==pdPASS){
      SerialUSB.print("\nMagnetometer:\n X = ");
      SerialUSB.println(vX, 4);
      SerialUSB.print(" Y = ");
      SerialUSB.println(vY, 4);
      SerialUSB.print(" Z = ");
      SerialUSB.println(vZ, 4);      
    }else {
      SerialUSB.println("Quene reading error");
    }

    xSemaphoreGive( sem );
    vTaskDelay((INT_ms * configTICK_RATE_HZ) / 1000L);
  }
 
    
}


void loop(){
}
