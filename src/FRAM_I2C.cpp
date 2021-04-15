#include "FRAM_I2C.h"
#include "pf.h"

bool FRAM_I2C::begin(uint8_t addr) {
  pfln("FRAM_I2C begin addr 0x%x", addr);
  i2c_addr_ = addr;
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission()) {
    pfln("FRAM_I2C end failed");
    enabled_ = 0;
    return(0);
  }
  enabled_ = 1;
  return(1);
}

void FRAM_I2C::write8(uint16_t offset, uint8_t value) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(offset >> 8);
  Wire.write(offset & 0xFF);
  Wire.write(value);
  Wire.endTransmission();
}

void FRAM_I2C::write32(uint16_t offset, uint32_t value) {
  size_t i;
  uint8_t *ptr = (uint8_t *)&value;
  for (i = 0;i < sizeof(uint32_t);i++)
    write8(offset+i, ptr[i]);
}

void FRAM_I2C::write_buf(uint8_t *buf, uint16_t offset, uint16_t size) {
  size_t i;

  for (i = 0;i < size;i++) {
    write8(offset+i, buf[i]);
  }
}

uint8_t FRAM_I2C::read8(uint16_t offset) {
  Wire.beginTransmission(i2c_addr_);
  Wire.write(offset >> 8);
  Wire.write(offset & 0xFF);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr_, (uint8_t)1);
  return Wire.read();
}

 uint32_t FRAM_I2C::read32(uint16_t offset) {
  size_t i;
  uint32_t res;
  uint8_t *ptr = (uint8_t *)&res;
  for (i = 0;i < sizeof(uint32_t);i++)
    ptr[i] = read8(offset+i);
  return(res);
}

void FRAM_I2C::read_buf(uint8_t *buf, uint16_t offset, uint16_t size) {
  size_t i;
  for (i = 0;i < size;i++) {
    buf[i] = read8(offset+i);
  }
}