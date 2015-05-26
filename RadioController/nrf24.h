#ifndef nrf24_h
#define nrf24_h

#include "Arduino.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

class NRF24 : public RF24
{
  public:
    NRF24(uint8_t CE, uint8_t CS);
    void init(uint8_t channel, uint8_t PAlevel, uint8_t DataRate, bool AutoAck, uint8_t Retries1, uint8_t Retries2, uint8_t CRC);
    void sendData(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, uint8_t keySwitch);
    int transferCounter;
};

#endif


