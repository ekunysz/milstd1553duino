#ifndef TRANSPORT_I2C_H
#define TRANSPORT_I2C_H

#include <Transport.h>
#include <Wire.h>

class TransportI2C : public Transport {
  public:
    TransportI2C(uint8_t address, bool isMaster);
    void begin();
    void sendWord(uint16_t word);
    bool receiveWord(uint16_t &word);

  private:
    uint8_t _address;
    bool _isMaster;
};

#endif

