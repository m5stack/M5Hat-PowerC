#include "M5_IP5209.h"

bool M5_IP5209::begin(TwoWire *wire, uint8_t sda, uint8_t scl, uint8_t addr) {
    _wire = wire;
    _addr = addr;
    _sda  = sda;
    _scl  = scl;
    _wire->begin(_sda, _scl, 100);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

void M5_IP5209::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                           uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void M5_IP5209::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                          uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

uint16_t M5_IP5209::getBatVoltageAdc() {
    uint8_t data[2];
    readBytes(M5_IP5209_ADDRESS, M5_IP5209_BAT_VOLTAGE_REG, data, 2);
    uint16_t voltage_h = data[1];
    return (voltage_h << 8) | data[0];
}

uint16_t M5_IP5209::getBatCurrentAdc() {
    uint8_t data[2];
    readBytes(M5_IP5209_ADDRESS, M5_IP5209_BAT_VOLTAGE_REG, data, 2);
    uint16_t cureent_h = data[1];
    return (cureent_h << 8) | data[0];
}

float M5_IP5209::getBatVoltage() {
    uint16_t _bat_voltage_adc = getBatVoltageAdc();
    return (float)_bat_voltage_adc * 0.00026855 + 2.6;
    ;
}

float M5_IP5209::getBatCurrent() {
    uint16_t _bat_current_adc = getBatCurrentAdc();
    return (float)_bat_current_adc * 0.745985;
}
