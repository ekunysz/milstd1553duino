#ifndef MIL1553_H
#define MIL1553_H

#include <Transport.h>

#define MAX_SUBADDR 32 // Max number of RT subaddress

struct CommandWord
{
  uint8_t rtAddress;
  uint8_t tr;
  uint8_t subAddress;
  uint8_t wordCount;
};

struct StatusWord
{
  uint8_t rtAddress;
  bool messageError;
  bool busy;
};

struct DataWord
{
  uint16_t data;
};

struct MIL1553_Message
{
  CommandWord cmd;
  uint16_t data;      // last recived data (BC→RT)
  bool valid = false; // availability flag
};

class MIL1553_BC
{
public:
  MIL1553_BC(Transport &t) : _transport(t) {}
  void begin();
  void sendCommand(CommandWord cmd);
  void sendData(DataWord data);

private:
  Transport &_transport;
};

class MIL1553_RT
{
public:
  MIL1553_RT(Transport &t, uint8_t rtAddress)
      : _transport(t), _rtAddress(rtAddress) {}
  void begin();
  void listen();
  bool hasNewMessage();
  MIL1553_Message getMessage();
  // Buffer for send data RT-BC
  void setTxBuffer(uint8_t subAddr, uint16_t value);
  uint16_t getTxBuffer(uint8_t subAddr);

private:
  Transport &_transport;
  uint8_t _rtAddress;
  MIL1553_Message _rxMessage;      // RX buffer
  uint16_t _txBuffer[MAX_SUBADDR]; // setting for user for RT-BC
};

#endif
