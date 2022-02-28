#include "M5_IP5209.h"

bool M5_IP5209::begin(TwoWire *wire, uint8_t sda, uint8_t scl, uint8_t addr) {
    _wire = wire;
    _addr = addr;
    _sda  = sda;
    _scl  = scl;
    _wire->begin(_sda, _scl, 400000UL);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

bool M5_IP5209::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                           uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    if (_wire->endTransmission() == 0) return true;
    return false;
}

bool M5_IP5209::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                          uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    if (_wire->requestFrom(addr, length)) {
        for (int i = 0; i < length; i++) {
            buffer[index++] = _wire->read();
        }
        return true;
    }
    return false;
}

int M5_IP5209::getBatVAdc() {
    uint8_t data[2];
    if (readBytes(M5_IP5209_ADDRESS, M5_IP5209_BAT_VADC_REG, data, 2)) {
        uint16_t voltage_h = data[1] & 0x3f;
        return (voltage_h << 8) | data[0];
    }
    return -1;
}

int M5_IP5209::getBatIAdc() {
    uint8_t data[2];
    if (readBytes(M5_IP5209_ADDRESS, M5_IP5209_BAT_IADC_REG, data, 2)) {
        if ((data[1] & 0x20) == 0x20) {
            charged       = false;
            uint8_t temp1 = ~data[1];
            uint8_t temp2 = (~(data[1] & 0x1f) & 0x1f);
            return (temp2 * 256 + temp1 + 1);
        } else {
            charged            = true;
            uint16_t current_h = data[1] & 0xff;
            return ((current_h << 8) | data[0]);
        }
    }
    return -1;
}

int M5_IP5209::getBatOCV() {
    uint8_t data[2];
    if (readBytes(M5_IP5209_ADDRESS, M5_IP5209_BAT_OCV_REG, data, 2)) {
        uint16_t voltage_h = data[1] & 0x3f;
        return (voltage_h << 8) | data[0];
    }
    return -1;
}

bool M5_IP5209::getBatVoltage() {
    uint16_t _bat_voltage_adc = getBatVAdc();
    if (_bat_voltage_adc != -1) {
        voltage = _bat_voltage_adc * 0.00026855 + 2.6;
        return true;
    }
    return false;
}

bool M5_IP5209::getBatCurrent() {
    uint16_t _bat_current_adc = getBatIAdc();
    if (_bat_current_adc != -1) {
        current = _bat_current_adc * 0.745985;
        return true;
    } else {
        return false;
    }
}

bool M5_IP5209::update() {
    if (getBatCurrent() && getBatVoltage()) {
        power = voltage * current / 1000;
        return true;
    } else {
        return false;
    }
}
