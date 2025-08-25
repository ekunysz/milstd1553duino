#include <TransportI2c.h>

static volatile uint16_t _lastWord = 0;
static volatile bool _hasWord = false;
static volatile uint16_t _txWord = 0; // to store the word to be sended to RT

// Static handler (called by I2C slave interrupt)
static void receiveHandler(int numBytes)
{
  if (numBytes >= 2)
  {
    uint8_t hi = Wire.read();
    uint8_t lo = Wire.read();
    _lastWord = (hi << 8) | lo;
    _hasWord = true;
  }
}

// Handler: when BC ask for RT data
static void requestHandler()
{
  // RT responds with the last value loaded in the transmission buffer
  Wire.write((_txWord >> 8) & 0xFF);
  Wire.write(_txWord & 0xFF);
}

TransportI2C::TransportI2C(uint8_t address, bool isMaster)
    : _address(address), _isMaster(isMaster) {}

void TransportI2C::begin()
{
  if (_isMaster)
  {
    Wire.begin(); // Master
  }
  else
  {
    Wire.begin(_address);           // Slave mode
    Wire.onReceive(receiveHandler); // callback when receiving data
    Wire.onRequest(requestHandler); // callback when the BC requests data
  }
}

// Only for MASTER (BC)
void TransportI2C::sendWord(uint16_t word)
{
  Wire.beginTransmission(_address);
  Wire.write((word >> 8) & 0xFF);
  Wire.write(word & 0xFF);
  Wire.endTransmission();
}

// Only for MASTER (BC)
bool TransportI2C::receiveWord(uint16_t &word)
{
  int bytesRead = Wire.requestFrom(_address, (uint8_t)2);
  if (bytesRead == 2)
  {
    uint8_t hi = Wire.read();
    uint8_t lo = Wire.read();
    word = (hi << 8) | lo;
    return true;
  }
  return false;
}

// Solo para SLAVE (RT): prepara el dato que mandará en la próxima petición del BC
void TransportI2C::prepareResponse(uint16_t word)
{
  _txWord = word;
}

// Solo para SLAVE (RT): obtiene lo último que recibió del BC
bool TransportI2C::getLastWord(uint16_t &word)
{
  if (_hasWord)
  {
    word = _lastWord;
    _hasWord = false; // flag clean
    return true;
  }
  return false;
}
