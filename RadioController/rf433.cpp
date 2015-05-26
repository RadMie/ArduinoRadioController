#include "Arduino.h"
#include "rf433.h"

RF433::RF433(uint8_t tx, uint8_t rx, uint8_t ptt, uint8_t inv)
{
  transferCounter = 0;
  vw_set_tx_pin(tx);
  vw_set_rx_pin(rx);
  vw_set_ptt_pin(ptt);
  vw_set_ptt_inverted(inv);   // Required for DR3100
}

void RF433::init(uint16_t bps) {
  
  vw_setup(bps);	      // Bits per sec
}

void RF433::sendData(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, uint8_t sw) {
  
  uint8_t msg[7] = {LX,LY,RX,RY,VRA,VRB,sw};

  if(!vx_tx_active()) {
    vw_send((uint8_t *)msg, 7);
    transferCounter += 7;  
  }
}


