#include <Wire.h>
#include "MIL1553.h"
#include "TransportI2C.h"

TransportI2C transport(0x08, true); // Dirección RT: 0x08
MIL1553_BC bc(transport);

void setup() {
  Serial.begin(9600);
  bc.begin();

  CommandWord cmd = { .rtAddress = 1, .tr = 0, .subAddress = 2, .wordCount = 1 };
  Serial.println("BC enviando comando...");
  bc.sendCommand(cmd);
}

void loop() {
  // Podrías enviar comandos periódicos
  delay(2000);
}

