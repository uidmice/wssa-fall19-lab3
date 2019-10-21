#include <Arduino.h>
#include<SPI.h>
#include<math.h>
#include <stdint.h>
#include "DebugMacros.h"


// Chip Select Pin for SPI
#define CS_PIN 51

#define READ  0x01111111   // write command
#define WRITE 0x11111111


//Function Declarations
void spi_write_cmd(uint8_t address, uint8_t tx_data);
uint8_t spi_read_cmd(uint8_t address);
