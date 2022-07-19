/*!
 * @brief  A charging module From M5Stack
 * @copyright Copyright (c) 2022 by M5Stack[https://m5stack.com]
 *
 * @Links [PowerC HAT](https://docs.m5stack.com/en/hat/hat-powerc)
 * @version  V0.0.1
 * @date  2022-07-19
 */
#ifndef _Hat_PowerC_H_
#define _Hat_PowerC_H_

#include <Arduino.h>
#include <Wire.h>
#include "Pins_Arduino.h"

#define PowerC_ADDRESS      0x75
#define PowerC_BAT_VADC_REG 0xa2
#define PowerC_BAT_IADC_REG 0xa4
#define PowerC_BAT_OCV_REG  0xa8
#define PowerC_READ0_REG    0x70

class PowerC {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = SDA, uint8_t scl = SCL,
               uint8_t addr = PowerC_ADDRESS);
    int getBatVAdc();
    int getBatIAdc();
    int getBatOCV();
    bool getBatVoltage();
    bool getBatCurrent();
    bool update();
    float voltage = 0;
    float current = 0;
    float power   = 0;
    bool charged  = false;
};

#endif
