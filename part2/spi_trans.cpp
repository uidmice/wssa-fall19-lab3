#include "spi_trans.h"

void spi_write_cmd(uint8_t address, uint8_t tx_data) {
  debug_print("Write to Reg: ");
  debug_prints(address, BIN);
  debug_prints("\t  data value: ");
  debug_printlns(tx_data, BIN);

  byte c1 = address | WRITE;
  byte c2 = address; 
  debug_prints("Sending ");
  debug_prints(c1, BIN);
  debug_prints("\t");
  debug_prints("and ");
  debug_printlns(c2, BIN);
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
  uint8_t data = 0;           // incoming byte from the SPI
  debug_print("Read from Reg: ");
  debug_printlns(address, BIN);

  uint8_t c1 = (address<<1)>>1;
  uint8_t c2 = address; 
  debug_prints("Sending ");
  debug_prints(c1, BIN);
  debug_prints("\t");
  debug_prints("and ");
  debug_printlns(c2, BIN);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(c1);
  SPI.transfer(c2);
  data = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  debug_printlns(data, BIN);

  return (data);

}

//*****************************************************************************
