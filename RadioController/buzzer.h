#ifndef buzzer_h
#define buzzer_h

#include "Arduino.h"

class Buzzer
{
  public:
    Buzzer(int pin);
    void on(uint8_t lvl);
    void process();
    boolean status;
    unsigned long counterMillis;
  private:
    int _pin;
};

#endif


