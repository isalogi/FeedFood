#include <Arduino.h>
#include <serialUtil.h>
#include <SoftwareSerial.h>

#include "prueba.h"

Prueba::Prueba(uint8_t rxPin, uint8_t txPin)
{
  // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
  // This means that you need to connect the TX line from the esp to the Arduino's pin 2
  // and the RX line from the esp to the Arduino's pin 3
  this->esp8266 = new SoftwareSerial(rxPin, txPin);
}

String Prueba::sendData(String command, const int timeout)
{
  esp8266->println(command);

  String response = SerialUtil::Read(esp8266, timeout);
  Serial.print(response);

  return response;
}

void Prueba::test()
{
  this->sendData("AT", 2000);
}

void Prueba::reset()
{
  this->sendData("AT+RST", 1000);
}

void Prueba::setWifiMode(WifiMode mode)
{
  this->sendData("AT+CWMODE=" + static_cast<int>(mode), 1000);
}

void Prueba::getIp()
{
  this->sendData("AT+CIFSR", 1000);
}

void Prueba::setConnectionMode(ConnectionMode mode)
{
  this->sendData("AT+CIPMUX=" + static_cast<int>(mode), 1000);
}

void Prueba::createServer(uint16_t port)
{
  this->sendData("AT+CIPSERVER=1," + port, 1000);
}

void Prueba::deleteServer(uint16_t port)
{
  this->sendData("AT+CIPSERVER=0," + port, 1000);
  this->reset();
}

void Prueba::closeConnection()
{
  //ASCII 48 is 0 int
  int connectionId = this->esp8266->read() - 48;
  this->sendData("AT+CIPCLOSE=" + connectionId, 1000);
}

bool Prueba::find(char *findText)
{
  return this->esp8266->find(findText);
}
