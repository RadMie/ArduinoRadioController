#include "Arduino.h"
#include "memory.h"

Memory::Memory(int address)
{
  _address = address;
  read8bit();
}
Memory::Memory(int address, int address1)
{
  _address = address;
  _address1 = address1;
  read16bit();
}

void Memory::read8bit() {
  
  value = EEPROM.read(_address);  
}

void Memory::read16bit() {
  
  value16bit = EEPROM.read(_address) | EEPROM.read(_address1) << 8; 
}

void Memory::write8bit() {
  
  EEPROM.update(_address, value);
}

void Memory::write16bit() {
  
  EEPROM.update(_address, value16bit & 0xFF);
  EEPROM.update(_address1, (value16bit >> 8) & 0xFF);
}




