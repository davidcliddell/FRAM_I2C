#pragma once
#include <Wire.h>

class FRAM_I2C {
public:
  bool begin(uint8_t addr = 0x50);
  void write8(uint16_t offset, uint8_t value);
  void write32(uint16_t offset, uint32_t value);
  void write_buf(uint8_t *buf, uint16_t offset, uint16_t size);
  uint8_t read8(uint16_t offset);
  uint32_t read32(uint16_t offset);
  void read_buf(uint8_t *buf, uint16_t offset, uint16_t size);
private:
  uint8_t i2c_addr_;
  bool enabled_ = 0;
};
