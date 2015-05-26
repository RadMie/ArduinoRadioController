#ifndef rf433_h
#define rf433_h

#include "Arduino.h"
#include <VirtualWire.h>

class RF433
{
  public:
    RF433(uint8_t tx, uint8_t rx, uint8_t ptt, uint8_t inv);
    void init(uint16_t bps);
    void sendData(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, uint8_t sw);
    int transferCounter;
};

#endif


