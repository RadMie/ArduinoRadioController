#ifndef analog_h
#define analog_h

#include "Arduino.h"

class Analog
{
  public:
    Analog(int pin);
    int readRAW();
    int readRAW(int minRaw, int maxRaw);
    uint8_t read8BIT();
    uint8_t read8BIT(int minRaw, int maxRaw);
    uint8_t readPercent();
    uint8_t readPercent(int minRaw, int maxRaw);
    int raw;
    float readVoltage();
  private:
    int _pin;
};

#endif


