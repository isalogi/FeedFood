#include <SoftwareSerial.h>
#include <Arduino.h>
#include <prueba.h>

#define DEBUG true

Prueba prueba(2, 3);

void setup()
{
  Serial.begin(115200);
  prueba.esp8266->begin(115200); // your esp's baud rate might be different

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  prueba.test();
  prueba.reset();
  prueba.setWifiMode(WifiMode::Host);
  prueba.getIp();
  prueba.setConnectionMode(ConnectionMode::Multiple);
  prueba.createServer(80);
}

void loop()
{
  if (prueba.esp8266->available()) // check if the esp is sending a message
  {
    Serial.println("OK");
    //Serial.println((char)prueba.esp8266->find("+IPD,"));

    if (prueba.esp8266->find("+IPD,"))
    {
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect

      prueba.find("pin="); // advance cursor to "pin="

      int pinNumber = (prueba.esp8266->read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
      pinNumber += (prueba.esp8266->read() - 48);         // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number

      digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin

      prueba.closeConnection();
    }
  }
}