#include "Arduino.h"
#include "buzzer.h"

Buzzer::Buzzer(int pin)
{
  _pin = pin;
  status = 0;
}

void Buzzer::on(uint8_t lvl) {
  
  analogWrite(_pin, lvl); 
  status = 1;
  counterMillis = millis();
}

void Buzzer::process() {
  
  if(status) {
    if((millis() - counterMillis) > 40) {
      analogWrite(_pin,0);
      status = 0;
    }
  }
}



