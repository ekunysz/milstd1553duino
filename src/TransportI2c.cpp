#include <TransportI2c.h>

static volatile uint16_t _lastWord = 0;
static volatile bool _hasWord = false;

// Static handler (called by I2C slave interrupt)
static void receiveHandler(int numBytes) {
  if (numBytes >= 2) {
    uint8_t hi = Wire.read();
    uint8_t lo = Wire.read();
    _lastWord = (hi << 8) | lo;
    _hasWord = true;
  }
}

TransportI2C::TransportI2C(uint8_t address, bool isMaster)
  : _address(address), _isMaster(isMaster) {}

void TransportI2C::begin() {
  if (_isMaster) {
    Wire.begin(); // Master
  } else {
    Wire.begin(_address); // Slave
    Wire.onReceive(receiveHandler); //Interrupt activation
  }
}

void TransportI2C::sendWord(uint16_t word) {
  Wire.beginTransmission(_address);
  Wire.write((word >> 8) & 0xFF);
  Wire.write(word & 0xFF);
  Wire.endTransmission();
}

bool TransportI2C::receiveWord(uint16_t &word) {
  if (_hasWord) {
    word = _lastWord;
    _hasWord = false; // flag clean
    return true;
  }
  return false;
}

