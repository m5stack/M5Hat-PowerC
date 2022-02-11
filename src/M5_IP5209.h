#ifndef _M5_IP5209_H_
#define _M5_IP5209_H_

#include <Arduino.h>
#include <Wire.h>

#define M5_IP5209_ADDRESS         0x75
#define M5_IP5209_BAT_VOLTAGE_REG 0xA2
#define M5_IP5209_BAT_CURRENT_REG 0XA4

class M5_IP5209 {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 0, uint8_t scl = 26,
               uint8_t addr = M5_IP5209_ADDRESS);
    uint16_t getBatVoltageAdc();
    uint16_t getBatCurrentAdc();
    float getBatVoltage();
    float getBatCurrent();
};

#endif
