#include "MIL1553.h"

void MIL1553_BC::begin() {
  _transport.begin();
}

void MIL1553_BC::sendCommand(CommandWord cmd) {
  uint16_t word = (cmd.rtAddress << 11) |
                  (cmd.tr << 10) |
                  (cmd.subAddress << 5) |
                  (cmd.wordCount);
  _transport.sendWord(word);
}

void MIL1553_RT::begin() {
  _transport.begin();
}

void MIL1553_RT::listen() {
  uint16_t word;
  if (_transport.receiveWord(word)) {
    // Simulación: simplemente imprimir lo recibido
    Serial.print("RT ");
    Serial.print(_rtAddress);
    Serial.print(" recibió comando: 0x");
    Serial.println(word, HEX);
  }
}

