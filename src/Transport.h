#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <Arduino.h>

class Transport
{
public:
  virtual void begin() = 0;
  virtual void sendWord(uint16_t word) = 0;
  virtual bool receiveWord(uint16_t &word) = 0;
  virtual void prepareResponse(uint16_t word) = 0;
  virtual bool getLastWord(uint16_t &word) = 0;
};

#endif
