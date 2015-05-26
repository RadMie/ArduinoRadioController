#ifndef memory_h
#define memory_h

#include "Arduino.h"
#include <EEPROM.h>

class Memory
{
  public:
    Memory(int address);
    Memory(int address, int address1);
    void read8bit();
    void read16bit();
    void write8bit();
    void write16bit();
    uint8_t value;
    uint16_t value16bit;
  private:
    int _address;
    int _address1;
};

#endif


