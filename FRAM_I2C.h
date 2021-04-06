#pragma once
#include <Wire.h>

class FRAM_I2C {
public:
  bool begin(uint8_t addr = 0x50);
  void write8(uint16_t i2c_addr, uint8_t value);
  void write32(uint16_t i2c_addr, uint32_t value);
  uint8_t read8(uint16_t i2c_addr);
  uint32_t read32(uint16_t i2c_addr);
private:
  uint8_t i2c_addr_;
  bool enabled_ = 0;
};
