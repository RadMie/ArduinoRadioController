#include "Arduino.h"
#include "lcd.h"

LCD::LCD(int DC, int CS, int RST, int BK) : Adafruit_PCD8544(DC,CS,RST)
{
   pinMode(BK, OUTPUT);  // LCD PWM Backlight
   _bk = BK;
}

void LCD::init(uint8_t contrast, uint8_t backlight) {
  
  if(contrast == 255 || contrast == 0) contrast = 58; // for new EEPROM 
  
  begin();                  // init
  setContrast(contrast);    // contrast
  clearDisplay();           // clears the screen and buffer
  setBacklight(backlight);  // backlight
}

void LCD::setBacklight(uint8_t BK) {
  
  analogWrite(_bk, BK);     // set PWM Backlight
}
//============================== COMPONENT ===========================================================

void LCD::logo() {
  
    static const unsigned char PROGMEM logo[] = {
      0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x01, 0x80, 0x70, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x01, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x18,
      0x01, 0x80, 0x18, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0x18, 0x03, 0xC0, 0x18, 0x40, 0x00, 0x00,
      0x00, 0x00, 0x02, 0x30, 0x07, 0xE0, 0x0C, 0x40, 0x00, 0x00, 0x00, 0x01, 0x07, 0x30, 0x0F, 0xF0,
      0x0C, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0x00, 0x00, 0x00, 0x00,
      0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
      0x00, 0xC4, 0x18, 0x80, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0x00, 0xA4, 0x14, 0x80, 0xE0, 0x0F,
      0xFF, 0xFF, 0xF0, 0x07, 0x00, 0x94, 0x12, 0x81, 0xC0, 0x00, 0x1F, 0xF8, 0x00, 0x03, 0x80, 0x8C,
      0x11, 0x81, 0x80, 0x00, 0x07, 0xE0, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x98, 0x00, 0xC0, 0x03,
      0x00, 0x19, 0x81, 0xFC, 0x3F, 0x81, 0x98, 0x70, 0xC0, 0x03, 0x0E, 0x19, 0x80, 0x20, 0x04, 0x01,
      0x83, 0x8E, 0x00, 0x00, 0x71, 0xC1, 0x80, 0x20, 0x04, 0x01, 0x84, 0x01, 0x00, 0x00, 0x80, 0x21,
      0x81, 0xFC, 0x3F, 0x81, 0x84, 0x01, 0x00, 0x00, 0x80, 0x21, 0x80, 0x00, 0x00, 0x01, 0x84, 0x01,
      0x03, 0xC0, 0x80, 0x21, 0x81, 0xFC, 0x27, 0x01, 0x88, 0x70, 0xB3, 0xCD, 0x0E, 0x11, 0x80, 0x80,
      0x24, 0x81, 0x88, 0x50, 0xB3, 0xCD, 0x0A, 0x11, 0x80, 0x40, 0x24, 0x81, 0x88, 0x70, 0xB3, 0xCD,
      0x0E, 0x11, 0x80, 0x80, 0x20, 0x81, 0x84, 0x01, 0x03, 0xC0, 0x80, 0x21, 0x81, 0xFC, 0x1F, 0x01,
      0x84, 0x01, 0x00, 0x00, 0x80, 0x21, 0x80, 0x00, 0x00, 0x01, 0x84, 0x01, 0x00, 0x00, 0x80, 0x21,
      0x80, 0x00, 0x00, 0x01, 0x83, 0x8E, 0x00, 0x00, 0x71, 0xC1, 0x80, 0x00, 0x00, 0x01, 0x98, 0x70,
      0xC0, 0x03, 0x0E, 0x19, 0x80, 0xD8, 0x3F, 0x81, 0x98, 0x00, 0xC0, 0x03, 0x00, 0x19, 0x81, 0x24,
      0x04, 0x01, 0x80, 0x70, 0x07, 0xE0, 0x0E, 0x01, 0x81, 0x24, 0x04, 0x01, 0xC0, 0x70, 0x3F, 0xFC,
      0x0E, 0x03, 0x81, 0x04, 0x3C, 0x01, 0xE0, 0x03, 0xFF, 0xFF, 0xC0, 0x07, 0x80, 0x00, 0x00, 0x01,
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xD8, 0x00, 0x81, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07,
      0x81, 0x24, 0x00, 0x01, 0xC0, 0x00, 0x7F, 0xFE, 0x00, 0x03, 0x81, 0x24, 0x00, 0x01, 0x80, 0x38,
      0x60, 0x06, 0x1C, 0x01, 0x81, 0x04, 0x18, 0x81, 0x80, 0x38, 0x60, 0x06, 0x1C, 0x01, 0x80, 0x00,
      0x24, 0x81, 0x80, 0x00, 0x60, 0x06, 0x00, 0x01, 0x81, 0xFC, 0x24, 0x81, 0x80, 0x38, 0x60, 0x06,
      0x1C, 0x01, 0x80, 0x20, 0x24, 0x81, 0x80, 0x38, 0x60, 0x06, 0x1C, 0x01, 0x80, 0x20, 0x13, 0x81,
      0xC0, 0x00, 0x7F, 0xFE, 0x00, 0x03, 0x81, 0xE0, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07,
      0x80, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF,
      0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x01, 0xF0, 0x00, 0x00};
    drawBitmap(2, 0, logo, 80, 48, BLACK);
}

void LCD::progressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, boolean color, uint8_t progress) {
  
  drawLine(x+1, y, x+w-2, y, color);
  drawLine(x+1, y+h-1, x+w-2, y+h-1, color);
  drawLine(x, y+1, x, y+h-2, color);
  drawLine(x+w-1, y+1, x+w-1, y+h-2, color);
  fillRect(x+2, y+2, ((w-4)*progress)/254, h-4, color);
}

void LCD::gird(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  
  boolean c = 1;
  for(int i=y; i <= y+h; i++) {
    for(int j=x; j <= x+w; j++) {
      drawPixel(j, i, c);
      c = !c;
    }
  }
}

void LCD::window(char* nameText) {
  
  fillRoundRect(0,0,84,9,1,BLACK);
  drawRoundRect(0,0,84,48,1,BLACK);
  setCursor(3,1);
  setTextColor(WHITE,BLACK);
  setTextSize(1);
  println(nameText);
}

void LCD::battery(uint8_t lvl) {
  
  drawRect(69, 0, 15, 7, BLACK);
  drawLine(68, 2, 68, 4, BLACK);
  switch(lvl) {
    case 1:
      fillRect(71,2,2,3,BLACK);
      break;
    case 2:
      fillRect(71,2,2,3,BLACK);
      fillRect(74,2,2,3,BLACK);
      break;
    case 3:
      fillRect(71,2,2,3,BLACK);
      fillRect(74,2,2,3,BLACK);
      fillRect(77,2,2,3,BLACK);
      break;
    case 4:
      fillRect(71,2,2,3,BLACK);
      fillRect(74,2,2,3,BLACK);
      fillRect(77,2,2,3,BLACK);
      fillRect(80,2,2,3,BLACK);
      break;
  }
}

void LCD::trimmed(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY) {
  
  char tLY = max(min(map(LY,112,144,-16,16),16),-16);
  char tLX = max(min(map(LX,112,144,-16,16),16),-16);
  char tRX = max(min(map(RX,112,144,-16,16),16),-16);
  char tRY = max(min(map(RY,112,144,-16,16),16),-16);

  drawLine(2, 9, 2, 43, BLACK);
  drawLine(5, 45, 39, 45, BLACK);
  drawLine(44, 45, 78, 45, BLACK);
  drawLine(81, 9, 81, 43, BLACK);
  
  drawLine(0, 26, 4, 26, BLACK);
  drawLine(22, 43, 22, 47, BLACK);
  drawLine(61, 43, 61, 47, BLACK);
  drawLine(79, 26, 83, 26, BLACK);
  
  fillRect(1,25-tLY,3,3,BLACK);
  fillRect(21+tLX,44,3,3,BLACK);
  fillRect(60+tRX,44,3,3,BLACK);
  fillRect(80,25-tRY,3,3,BLACK);
  
}

void LCD::sticks(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY) {
  
  char tLY = max(min(map(LY,0,255,-14,14),14),-14);
  char tLX = max(min(map(LX,0,255,-14,14),14),-14);
  char tRX = max(min(map(RX,0,255,-14,14),14),-14);
  char tRY = max(min(map(RY,0,255,-14,14),14),-14);
  
  drawRoundRect(8,9,33,33,1,BLACK);
  drawRoundRect(43,9,33,33,1,BLACK);
  
  fillRoundRect(22+tLX,23-tLY,5,5,1,BLACK);
  fillRoundRect(57+tRX,23-tRY,5,5,1,BLACK);
  
  //drawLine(23+LX, 25-LY, 25+LX, 25-LY, BLACK);
  //drawLine(24+LX, 24-LY, 24+LX, 26-LY, BLACK);
  //drawLine(58+RX, 25-RY, 60+RX, 25-RY, BLACK);
  //drawLine(59+RX, 24-RY, 59+RX, 26-RY, BLACK);
  drawPixel(24+tLX, 25-tLY, WHITE);
  drawPixel(59+tRX, 25-tRY, WHITE);

}

void LCD::keySW(uint8_t keysw) {
  
  if(bitRead(keysw, 0)) {
    fillRect(63,0,3,3,BLACK);
  } else {
    drawRect(63,0,3,3,BLACK);
    drawRect(63,1,2,2,WHITE);
  }
  if(bitRead(keysw, 1)) {
    fillRect(63,4,3,3,BLACK);
  } else {
    drawRect(63,4,3,3,BLACK);
    drawRect(63,4,2,2,WHITE);
  }
  
  if(bitRead(keysw, 2)) {
    fillRect(59,0,3,3,BLACK);
  } else {
    drawRect(59,0,3,3,BLACK);
    drawRect(60,1,2,2,WHITE);
  }
  if(bitRead(keysw, 3)) {
    fillRect(59,4,3,3,BLACK);
  } else {
    drawRect(59,4,3,3,BLACK);
    drawRect(60,4,2,2,WHITE);
  }
  
}

void LCD::control(uint8_t tx, uint8_t t24, uint8_t t433) {
  
  setTextColor(BLACK);
  setTextSize(1);

  if(tx) {
    drawLine(0, 5, 0, 6, BLACK);
    drawLine(2, 4, 2, 6, BLACK);
    drawLine(4, 3, 4, 6, BLACK);
    drawLine(6, 2, 6, 6, BLACK);
    drawLine(8, 1, 8, 6, BLACK);
  }
  if(t433 && !t24) {
    setCursor(12,0);
    println("433");
  } else if(t24 && !t433) {
    setCursor(12,0);
    println("2.4");
  } else {
    setCursor(12,0);
    println("DUAL");
  } 
}

//============================== PANELS ===========================================================

void LCD::startPanel() {
  
  clearDisplay();
  logo();
  display();
}

void LCD::mainPanel0(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t stickLY, uint8_t stickLX, uint8_t stickRX, uint8_t stickRY, uint8_t keysw) {
  
  clearDisplay();
  battery(bat);
  keySW(keysw);
  control(tx, t24, t433);
  trimmed(trimLY,trimLX,trimRX,trimRY);
  sticks(stickLY,stickLX,stickRX,stickRY);
  display();
}

void LCD::mainPanel1(uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB) {
  
  LX = max(min(map(LX,0,255,0,100),100),0);
  LY = max(min(map(LY,0,255,0,100),100),0);
  RX = max(min(map(RX,0,255,0,100),100),0);
  RY = max(min(map(RY,0,255,0,100),100),0);
  VRA = max(min(map(VRA,0,255,0,100),100),0);
  VRB = max(min(map(VRB,0,255,0,100),100),0);
  
  clearDisplay();
  setTextColor(BLACK);
  setTextSize(1);
  setCursor(0,0);
  println("LX:");
  println("LY:");
  println("RX:");
  println("RY:");
  println("VRA:");
  println("VRB:");
  
  drawRect(23,0,34,7,BLACK);
  drawRect(23,8,34,7,BLACK);
  drawRect(23,16,34,7,BLACK);
  drawRect(23,24,34,7,BLACK);
  drawRect(23,32,34,7,BLACK);
  drawRect(23,40,34,7,BLACK);
  
  fillRect(24,1,LX/3,6,BLACK);
  fillRect(24,9,LY/3,6,BLACK);
  fillRect(24,17,RX/3,6,BLACK);
  fillRect(24,25,RY/3,6,BLACK);
  fillRect(24,33,VRA/3,6,BLACK);
  fillRect(24,41,VRB/3,6,BLACK);
  
  setCursor(59,0); print(LX); print("%");
  setCursor(59,8); print(LY); print("%");
  setCursor(59,16); print(RX); print("%");
  setCursor(59,24); print(RY); print("%");
  setCursor(59,32); print(VRA); print("%");
  setCursor(59,40); print(VRB); print("%");
  
  display();
}

void LCD::mainPanel2(float bat, uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB) {
  
  clearDisplay();
  setTextColor(BLACK);
  setTextSize(2);
  setCursor(12,0);
  print(bat,1); print("V");
  trimmed(trimLY,trimLX,trimRX,trimRY);
  
  drawLine(7, 21, 37, 21, BLACK);
  drawLine(7, 29, 37, 29, BLACK);
  drawLine(7, 37, 37, 37, BLACK);
  drawLine(46, 21, 76, 21, BLACK);
  drawLine(46, 29, 76, 29, BLACK);
  drawLine(46, 37, 76, 37, BLACK);
  drawLine(22, 18, 22, 24, BLACK);
  drawLine(22, 26, 22, 32, BLACK);
  drawLine(22, 34, 22, 40, BLACK);
  drawLine(61, 18, 61, 24, BLACK);
  drawLine(61, 26, 61, 32, BLACK);
  drawLine(61, 34, 61, 40, BLACK);
  
  char tLX = max(min(map(LX,0,255,-15,15),15),-15);
  char tLY = max(min(map(LY,0,255,-15,15),15),-15);
  char tRX = max(min(map(RX,0,255,-15,15),15),-15);
  char tRY = max(min(map(RY,0,255,-15,15),15),-15);
  char tVRA = max(min(map(VRA,0,255,-15,15),15),-15);
  char tVRB = max(min(map(VRB,0,255,-15,15),15),-15);
  
  if(tLX > 0) {
    fillRect(23,19,tLX,5,BLACK);
  } else if(tLX < 0) {
    fillRect(22+tLX,19,(tLX*-1),5,BLACK);
  }
  if(tLY > 0) {
    fillRect(23,27,tLY,5,BLACK);
  } else if(tLY < 0) {
    fillRect(22+tLY,27,(tLY*-1),5,BLACK);
  }
  if(tRX > 0) {
    fillRect(23,35,tRX,5,BLACK);
  } else if(tRX < 0) {
    fillRect(22+tRX,35,(tRX*-1),5,BLACK);
  }
  if(tRY > 0) {
    fillRect(62,19,tRY,5,BLACK);
  } else if(tRY < 0) {
    fillRect(61+tRY,19,(tRY*-1),5,BLACK);
  }
  if(tVRA > 0) {
    fillRect(62,27,tVRA,5,BLACK);
  } else if(tVRA < 0) {
    fillRect(61+tVRA,27,(tVRA*-1),5,BLACK);
  }
  if(tVRB > 0) {
    fillRect(62,35,tVRB,5,BLACK);
  } else if(tVRB < 0) {
    fillRect(61+tVRB,35,(tVRB*-1),5,BLACK);
  }
  
  display();
}

void LCD::mainPanel3(uint8_t trimLY, uint8_t trimLX, uint8_t trimRX, uint8_t trimRY, uint8_t LY, uint8_t LX, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB) {
  
  clearDisplay();
  setTextColor(BLACK);
  setTextSize(1);
  setCursor(0,0);
  print("LX:"); print(LX); print(" TR:"); println(map(trimLX,0,255,-128,128));
  print("LY:"); print(LY); print(" TR:"); println(map(trimLY,0,255,-128,128));
  print("RX:"); print(RX); print(" TR:"); println(map(trimRX,0,255,-128,128));
  print("RY:"); print(RY); print(" TR:"); println(map(trimRY,0,255,-128,128));
  print("VRA:"); println(VRA);
  print("VRB:"); println(VRB);
  
  display(); 
}

void LCD::mainPanel4(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t keysw, float rateNRF24, float rate433, uint16_t cps, uint8_t rateLCD) {
  
  clearDisplay();
  battery(bat);
  keySW(keysw);
  control(tx, t24, t433);
  
  setTextColor(BLACK);
  setTextSize(1);
  setCursor(0,15);
  
  if(rateNRF24 > 999) {
    rateNRF24 /= 1000;  // kB/s
    print("2.4: ");  print(rateNRF24,2); println("kB/s");
  } else {
    print("2.4: "); print(rateNRF24,0); println(" B/s");  
  }
  if(rate433 > 999) {
    rate433 /= 1000;  // kB/s
    print("433: ");  print(rate433,2); println("kB/s");
  } else {
    print("433: "); print(rate433,0); println(" B/s");
  }
  
  print("Freq: "); print(cps); println(" Hz");
  print("Lcd: "); print(rateLCD); println(" Hz");
  
  display();
}

void LCD::mainPanel5(uint8_t bat, uint8_t tx, uint8_t t24, uint8_t t433, uint8_t keysw, uint8_t limitRX, uint8_t limitRY) {
  
  clearDisplay();
  battery(bat);
  keySW(keysw);
  control(tx, t24, t433);
  setTextColor(BLACK);
  setTextSize(1);
  
  if(limitRX == limitRY) {
    
    limitRX = map(limitRX,0,127,0,100);
    setCursor(0,27);
    print("RX-RY");
    setTextSize(2);
    setCursor(35,20);
    print(limitRX); print("%");
    
  } else {
    
    setCursor(0,27);
    print("RX-RY");
    setTextSize(2);
    setCursor(35,20);
    print("DIFF");
  }
  display();
}

void LCD::mainMenu(uint8_t positionNumber) {
  
  static const unsigned char PROGMEM icoLCD[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x08, 0x00, 0x00, 0x00, 0x10, 0x0B, 0xBB,
    0xB8, 0x00, 0x10, 0x0B, 0xBB, 0xB8, 0x00, 0x10, 0x0B, 0xBB, 0xB8, 0x00, 0x10, 0x08, 0x00, 0x00,
    0x00, 0x10, 0x0B, 0xBB, 0x80, 0x00, 0x10, 0x0B, 0xBB, 0x80, 0x00, 0x10, 0x0B, 0xBB, 0x80, 0x00,
    0x10, 0x08, 0x00, 0x00, 0x00, 0x10, 0x0B, 0xB8, 0x00, 0x00, 0x10, 0x0B, 0xB8, 0x00, 0x00, 0x10,
    0x0B, 0xB8, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x10, 0x0B, 0x80, 0x00, 0x00, 0x10, 0x0B,
    0x80, 0x00, 0x00, 0x10, 0x0B, 0x80, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x10, 0x0F, 0xFF,
    0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoCalibration[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x1F,
    0xFF, 0xFF, 0xFF, 0xF8, 0x38, 0x00, 0x00, 0x00, 0x1C, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x34, 0x00,
    0x42, 0x00, 0x2C, 0x30, 0x38, 0x00, 0x1C, 0x0C, 0x31, 0xC7, 0x00, 0xE3, 0x8C, 0x32, 0x00, 0x81,
    0x00, 0x4C, 0x32, 0x00, 0x81, 0x00, 0x4C, 0x32, 0x00, 0x99, 0x00, 0x4C, 0x34, 0x38, 0x5A, 0x1C,
    0x2C, 0x34, 0x28, 0x5A, 0x14, 0x2C, 0x34, 0x38, 0x5A, 0x1C, 0x2C, 0x32, 0x00, 0x99, 0x00, 0x4C,
    0x32, 0x00, 0x81, 0x00, 0x4C, 0x32, 0x00, 0x81, 0x00, 0x4C, 0x31, 0xC7, 0x00, 0xE3, 0x8C, 0x30,
    0x38, 0x00, 0x1C, 0x0C, 0x34, 0x00, 0x42, 0x00, 0x2C, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x38, 0x00,
    0x00, 0x00, 0x1C, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoTrimmed[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00,
    0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70,
    0x38, 0x1C, 0x00, 0x00, 0x88, 0x38, 0x22, 0x00, 0x01, 0x04, 0x38, 0x41, 0x00, 0x01, 0x04, 0x38,
    0x41, 0x00, 0x01, 0x04, 0x38, 0x41, 0x00, 0x00, 0x88, 0x38, 0x22, 0x00, 0x00, 0x70, 0x38, 0x1C,
    0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x44, 0x1C, 0x00, 0x00, 0x70, 0x82, 0x1C, 0x00,
    0x00, 0x70, 0x82, 0x1C, 0x00, 0x00, 0x70, 0x82, 0x1C, 0x00, 0x00, 0x70, 0x44, 0x1C, 0x00, 0x00,
    0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70,
    0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38, 0x1C, 0x00, 0x00, 0x70, 0x38,
    0x1C, 0x00, 0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoSound[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xE0, 0x84, 0x00, 0x00, 0x01,
    0xF0, 0x44, 0x00, 0x00, 0x03, 0xF0, 0x42, 0x00, 0x00, 0x07, 0xF4, 0x22, 0x00, 0x00, 0x0F, 0xF2,
    0x21, 0x00, 0x00, 0xFF, 0xF2, 0x11, 0x00, 0x01, 0xFF, 0xF1, 0x11, 0x00, 0x01, 0xFF, 0xF1, 0x11,
    0x00, 0x01, 0xFF, 0xF1, 0x11, 0x00, 0x01, 0xFF, 0xF1, 0x11, 0x00, 0x01, 0xFF, 0xF1, 0x11, 0x00,
    0x00, 0xFF, 0xF2, 0x11, 0x00, 0x00, 0x0F, 0xF2, 0x21, 0x00, 0x00, 0x07, 0xF4, 0x22, 0x00, 0x00,
    0x03, 0xF0, 0x42, 0x00, 0x00, 0x01, 0xF0, 0x44, 0x00, 0x00, 0x00, 0xE0, 0x84, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoBattery[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x40, 0x01, 0x77, 0x77,
    0x77, 0x40, 0x07, 0x77, 0x77, 0x77, 0x40, 0x07, 0x77, 0x77, 0x77, 0x40, 0x07, 0x77, 0x77, 0x77,
    0x40, 0x07, 0x77, 0x77, 0x77, 0x40, 0x07, 0x77, 0x77, 0x77, 0x40, 0x07, 0x77, 0x77, 0x77, 0x40,
    0x01, 0x77, 0x77, 0x77, 0x40, 0x01, 0x00, 0x00, 0x00, 0x40, 0x01, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoTransmission[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x88,
    0x00, 0x22, 0x00, 0x00, 0x91, 0x01, 0x12, 0x00, 0x01, 0x12, 0x00, 0x91, 0x00, 0x01, 0x22, 0x38,
    0x89, 0x00, 0x01, 0x24, 0x44, 0x49, 0x00, 0x01, 0x24, 0x44, 0x49, 0x00, 0x01, 0x24, 0x44, 0x49,
    0x00, 0x01, 0x22, 0x38, 0x89, 0x00, 0x01, 0x12, 0x10, 0x91, 0x00, 0x00, 0x91, 0x11, 0x12, 0x00,
    0x00, 0x88, 0x10, 0x22, 0x00, 0x00, 0x40, 0x10, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoLimits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x04, 0x18, 0x20, 0x00, 0x00, 0x06, 0x18, 0x60, 0x00, 0x00, 0x07, 0x18, 0xE0,
    0x00, 0x0F, 0xFF, 0x99, 0xFF, 0xF0, 0x0F, 0xFF, 0xDB, 0xFF, 0xF0, 0x0F, 0xFF, 0x99, 0xFF, 0xF0,
    0x00, 0x07, 0x18, 0xE0, 0x00, 0x00, 0x06, 0x18, 0x60, 0x00, 0x00, 0x04, 0x18, 0x20, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoMixer[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x0F, 0xFF,
    0xFF, 0xFF, 0xF0, 0x1F, 0xBF, 0x7E, 0xFD, 0xF8, 0x1F, 0xFF, 0x7E, 0xFD, 0xF8, 0x1E, 0x0F, 0x7E,
    0xFF, 0xF8, 0x1E, 0xEF, 0x7E, 0xF0, 0x78, 0x1E, 0x0F, 0x7E, 0xF7, 0x78, 0x1F, 0xFF, 0xFE, 0xF0,
    0x78, 0x1F, 0xBC, 0x1E, 0xFF, 0xF8, 0x1F, 0xBD, 0xDE, 0xFD, 0xF8, 0x1F, 0xBC, 0x1F, 0xFD, 0xF8,
    0x1F, 0xBF, 0xF8, 0x3D, 0xF8, 0x1F, 0xBF, 0x7B, 0xBD, 0xF8, 0x1F, 0xBF, 0x78, 0x3D, 0xF8, 0x1F,
    0xBF, 0x7F, 0xFD, 0xF8, 0x1F, 0xBF, 0x7E, 0xFD, 0xF8, 0x1F, 0xBF, 0x7E, 0xFD, 0xF8, 0x1F, 0xFF,
    0xFF, 0xFF, 0xF8, 0x1F, 0xBF, 0x7E, 0xFD, 0xF8, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF,
    0xFF, 0xE0, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoModel[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFE, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x0F,
    0xFF, 0xE0, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x3E, 0x7C, 0xF8, 0x00, 0x00, 0x7E, 0x38,
    0xFC, 0x00, 0x00, 0x7E, 0x10, 0xFC, 0x00, 0x00, 0x7E, 0x44, 0xFC, 0x00, 0x00, 0x7E, 0x6C, 0xFC,
    0x00, 0x00, 0x7E, 0x7C, 0xFC, 0x00, 0x00, 0x7E, 0x7C, 0xFC, 0x00, 0x00, 0x7E, 0x7C, 0xFC, 0x00,
    0x00, 0x7E, 0x7C, 0xFC, 0x00, 0x00, 0x7E, 0x7C, 0xFC, 0x00, 0x00, 0x3E, 0x7C, 0xF8, 0x00, 0x00,
    0x1E, 0x7C, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x03,
    0xFF, 0x80, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM icoVersion[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00,
    0x10, 0x40, 0x00, 0x00, 0x00, 0x10, 0x40, 0x20, 0x00, 0x00, 0x20, 0x20, 0xD8, 0x00, 0x00, 0x10,
    0x41, 0x04, 0x00, 0x00, 0x10, 0x41, 0x04, 0x00, 0x00, 0x0D, 0x82, 0x02, 0x00, 0x00, 0x07, 0x01,
    0x04, 0x00, 0x00, 0x07, 0x01, 0x04, 0x00, 0x00, 0x07, 0x00, 0xD8, 0x00, 0x00, 0x07, 0x00, 0x70,
    0x00, 0x00, 0x07, 0x00, 0xF0, 0x00, 0x00, 0x07, 0x01, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00,
    0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0x80, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x10,
    0x40, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10, 0x40,
    0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM ico433[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x80, 0x00, 0x00, 0x01, 0x84, 0x40, 0x00, 0x00, 0x80, 0x62, 0x20, 0x00, 0x00, 0xC0, 0x11, 0x20,
    0x00, 0x00, 0xE0, 0x09, 0x10, 0x00, 0x00, 0xF0, 0xC8, 0x90, 0x00, 0x00, 0xF8, 0xC4, 0x90, 0x00,
    0x00, 0xFD, 0x04, 0x90, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x9F, 0xE0, 0xAE, 0xE0, 0x01, 0xCF,
    0xF0, 0xA2, 0x20, 0x01, 0xE3, 0xF8, 0xE6, 0x60, 0x03, 0xF0, 0x00, 0x22, 0x20, 0x03, 0xF0, 0x00,
    0x2E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  static const unsigned char PROGMEM ico24[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x80, 0x00, 0x00, 0x01, 0x84, 0x40, 0x00, 0x00, 0x80, 0x62, 0x20, 0x00, 0x00, 0xC0, 0x11, 0x20,
    0x00, 0x00, 0xE0, 0x09, 0x10, 0x00, 0x00, 0xF0, 0xC8, 0x90, 0x00, 0x00, 0xF8, 0xC4, 0x90, 0x00,
    0x00, 0xFD, 0x04, 0x90, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x9F, 0xE0, 0xE1, 0x40, 0x01, 0xCF,
    0xF0, 0x21, 0x40, 0x01, 0xE3, 0xF8, 0xE1, 0xC0, 0x03, 0xF0, 0x00, 0x80, 0x40, 0x03, 0xF0, 0x00,
    0xE4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
  static const unsigned char PROGMEM icoSystem[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x0E,
    0x03, 0x80, 0x00, 0x00, 0x0E, 0x03, 0x80, 0x00, 0x00, 0x0E, 0x03, 0x80, 0x00, 0x00, 0x0F, 0x07,
    0x80, 0x00, 0x00, 0x07, 0x8F, 0x00, 0x00, 0x00, 0x03, 0xFE, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00,
    0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x73, 0xFF, 0x00,
    0x01, 0xF0, 0x74, 0x01, 0x80, 0x01, 0xFF, 0x8D, 0xFD, 0x80, 0x01, 0xF0, 0x74, 0x01, 0x80, 0x00,
    0x00, 0x73, 0xFF, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  
  if(positionNumber > 13) positionNumber = 13;
  if(positionNumber == 0) return void();
  
  clearDisplay();
  setCursor(0,0);
  setTextColor(BLACK);
  setTextSize(1);
  //drawRoundRect(80,0,4,48,1,BLACK);
  
  switch(positionNumber) {
    case 1:  // LCD
      setCursor(33,0);
      print("LCD");
      drawBitmap(22, 10, icoLCD, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,1,2,4,BLACK);
      break;
    case 2:  // Calibration
      setCursor(9,0);
      print("Calibration");
      drawBitmap(22, 10, icoCalibration, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,5,2,5,BLACK);
      break;
    case 3:  // Trimmed
      setCursor(21,0);
      print("Trimmed");
      drawBitmap(22, 10, icoTrimmed, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,10,2,4,BLACK);
      break;
    case 4:  // Sound
      setCursor(27,0);
      print("Sound");
      drawBitmap(22, 10, icoSound, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,14,2,5,BLACK);
      break;
    case 5:  // Battery
      setCursor(21,0);
      print("Battery");
      drawBitmap(22, 10, icoBattery, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,19,2,4,BLACK);
      break;
    case 6:  // Transmission
      setCursor(6,0);
      print("Transmission");
      drawBitmap(22, 10, icoTransmission, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,23,2,5,BLACK);
      break;
    case 7:  // Limits
      setCursor(24,0);
      print("Limits");
      drawBitmap(22, 10, icoLimits, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,28,2,4,BLACK);
      break;
    case 8:  // Mixer
      setCursor(27,0);
      print("Mixer");
      drawBitmap(22, 10, icoMixer, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,32,2,5,BLACK);
      break;
    case 9:  // Model
      setCursor(27,0);
      print("Model");
      drawBitmap(22, 10, icoModel, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,37,2,4,BLACK);
      break;
    case 10:  // Version
      setCursor(21,0);
      print("Version");
      drawBitmap(22, 10, icoVersion, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      //fillRect(81,42,2,5,BLACK);
      break;
    case 11:  // 433MHz
      setCursor(24,0);
      print("433MHz");
      drawBitmap(22, 10, ico433, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      break;
    case 12:  // 2.4GHz
      setCursor(24,0);
      print("2.4GHz");
      drawBitmap(22, 10, ico24, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      break;
    case 13:  // System
      setCursor(24,0);
      print("System");
      drawBitmap(22, 10, icoSystem, 40, 28, BLACK);
      setCursor(24,40);
      print("Select");
      break;
  }
  display();
}

void LCD::subMenuLCD(uint8_t light, uint8_t contrast, uint8_t freq, int pos, boolean sel) {
  
  if(pos > 3) pos = 3;
  if(pos == 0) return void();
  
  clearDisplay();
  window("LCD");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  light = map(light,0,255,0,100);
  contrast = map(contrast,0,127,0,100);
  
  if(pos == 1){if(!sel){ fillRect(2,10,37,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("Light:");    setTextColor(BLACK); setCursor(63,11); print(light); print("%");    }else{ fillRect(62,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("Light:");    setTextColor(WHITE); setCursor(63,11); print(light); print("%");    }}else{ setTextColor(BLACK); setCursor(3,11); print("Light:"); setCursor(63,11); print(light); print("%"); }
  if(pos == 2){if(!sel){ fillRect(2,19,55,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("Contrast:"); setTextColor(BLACK); setCursor(63,20); print(contrast); print("%"); }else{ fillRect(62,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("Contrast:"); setTextColor(WHITE); setCursor(63,20); print(contrast); print("%"); }}else{ setTextColor(BLACK); setCursor(3,20); print("Contrast:"); setCursor(63,20); print(contrast); print("%"); }
  if(pos == 3){if(!sel){ fillRect(2,28,31,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("Freq:");     setTextColor(BLACK); setCursor(57,29); print(freq); print("Hz");     }else{ fillRect(56,28,25,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("Freq:");    setTextColor(WHITE); setCursor(57,29); print(freq); print("Hz");    }}else{ setTextColor(BLACK); setCursor(3,29); print("Freq:"); setCursor(57,29); print(freq); print("Hz"); }
  
  display();
}

void LCD::subMenuCalibration(uint16_t LXmin, uint16_t LXmax, uint16_t LYmin, uint16_t LYmax, uint16_t RXmin, uint16_t RXmax, uint16_t RYmin, uint16_t RYmax, uint16_t LX, uint16_t LY, uint16_t RX, uint16_t RY, int pos, boolean sel) {
  
  if(pos > 8) pos = 8;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Calibration");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  if(pos < 4) {
    
    if(pos == 1){if(!sel){ fillRect(2,10,37,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("LXmin:"); setTextColor(BLACK); setCursor(50,11); print(LXmin); }else{ fillRect(49,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("LXmin:"); setTextColor(WHITE); setCursor(50,11); print(LX); }}else{ setTextColor(BLACK); setCursor(3,11); print("LXmin:"); setCursor(50,11); print(LXmin); }
    if(pos == 2){if(!sel){ fillRect(2,19,37,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("LXmax:"); setTextColor(BLACK); setCursor(50,20); print(LXmax); }else{ fillRect(49,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("LXmax:"); setTextColor(WHITE); setCursor(50,20); print(LX); }}else{ setTextColor(BLACK); setCursor(3,20); print("LXmax:"); setCursor(50,20); print(LXmax); }
    if(pos == 3){if(!sel){ fillRect(2,28,37,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("LYmin:"); setTextColor(BLACK); setCursor(50,29); print(LYmin); }else{ fillRect(49,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("LYmin:"); setTextColor(WHITE); setCursor(50,29); print(LY); }}else{ setTextColor(BLACK); setCursor(3,29); print("LYmin:"); setCursor(50,29); print(LYmin); }
  
  } else if(pos < 7) {
    
    if(pos == 4){if(!sel){ fillRect(2,10,37,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("LYmax:"); setTextColor(BLACK); setCursor(50,11); print(LYmax); }else{ fillRect(49,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("LYmax:"); setTextColor(WHITE); setCursor(50,11); print(LY); }}else{ setTextColor(BLACK); setCursor(3,11); print("LYmax:"); setCursor(50,11); print(LYmax); }
    if(pos == 5){if(!sel){ fillRect(2,19,37,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("RXmin:"); setTextColor(BLACK); setCursor(50,20); print(RXmin); }else{ fillRect(49,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("RXmin:"); setTextColor(WHITE); setCursor(50,20); print(RX); }}else{ setTextColor(BLACK); setCursor(3,20); print("RXmin:"); setCursor(50,20); print(RXmin); }
    if(pos == 6){if(!sel){ fillRect(2,28,37,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("RXmax:"); setTextColor(BLACK); setCursor(50,29); print(RXmax); }else{ fillRect(49,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("RXmax:"); setTextColor(WHITE); setCursor(50,29); print(RX); }}else{ setTextColor(BLACK); setCursor(3,29); print("RXmax:"); setCursor(50,29); print(RXmax); }
  
  } else if(pos < 10) {
    
    if(pos == 7){if(!sel){ fillRect(2,10,37,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("RYmin:"); setTextColor(BLACK); setCursor(50,11); print(RYmin); }else{ fillRect(49,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("RYmin:"); setTextColor(WHITE); setCursor(50,11); print(RY); }}else{ setTextColor(BLACK); setCursor(3,11); print("RYmin:"); setCursor(50,11); print(RYmin); }
    if(pos == 8){if(!sel){ fillRect(2,19,37,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("RYmax:"); setTextColor(BLACK); setCursor(50,20); print(RYmax); }else{ fillRect(49,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("RYmax:"); setTextColor(WHITE); setCursor(50,20); print(RY); }}else{ setTextColor(BLACK); setCursor(3,20); print("RYmax:"); setCursor(50,20); print(RYmax); }

  } 
  display();
}

void LCD::subMenuTrimmed(uint8_t precision, int pos, boolean sel) {
  
  if(pos > 1) pos = 1;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Trimmed");
  setTextSize(1);
  
  switch(pos) {
    case 1:
      if(!sel) {
        fillRect(2,14,61,9,BLACK);
        setTextColor(WHITE,BLACK); setCursor(3,15); print("Precision:"); 
        setTextColor(BLACK); setCursor(68,15); print(precision);
        setCursor(24,39); print("Select"); 
      } else {
        fillRect(67,14,7,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Precision:"); 
        setTextColor(WHITE,BLACK); setCursor(68,15); print(precision);
        setTextColor(BLACK); setCursor(30,39); print("Save");
      }
      break;
  }
  
  display();
}

void LCD::subMenuSound(uint8_t mode, uint8_t volume, int pos, boolean sel) {
  
  if(pos > 2) pos = 2;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Sound");
  setTextSize(1);
  
  switch(pos) {
    case 1:
      if(!sel) {
        fillRect(2,14,31,9,BLACK);
        setTextColor(WHITE,BLACK); setCursor(3,15); print("Mode:"); 
        setTextColor(BLACK); setCursor(63,15); if(mode == 1) { print("On"); } else if(mode == 2) { print("Off"); }
        setCursor(3,24); print("Volume:"); 
        setCursor(63,24); print(map(volume,0,255,0,100)); print("%");
        setCursor(24,39); print("Select"); 
      } else {
        fillRect(62,14,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Mode:"); 
        setTextColor(WHITE,BLACK); setCursor(63,15); if(mode == 1) { print("On"); } else if(mode == 2) { print("Off"); }
        setTextColor(BLACK); setCursor(3,24); print("Volume:"); 
        setCursor(63,24); print(map(volume,0,255,0,100)); print("%");
        setCursor(30,39); print("Save");
      }
      break;
    case 2:
      if(!sel) {
        fillRect(2,23,43,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Mode:"); 
        setCursor(63,15); if(mode == 1) { print("On"); } else if(mode == 2) { print("Off"); }
        setTextColor(WHITE,BLACK); setCursor(3,24); print("Volume:"); 
        setTextColor(BLACK); setCursor(63,24); print(map(volume,0,255,0,100)); print("%");
        setCursor(24,39); print("Select");
      } else {
        fillRect(62,23,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Mode:"); 
        setCursor(63,15); if(mode == 1) { print("On"); } else if(mode == 2) { print("Off"); }
        setCursor(3,24); print("Volume:"); 
        setTextColor(WHITE,BLACK); setCursor(63,24); print(map(volume,0,255,0,100)); print("%");
        setTextColor(BLACK); setCursor(30,39); print("Save");
      }
      break;
  }
  display();
}

void LCD::subMenuBattery(uint8_t rawbatWarn, uint8_t rawbatLvl0, uint8_t rawbatLvl1, uint8_t rawbatLvl2, uint8_t rawbatLvl3, uint8_t rawbatLvl4, uint8_t batFreq, int pos, boolean sel) {
  
  if(pos > 7) pos = 7;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Battery");
  
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  float batWarn = rawbatWarn / 10.0;
  float batLvl0 = rawbatLvl0 / 10.0;
  float batLvl1 = rawbatLvl1 / 10.0;
  float batLvl2 = rawbatLvl2 / 10.0;
  float batLvl3 = rawbatLvl3 / 10.0;
  float batLvl4 = rawbatLvl4 / 10.0;
  
  if(pos < 4) {
    
    if(pos == 1){if(!sel){ fillRect(2,10,31,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("Warn<"); setTextColor(BLACK); setCursor(50,11); print(batWarn,1); print("V"); }else{ fillRect(49,10,31,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("Warn<"); setTextColor(WHITE); setCursor(50,11); print(batWarn,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,11); print("Warn<"); setCursor(50,11); print(batWarn,1); print("V");}
    if(pos == 2){if(!sel){ fillRect(2,19,31,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("Lvl0<"); setTextColor(BLACK); setCursor(50,20); print(batLvl0,1); print("V"); }else{ fillRect(49,19,31,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("Lvl0<"); setTextColor(WHITE); setCursor(50,20); print(batLvl0,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,20); print("Lvl0<"); setCursor(50,20); print(batLvl0,1); print("V");}
    if(pos == 3){if(!sel){ fillRect(2,28,31,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("Lvl1<"); setTextColor(BLACK); setCursor(50,29); print(batLvl1,1); print("V"); }else{ fillRect(49,28,31,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("Lvl1<"); setTextColor(WHITE); setCursor(50,29); print(batLvl1,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,29); print("Lvl1<"); setCursor(50,29); print(batLvl1,1); print("V");}
  
  } else if(pos < 7) {
    
    if(pos == 4){if(!sel){ fillRect(2,10,31,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("Lvl2<"); setTextColor(BLACK); setCursor(50,11); print(batLvl2,1); print("V"); }else{ fillRect(49,10,31,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("Lvl2<"); setTextColor(WHITE); setCursor(50,11); print(batLvl2,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,11); print("Lvl2<"); setCursor(50,11); print(batLvl2,1); print("V");}
    if(pos == 5){if(!sel){ fillRect(2,19,31,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("Lvl3<"); setTextColor(BLACK); setCursor(50,20); print(batLvl3,1); print("V"); }else{ fillRect(49,19,31,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("Lvl3<"); setTextColor(WHITE); setCursor(50,20); print(batLvl3,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,20); print("Lvl3<"); setCursor(50,20); print(batLvl3,1); print("V");}
    if(pos == 6){if(!sel){ fillRect(2,28,31,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("Lvl4<"); setTextColor(BLACK); setCursor(50,29); print(batLvl4,1); print("V"); }else{ fillRect(49,28,31,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("Lvl4<"); setTextColor(WHITE); setCursor(50,29); print(batLvl4,1); print("V"); }}else{ setTextColor(BLACK); setCursor(3,29); print("Lvl4<"); setCursor(50,29); print(batLvl4,1); print("V");}
  
  } else {
    
    if(pos == 7){if(!sel){ fillRect(2,10,31,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("Freq:"); setTextColor(BLACK); setCursor(50,11); print(batFreq); print("Hz");  }else{ fillRect(49,10,25,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("Freq:"); setTextColor(WHITE); setCursor(50,11); print(batFreq); print("Hz"); }}else{ setTextColor(BLACK); setCursor(3,11); print("Freq:"); setCursor(50,11); print(batLvl2,1); print("Hz");}
  }
  display();
}

void LCD::subMenuTransmission(uint8_t tx, uint8_t t433, uint8_t t24, int pos, boolean sel) {
  
  if(pos > 3) pos = 3;
  if(pos == 0) return void();
  
  clearDisplay();
  setTextSize(1);
  window("Transmission");
  
  switch(pos) {
    case 1:
      if(!sel) {
        fillRect(2,10,55,9,BLACK);
        setTextColor(WHITE); setCursor(3,11); print("Transmit:"); 
        setTextColor(BLACK); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,20); print("433Mhz:"); 
        setTextColor(BLACK); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(BLACK); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(24,39); print("Select"); 
      } else {
        fillRect(62,10,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,11); print("Transmit:"); 
        setTextColor(WHITE); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,20); print("433Mhz:"); 
        setTextColor(BLACK); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(BLACK); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(30,39); print("Save"); 
      }
      break;
    case 2:
      if(!sel) {
        fillRect(2,19,43,9,BLACK);
        setTextColor(BLACK); setCursor(3,11); print("Transmit:"); 
        setTextColor(BLACK); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(WHITE); setCursor(3,20); print("433Mhz:"); 
        setTextColor(BLACK); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(BLACK); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(24,39); print("Select"); 
      } else {
        fillRect(62,19,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,11); print("Transmit:"); 
        setTextColor(BLACK); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,20); print("433Mhz:"); 
        setTextColor(WHITE); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(BLACK); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(30,39); print("Save"); 
      }
      break;
    case 3:
      if(!sel) {
        fillRect(2,28,43,9,BLACK);
        setTextColor(BLACK); setCursor(3,11); print("Transmit:"); 
        setTextColor(BLACK); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,20); print("433Mhz:"); 
        setTextColor(BLACK); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(WHITE); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(BLACK); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(24,39); print("Select"); 
      } else {
        fillRect(62,28,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,11); print("Transmit:"); 
        setTextColor(BLACK); setCursor(63,11); if(tx) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,20); print("433Mhz:"); 
        setTextColor(BLACK); setCursor(63,20); if(t433) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(3,29); print("2.4Ghz:"); 
        setTextColor(WHITE); setCursor(63,29); if(t24) { print("On"); } else { print("Off"); }
        setTextColor(BLACK); setCursor(30,39); print("Save"); 
      }
      break;
  }
  display();
}

void LCD::subMenuLimits(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, int pos, boolean sel) {
  
  if(pos > 6) pos = 6;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Limits");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  LX = map(LX,0,127,0,100);
  LY = map(LY,0,127,0,100);
  RX = map(RX,0,127,0,100);
  RY = map(RY,0,127,0,100);
  VRA = map(VRA,0,127,0,100);
  VRB = map(VRB,0,127,0,100);
  
  if(pos < 4) {
    
    if(pos == 1){if(!sel){ fillRect(2,10,19,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("LX:"); setTextColor(BLACK); setCursor(50,11); print(LX); print("%"); }else{ fillRect(49,10,25,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("LX:"); setTextColor(WHITE); setCursor(50,11); print(LX); print("%"); }}else{ setTextColor(BLACK); setCursor(3,11); print("LX:"); setCursor(50,11); print(LX); print("%"); }
    if(pos == 2){if(!sel){ fillRect(2,19,19,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("LY:"); setTextColor(BLACK); setCursor(50,20); print(LY); print("%"); }else{ fillRect(49,19,25,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("LY:"); setTextColor(WHITE); setCursor(50,20); print(LY); print("%"); }}else{ setTextColor(BLACK); setCursor(3,20); print("LY:"); setCursor(50,20); print(LY); print("%"); }
    if(pos == 3){if(!sel){ fillRect(2,28,19,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("RX:"); setTextColor(BLACK); setCursor(50,29); print(RX); print("%"); }else{ fillRect(49,28,25,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("RX:"); setTextColor(WHITE); setCursor(50,29); print(RX); print("%"); }}else{ setTextColor(BLACK); setCursor(3,29); print("RX:"); setCursor(50,29); print(RX); print("%"); }
  
  } else {
    
    if(pos == 4){if(!sel){ fillRect(2,10,19,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("RY:");  setTextColor(BLACK); setCursor(50,11); print(RY);  print("%"); }else{ fillRect(49,10,25,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("RY:");  setTextColor(WHITE); setCursor(50,11); print(RY);  print("%"); }}else{ setTextColor(BLACK); setCursor(3,11); print("RY:"); setCursor(50,11); print(RY); print("%"); }
    if(pos == 5){if(!sel){ fillRect(2,19,19,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("VRA:"); setTextColor(BLACK); setCursor(50,20); print(VRA); print("%"); }else{ fillRect(49,19,25,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("VRA:"); setTextColor(WHITE); setCursor(50,20); print(VRA); print("%"); }}else{ setTextColor(BLACK); setCursor(3,20); print("VRA:"); setCursor(50,20); print(VRA); print("%"); }
    if(pos == 6){if(!sel){ fillRect(2,28,19,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("VRB:"); setTextColor(BLACK); setCursor(50,29); print(VRB); print("%"); }else{ fillRect(49,28,25,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("VRB:"); setTextColor(WHITE); setCursor(50,29); print(VRB); print("%"); }}else{ setTextColor(BLACK); setCursor(3,29); print("VRB:"); setCursor(50,29); print(VRB); print("%"); }
  
  }
  display();
}

char* LCD::_chConvNrTochar(uint8_t nr) {
  
  switch(nr) {
    case 1:
      return "OFF";
      break;
    case 2:
      return "NOR";
      break;
    case 3:
      return "INV";
      break;
    case 4:
      return "LX";
      break;
    case 5:
      return "LY";
      break;
    case 6:
      return "RX";
      break;
    case 7:
      return "RY";
      break;
    case 8:
      return "VRA";
      break;
    case 9:
      return "VRB";
      break;
  }
}

char* LCD::_swConvNrTochar(uint8_t nr) {
  
  switch(nr) {
    case 1:
      return "OFF";
      break;
    case 2:
      return "NOR";
      break;
    case 3:
      return "INV";
      break;
  }
}

void LCD::subMenuMixer(uint8_t LX, uint8_t LY, uint8_t RX, uint8_t RY, uint8_t VRA, uint8_t VRB, uint8_t SWA, uint8_t SWA1, uint8_t SWB, uint8_t SWB1, int pos, boolean sel) {
  
  if(pos > 10) pos = 10;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Mixer");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  char* ch1lx = _chConvNrTochar(LX);
  char* ch2ly = _chConvNrTochar(LY);
  char* ch3rx = _chConvNrTochar(RX);
  char* ch4ry = _chConvNrTochar(RY);
  char* ch5vra = _chConvNrTochar(VRA);
  char* ch6vrb = _chConvNrTochar(VRB);
  char* ch7swa = _swConvNrTochar(SWA);
  char* ch8swa1 = _swConvNrTochar(SWA1);
  char* ch9swb = _swConvNrTochar(SWB);
  char* ch10swb1 = _swConvNrTochar(SWB1);
  
  /*
  CH1-LX - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH2-LY - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH3-RX - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH4-RY - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH5-VRA - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH6-VRB - OFF / NOR / INV / LX / LY / RX / RY / VRA / VRB (1,2,3,4,5,6,7,8,9)
  CH7-SWA - OFF / NOR / INV (1,2,3)
  CH8-SWA1 - OFF / NOR / INV (1,2,3)
  CH9-SWB - OFF / NOR / INV (1,2,3)
  CH10-SWB1 - OFF / NOR / INV (1,2,3)
  */
  
  if(pos < 4) {
    
    if(pos == 1){if(!sel){ fillRect(2,10,43,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("CH1-LX:"); setTextColor(BLACK); setCursor(61,11); print(ch1lx); }else{ fillRect(60,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("CH1-LX:"); setTextColor(WHITE); setCursor(61,11); print(ch1lx); }}else{ setTextColor(BLACK); setCursor(3,11); print("CH1-LX:"); setCursor(61,11); print(ch1lx); }
    if(pos == 2){if(!sel){ fillRect(2,19,43,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("CH2-LY:"); setTextColor(BLACK); setCursor(61,20); print(ch2ly); }else{ fillRect(60,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("CH2-LY:"); setTextColor(WHITE); setCursor(61,20); print(ch2ly); }}else{ setTextColor(BLACK); setCursor(3,20); print("CH2-LY:"); setCursor(61,20); print(ch2ly); }
    if(pos == 3){if(!sel){ fillRect(2,28,43,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("CH3-RX:"); setTextColor(BLACK); setCursor(61,29); print(ch3rx); }else{ fillRect(60,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("CH3-RX:"); setTextColor(WHITE); setCursor(61,29); print(ch3rx); }}else{ setTextColor(BLACK); setCursor(3,29); print("CH3-RX:"); setCursor(61,29); print(ch3rx); }
  
  } else if(pos < 7) {
    
    if(pos == 4){if(!sel){ fillRect(2,10,43,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("CH4-RY:"); setTextColor(BLACK); setCursor(61,11);  print(ch4ry); }else{ fillRect(60,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("CH4-RY:"); setTextColor(WHITE); setCursor(61,11); print(ch4ry); }}else{ setTextColor(BLACK); setCursor(3,11); print("CH4-RY:"); setCursor(61,11); print(ch4ry); }
    if(pos == 5){if(!sel){ fillRect(2,19,49,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("CH5-VRA:"); setTextColor(BLACK); setCursor(61,20); print(ch5vra); }else{ fillRect(60,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("CH5-VRA:"); setTextColor(WHITE); setCursor(61,20); print(ch5vra); }}else{ setTextColor(BLACK); setCursor(3,20); print("CH5-VRA:"); setCursor(61,20); print(ch5vra); }
    if(pos == 6){if(!sel){ fillRect(2,28,49,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("CH6-VRB:"); setTextColor(BLACK); setCursor(61,29); print(ch6vrb); }else{ fillRect(60,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("CH6-VRB:"); setTextColor(WHITE); setCursor(61,29); print(ch6vrb); }}else{ setTextColor(BLACK); setCursor(3,29); print("CH6-VRB:"); setCursor(61,29); print(ch6vrb); }
  
  } else if(pos < 10) {
    
    if(pos == 7){if(!sel){ fillRect(2,10,49,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("CH7-SWA:"); setTextColor(BLACK); setCursor(61,11);  print(ch7swa); }else{ fillRect(60,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("CH7-SWA:"); setTextColor(WHITE); setCursor(61,11); print(ch7swa); }}else{ setTextColor(BLACK); setCursor(3,11); print("CH7-SWA:"); setCursor(61,11); print(ch7swa); }
    if(pos == 8){if(!sel){ fillRect(2,19,55,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("CH8-SWA1:"); setTextColor(BLACK); setCursor(61,20); print(ch8swa1); }else{ fillRect(60,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("CH8-SWA1:"); setTextColor(WHITE); setCursor(61,20); print(ch8swa1); }}else{ setTextColor(BLACK); setCursor(3,20); print("CH8-SWA1:"); setCursor(61,20); print(ch8swa1); }
    if(pos == 9){if(!sel){ fillRect(2,28,49,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("CH9-SWB:"); setTextColor(BLACK); setCursor(61,29);  print(ch9swb); }else{ fillRect(60,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("CH9-SWB:"); setTextColor(WHITE); setCursor(61,29); print(ch9swb); }}else{ setTextColor(BLACK); setCursor(3,29); print("CH9-SWB:"); setCursor(61,29); print(ch9swb); }
  
  } else {    
    
    if(pos == 10){if(!sel){ fillRect(2,10,61,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("CH10-SWB1:"); setTextColor(BLACK); setCursor(64,11); print(ch10swb1); }else{ fillRect(63,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("CH10-SWB1:"); setTextColor(WHITE); setCursor(64,11); print(ch10swb1); }}else{ setTextColor(BLACK); setCursor(3,11); print("CH10-SWB1:"); setCursor(64,11); print(ch10swb1); }
  }
  display();
}

void LCD::subMenuModel(uint8_t mode, int pos, boolean sel) {
  
  if(pos > 1) pos = 1;
  if(pos == 0) return void();
  
  clearDisplay();
  window("Model");
  setTextSize(1);

  switch(pos) {
    case 1:
      if(!sel) {
        fillRect(2,14,31,9,BLACK);
        setTextColor(WHITE,BLACK); setCursor(3,15); print("Mode:"); 
        setTextColor(BLACK); setCursor(45,15); if(mode == 1) { print("3PI"); } else if(mode == 2) { print("MR"); }
        setCursor(24,39); print("Select"); 
      } else {
        fillRect(44,14,19,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Mode:"); 
        setTextColor(WHITE,BLACK); setCursor(45,15); if(mode == 1) { print("3PI"); } else if(mode == 2) { print("MR"); }
        setTextColor(BLACK); setCursor(30,39); print("Save");
      }
      break;
  }
  display();
}

void LCD::subMenuVersion(char* git, char* vers, char* date, int pos, boolean sel) {
  
  clearDisplay();
  window("Version");
  setTextSize(1);
  setTextColor(BLACK);
  setCursor(3,11); print("GIT:"); print(git);
  setCursor(3,20); print("Ver:"); print(vers);
  setCursor(3,29); print("Date:"); print(date);
  setCursor(30,39); print("Menu");
  display();
}

void LCD::subMenu433(uint16_t bps, int pos, boolean sel) {
  
  if(pos > 1) pos = 1;
  if(pos == 0) return void();
  
  clearDisplay();
  window("433MHz");
  setTextSize(1);

  switch(pos) {
    case 1:
      if(!sel) {
        fillRect(2,14,37,9,BLACK);
        setTextColor(WHITE,BLACK); setCursor(3,15); print("Speed:"); 
        setTextColor(BLACK); setCursor(40,15); print(bps); print("b/s");
        setCursor(24,39); print("Select"); 
      } else {
        fillRect(39,14,43,9,BLACK);
        setTextColor(BLACK); setCursor(3,15); print("Speed:"); 
        setTextColor(WHITE,BLACK); setCursor(40,15); print(bps); print("b/s");
        setTextColor(BLACK); setCursor(30,39); print("Save");
      }
      break;
  }
  display();
}

void LCD::subMenu24(uint8_t channel, uint8_t pa, uint8_t ra, uint8_t ack, uint8_t delay, uint8_t count, uint8_t cr, int pos, boolean sel) {
  
  if(pos > 7) pos = 7;
  if(pos == 0) return void();
  
  clearDisplay();
  window("2.4GHz");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  char* palvl = "";
  char* rate = "";
  char* autoack = "";
  char* crc = "";
  
  switch(pa) {
    case 0: palvl = "MIN";
      break;
    case 1: palvl = "LOW";
      break;
    case 2: palvl = "HIGH";
      break;
    case 3: palvl = "MAX";
      break;
    case 4: palvl = "ERR";
      break;
  }
  switch(ra) {
    case 0: rate = "1MBPS";
      break;
    case 1: rate = "2MBPS";
      break;
    case 2: rate = "250KB";
      break;
  }
  switch(ack) {
    case 0: autoack = "OFF";
      break;
    case 1: autoack = "ON";
      break;
  }
  switch(cr) {
    case 0: crc = "OFF";
      break;
    case 1: crc = "8b";
      break;
    case 2: crc = "16b";
      break;
  }

  if(pos < 4) {
    
    if(pos == 1){if(!sel){ fillRect(2,10,49,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("Channel:"); setTextColor(BLACK); setCursor(52,11); print(channel); }else{ fillRect(51,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("Channel:"); setTextColor(WHITE); setCursor(52,11); print(channel); }}else{ setTextColor(BLACK); setCursor(3,11); print("Channel:"); setCursor(52,11); print(channel); }
    if(pos == 2){if(!sel){ fillRect(2,19,37,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("PALvl:");   setTextColor(BLACK); setCursor(52,20); print(palvl);   }else{ fillRect(51,19,25,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("PALvl:");   setTextColor(WHITE); setCursor(52,20); print(palvl);   }}else{ setTextColor(BLACK); setCursor(3,20); print("PALvl:");   setCursor(52,20); print(palvl); }
    if(pos == 3){if(!sel){ fillRect(2,28,31,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("Rate:");    setTextColor(BLACK); setCursor(52,29); print(rate);    }else{ fillRect(51,28,31,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("Rate:");    setTextColor(WHITE); setCursor(52,29); print(rate);    }}else{ setTextColor(BLACK); setCursor(3,29); print("Rate:");    setCursor(52,29); print(rate); }
  
  } else if(pos < 7) {
    
    if(pos == 4){if(!sel){ fillRect(2,10,49,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("AutoACK:"); setTextColor(BLACK); setCursor(52,11); print(autoack); }else{ fillRect(51,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("AutoACK:"); setTextColor(WHITE); setCursor(52,11); print(autoack); }}else{ setTextColor(BLACK); setCursor(3,11); print("AutoACK:"); setCursor(52,11); print(autoack); }
    if(pos == 5){if(!sel){ fillRect(2,19,37,9,BLACK); setTextColor(WHITE); setCursor(3,20); print("Delay:");   setTextColor(BLACK); setCursor(52,20); print(delay);   }else{ fillRect(51,19,19,9,BLACK); setTextColor(BLACK); setCursor(3,20); print("Delay:");   setTextColor(WHITE); setCursor(52,20); print(delay);   }}else{ setTextColor(BLACK); setCursor(3,20); print("Delay:");   setCursor(52,20); print(delay); }
    if(pos == 6){if(!sel){ fillRect(2,28,37,9,BLACK); setTextColor(WHITE); setCursor(3,29); print("Count:");   setTextColor(BLACK); setCursor(52,29); print(count);    }else{ fillRect(51,28,19,9,BLACK); setTextColor(BLACK); setCursor(3,29); print("Count:");   setTextColor(WHITE); setCursor(52,29); print(count);  }}else{ setTextColor(BLACK); setCursor(3,29); print("Count:");   setCursor(52,29); print(count); }
  
  } else {
    
    if(pos == 7){if(!sel){ fillRect(2,10,25,9,BLACK); setTextColor(WHITE); setCursor(3,11); print("CRC:"); setTextColor(BLACK); setCursor(52,11); print(crc); }else{ fillRect(51,10,19,9,BLACK); setTextColor(BLACK); setCursor(3,11); print("CRC:"); setTextColor(WHITE); setCursor(52,11); print(crc); }}else{ setTextColor(BLACK); setCursor(3,11); print("CRC:"); setCursor(52,11); print(crc); }
  }
  display();
}

void LCD::subMenuSystem(int pos, boolean sel) {
  
  if(pos > 1) pos = 1;
  if(pos == 0) return void();
  
  clearDisplay();
  window("System");
  setTextSize(1);
  setTextColor(BLACK);
  
  if(sel) {
    setCursor(30,39); print("Save");
  } else {
    setCursor(24,39); print("Select");
  }
  
  /*
  delay(2000);
  timer.attach(1, 200, Switch);
  debug ON / OFF
  */
  
  display();
}
