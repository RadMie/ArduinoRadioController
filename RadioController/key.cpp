#include "Arduino.h"
#include "key.h"

Key::Key(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
  status = 0;
}

boolean Key::pressed()
{
  if(digitalRead(_pin)) {
    return 0;
  } else {
    return 1;
  }
}
