#ifndef key_h
#define key_h

#include "Arduino.h"

class Key
{
  public:
    Key(int pin);
    boolean pressed();
    boolean status;
  private:
    int _pin;
};

#endif


