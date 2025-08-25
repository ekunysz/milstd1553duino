#include <MIL1553.h>

void MIL1553_BC::begin()
{
  _transport.begin();
}

void MIL1553_BC::sendCommand(CommandWord cmd)
{
  uint16_t word = (cmd.rtAddress << 11) |
                  (cmd.tr << 10) |
                  (cmd.subAddress << 5) |
                  (cmd.wordCount);
  _transport.sendWord(word);
}

void MIL1553_BC::sendData(DataWord data)
{
  uint16_t word = data.data;
  _transport.sendWord(word);
}

void MIL1553_RT::begin()
{
  _transport.begin();
}

void MIL1553_RT::listen()
{
  uint16_t word;
  if (_transport.receiveWord(word))
  {
    // Decode Word
    CommandWord cmd;
    cmd.rtAddress = (word >> 11) & 0x1F;
    cmd.tr = (word >> 10) & 0x01;
    cmd.subAddress = (word >> 5) & 0x1F;
    cmd.wordCount = (word & 0x1F);

    if (cmd.tr == 0)
    {
      // Casa BC→RT: recive data from BC
      delay(10); // FIX this delay
      if (_transport.receiveWord(word))
      {
        _rxMessage.cmd = cmd;
        _rxMessage.data = word;
        _rxMessage.valid = true;
      }
    }
    else
    {
      // Caso RT→BC: el BC está pidiendo datos
      uint16_t toSend = _txBuffer[cmd.subAddress];
      //_transport.sendWord(toSend);
      // (por ahora no guardamos nada, solo respondemos)
    }
  }
}

bool MIL1553_RT::hasNewMessage()
{
  return _rxMessage.valid;
}

MIL1553_Message MIL1553_RT::getMessage()
{
  MIL1553_Message msg = _rxMessage;
  _rxMessage.valid = false; // marcar como leído
  return msg;
}

void MIL1553_RT::setTxBuffer(uint8_t subAddr, uint16_t value)
{
  if (subAddr < MAX_SUBADDR)
  {
    _txBuffer[subAddr] = value;
  }
}

uint16_t MIL1553_RT::getTxBuffer(uint8_t subAddr)
{
  if (subAddr < MAX_SUBADDR)
  {
    return _txBuffer[subAddr];
  }
  return 0;
}