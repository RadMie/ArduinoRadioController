#include "Arduino.h"
#include "analog.h"

Analog::Analog(int pin)
{
  _pin = pin;
}

int Analog::readRAW() {
  return analogRead(_pin);
}

int Analog::readRAW(int minRaw, int maxRaw) {
  return map(analogRead(_pin), minRaw, maxRaw, 0, 1023);
}

uint8_t Analog::read8BIT() {
  
  return map(analogRead(_pin), 0, 1023, 0, 255); 
}

uint8_t Analog::read8BIT(int minRaw, int maxRaw) {
  
  raw = readRAW();
  
  int temp = map(raw, minRaw, maxRaw, 0, 255); 
  if(temp < 0) {
    return 0;
  } else if(temp > 255){
    return 255; 
  } else {
    return temp; 
  }
}

uint8_t Analog::readPercent() {
  
  return map(analogRead(_pin), 0, 1023, 0, 100);
}

uint8_t Analog::readPercent(int minRaw, int maxRaw) {
  
  return map(analogRead(_pin), minRaw, maxRaw, 0, 100);
}

float Analog::readVoltage() {
  
  return analogRead(_pin) * (15.0 / 1023.0);
}


