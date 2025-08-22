#ifndef MIL1553_H
#define MIL1553_H

#include "Transport.h"

struct CommandWord {
  uint8_t rtAddress;
  uint8_t tr;
  uint8_t subAddress;
  uint8_t wordCount;
};

struct StatusWord {
  uint8_t rtAddress;
  bool messageError;
  bool busy;
};

struct DataWord {
  uint16_t data;
};

class MIL1553_BC {
  public:
    MIL1553_BC(Transport &t) : _transport(t) {}
    void begin();
    void sendCommand(CommandWord cmd);
  private:
    Transport &_transport;
};

class MIL1553_RT {
  public:
    MIL1553_RT(Transport &t, uint8_t rtAddress) 
      : _transport(t), _rtAddress(rtAddress) {}
    void begin();
    void listen();
  private:
    Transport &_transport;
    uint8_t _rtAddress;
};

#endif

