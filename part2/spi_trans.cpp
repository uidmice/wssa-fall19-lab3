#include "spi_trans.h"

//------------------------------------------------------------------------------
void spi_write_cmd(uint8_t address, uint8_t tx_data) {
  debug_print("Read from Reg: ");
  debug_print(address, BIN);
  debug_print("\t");

  byte c1 = address & WRITE;
  byte c2 = address; 
  debug_print("Sending ");
  debug_print(c1, BIN);
  debug_print("\t");
  debug_print("and ");
  debug_println(c2, BIN);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(c1);
  SPI.transfer(c2);
  SPI.transfer(tx_data);
  digitalWrite(CS_PIN, HIGH);
    
}

//------------------------------------------------------------------------------
// spi_read_cmd(): Read from a SPI device. Return the data read from register
//------------------------------------------------------------------------------
uint8_t spi_read_cmd(uint8_t address) {
  byte data = 0;           // incoming byte from the SPI
  debug_print("Read from Reg: ");
  debug_print(address, BIN);
  debug_print("\t");

  byte c1 = address & READ;
  byte c2 = address; 
  debug_print("Sending ");
  debug_print(c1, BIN);
  debug_print("\t");
  debug_print("and ");
  debug_println(c2, BIN);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(c1);
  SPI.transfer(c2);
  data = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  return (data);

}

//*****************************************************************************
