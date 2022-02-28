#ifndef _M5_IP5209_H_
#define _M5_IP5209_H_

#include <Arduino.h>
#include <Wire.h>

#define M5_IP5209_ADDRESS      0x75
#define M5_IP5209_BAT_VADC_REG 0xa2
#define M5_IP5209_BAT_IADC_REG 0xa4
#define M5_IP5209_BAT_OCV_REG  0xa8
#define M5_IP5209_READ0_REG    0x70

class M5_IP5209 {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 0, uint8_t scl = 26,
               uint8_t addr = M5_IP5209_ADDRESS);
    int getBatVAdc();
    int getBatIAdc();
    int getBatOCV();
    bool getBatVoltage();
    bool getBatCurrent();
    bool update();
    float voltage = 0;
    float current = 0;
    float power = 0;
    bool charged  = false;
};

#endif
