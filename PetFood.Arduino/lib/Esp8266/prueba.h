#ifndef prueba_h
#define prueba_h

#include <Arduino.h>
#include "WifiMode.h"
#include "ConnectionMode.h"

class Prueba
{
public:
  SoftwareSerial *esp8266;

  Prueba(uint8_t RxPin, uint8_t TxPin);

  void test();
  void reset();
  void setWifiMode(WifiMode mode);
  void getIp();
  void setConnectionMode(ConnectionMode mode);
  void createServer(uint16_t port);
  void deleteServer(uint16_t port);
  void closeConnection();
  bool find(char *findText);

private:
  String sendData(String command, const int timeout);
};

#endif