#include <TransportI2c.h>

TransportI2C::TransportI2C(uint8_t address, bool isMaster)
  : _address(address), _isMaster(isMaster) {}

void TransportI2C::begin() {
  if (_isMaster) {
    Wire.begin(); // Master
  } else {
    Wire.begin(_address); // Slave
  }
}

void TransportI2C::sendWord(uint16_t word) {
  Wire.beginTransmission(_address);
  Wire.write((word >> 8) & 0xFF);
  Wire.write(word & 0xFF);
  Wire.endTransmission();
}

bool TransportI2C::receiveWord(uint16_t &word) {
  if (Wire.available() >= 2) {
    uint8_t hi = Wire.read();
    uint8_t lo = Wire.read();
    word = (hi << 8) | lo;
    return true;
  }
  return false;
}

