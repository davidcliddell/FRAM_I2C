#include "FRAM_I2C.h"
#include "pf.h"

bool FRAM_I2C::begin(uint8_t addr) {
  pfln("FRAM_I2C begin addr 0x%x", addr);
  i2c_addr_ = addr;
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission()) {
    pfln("end failed");
    enabled_ = 0;
    return(0);
  }
  enabled_ = 1;
  return(1);
}

void FRAM_I2C::write8(uint16_t addr, uint8_t value) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.write(value);
  Wire.endTransmission();
}

void FRAM_I2C::write32(uint16_t addr, uint32_t value) {
  size_t i;
  uint8_t *ptr = (uint8_t *)&value;
  for (i = 0;i < sizeof(uint32_t);i++)
    write8(addr+i, ptr[i]);
}

uint8_t FRAM_I2C::read8(uint16_t addr) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr_, (uint8_t)1);
  return Wire.read();
}

 uint32_t FRAM_I2C::read32(uint16_t addr) {
  size_t i;
  uint32_t res;
  uint8_t *ptr = (uint8_t *)&res;
  for (i = 0;i < sizeof(uint32_t);i++)
    ptr[i] = read8(addr+i);
  return(res);
}