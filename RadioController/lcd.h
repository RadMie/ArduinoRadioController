#ifndef lcd_h
#define lcd_h

#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

class LCD : public Adafruit_PCD8544 {

  public:
    LCD(int DC, int CS, int RST, int BK);
    uint8_t freqCount;
    void init(uint8_t contrast, uint8_t backlight);
    void setBacklight(uint8_t BK);
    void logo();
    void progressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, boolean color, uint8_t progress);
    void gird(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void window(char* nameText);
    void battery(uint8_t lvl);
    void trimmed(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY);
    void sticks(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY);
    void keySW(uint8_t keysw);
    void control(uint8_t tx, uint8_t t24, uint8_t t433);
    
    void startPanel();
    void mainPanel0(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t stickLY, uint8_t stickLX, uint8_t stickRX, uint8_t stickRY, uint8_t keysw);
    void mainPanel1(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB);
    void mainPanel2(float bat, uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB);
    void mainPanel3(uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB);
    void mainPanel4(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t keysw, float rateNRF24, float rate433, uint16_t cps, uint8_t rateLCD);
    void mainPanel5(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t keysw, uint8_t limitRX, uint8_t limitRY);
    
    void mainMenu(uint8_t positionNumber);
    void subMenuLCD(uint8_t light, uint8_t contrast, uint8_t freq, int pos, boolean sel);
    void subMenuCalibration(uint16_t LXmin, uint16_t LXmax, uint16_t LYmin, uint16_t LYmax, uint16_t RXmin, uint16_t RXmax, uint16_t RYmin, uint16_t RYmax, uint16_t LX, uint16_t LY, uint16_t RX, uint16_t RY, int pos, boolean sel);
    void subMenuTrimmed(uint8_t precision, int pos, boolean sel);
    void subMenuSound(uint8_t mode, uint8_t volume, int pos, boolean sel);
    void subMenuBattery(uint8_t rawbatWarn, uint8_t rawbatLvl0, uint8_t rawbatLvl1, uint8_t rawbatLvl2, uint8_t rawbatLvl3, uint8_t rawbatLvl4, uint8_t batFreq, int pos, boolean sel);
    void subMenuTransmission(uint8_t tx, uint8_t t433, uint8_t t24, int pos, boolean sel);
    void subMenuLimits(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, int pos, boolean sel);
    void subMenuMixer(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, uint8_t SWA, uint8_t SWA1, uint8_t SWB, uint8_t SWB1, int pos, boolean sel);
    void subMenuModel(uint8_t mode, int pos, boolean sel);
    void subMenuVersion(char* git, char* vers, char* date, int pos, boolean sel);
    void subMenu433(uint16_t bps, int pos, boolean sel);
    void subMenu24(uint8_t channel, uint8_t pa, uint8_t ra, uint8_t ack, uint8_t delay, uint8_t count, uint8_t cr, int pos, boolean sel);
    void subMenuSystem(int pos, boolean sel);
    
  private:
    int _bk;
    char* _chConvNrTochar(uint8_t nr);
    char* _swConvNrTochar(uint8_t nr);
};

#endif


