#ifndef serialUtil_h
#define serialUtil_h

#include <Arduino.h>

class SerialUtil
{
  public:
    static String Read(Stream *stream, const int timeout);
};

#endif