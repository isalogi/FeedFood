#include <Arduino.h>
#include "serialUtil.h"

String SerialUtil::Read(Stream *stream, const int timeout)
{
    String response = "";
    unsigned long int time = millis() + timeout;

    while (time > millis())
    {
        while (stream->available())
        {
            char c = stream->read();
            response += c;
        }
    }

    return response;
}