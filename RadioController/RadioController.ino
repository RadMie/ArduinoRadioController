/*
██████╗  █████╗ ██████╗ ██╗ ██████╗      ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  ██████╗ ██╗     ██╗     ███████╗██████╗
██╔══██╗██╔══██╗██╔══██╗██║██╔═══██╗    ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗██║     ██║     ██╔════╝██╔══██╗
██████╔╝███████║██║  ██║██║██║   ██║    ██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝██║   ██║██║     ██║     █████╗  ██████╔╝
██╔══██╗██╔══██║██║  ██║██║██║   ██║    ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██║   ██║██║     ██║     ██╔══╝  ██╔══██╗
██║  ██║██║  ██║██████╔╝██║╚██████╔╝    ╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║╚██████╔╝███████╗███████╗███████╗██║  ██║
╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝ ╚═════╝      ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝
*/
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <VirtualWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <KalmanFilter.h>
#include <MPU6050.h>
#include "RF24.h"
#include "Timers.h"
#include "key.h"
#include "lcd.h"
#include "memory.h"
#include "analog.h"
#include "buzzer.h"
#include "rf433.h"
#include "nrf24.h"
#include "printf.h"

#define DEBUG

char* git = "MPU-6050";
char* ver = "0.0.1";
char* date = "28.05.15";

Timers<10> timer;          // 10 x diff timer

Key KeyMenu = Key(4);
Key KeySel = Key(3);
Key KeyPlus = Key(5);
Key KeyMinus = Key(2);
Key KeySwA = Key(30);
Key KeySwA1 = Key(34);
Key KeySwB = Key(32);
Key KeySwB1 = Key(36);
Key KeyTrimLYup = Key(22);
Key KeyTrimLYdown = Key(24);
Key KeyTrimLXleft = Key(37);
Key KeyTrimLXright = Key(38);
Key KeyTrimRYup = Key(28);
Key KeyTrimRYdown = Key(26);
Key KeyTrimRXleft = Key(40);
Key KeyTrimRXright = Key(42);

Analog AnalogVRA = Analog(1);
Analog AnalogVRB = Analog(0);
Analog AnalogRY = Analog(2);
Analog AnalogLY = Analog(3);
Analog AnalogLX = Analog(4);
Analog AnalogRX = Analog(5);
Analog AnalogBattery = Analog(6);

Buzzer Buzz = Buzzer(8);

LCD display = LCD(48, 46, 44, 9);                 // only Hardware SPI PIN(DC,CS,RST,Backlight)

RF433 Transmission433 = RF433(12, 11, 10, true);  // (tx,rx,ptt,inv)

NRF24 TransmissionNRF24 = NRF24(6,7);             // only Hardware SPI PIN(ce,cs)

MPU6050 mpu;

KalmanFilter kalmanX(0.001, 0.003, 0.03);
KalmanFilter kalmanY(0.001, 0.003, 0.03);

Memory MemoryLcdContrast = Memory(0);
Memory MemoryLcdBacklight = Memory(1);
Memory MemoryTrimPrecision = Memory(2);
Memory MemoryBatteryWarning = Memory(3);
Memory MemoryBuzzerVolume = Memory(4);
Memory MemoryBuzzerMode = Memory(5);
Memory MemoryModelSel = Memory(6);
Memory MemoryControlTX = Memory(7);
Memory MemoryControl433 = Memory(8);
Memory MemoryControl24 = Memory(9);
Memory MemoryBatteryLevel0 = Memory(10);
Memory MemoryBatteryLevel1 = Memory(11);
Memory MemoryBatteryLevel2 = Memory(12);
Memory MemoryBatteryLevel3 = Memory(13);
Memory MemoryBatteryLevel4 = Memory(14);
Memory MemorySpeed433 = Memory(15,16);
Memory MemoryChannel24 = Memory(17);
Memory MemoryPAlvl24 = Memory(18);
Memory MemoryRate24 = Memory(19);
Memory MemoryAutoAck24 = Memory(20);
Memory MemoryDelay24 = Memory(21);
Memory MemoryCount24 = Memory(22);
Memory MemoryCRC24 = Memory(23);
Memory MemoryChannelConfigLX = Memory(24);
Memory MemoryChannelConfigLY = Memory(25);
Memory MemoryChannelConfigRX = Memory(26);
Memory MemoryChannelConfigRY = Memory(27);
Memory MemoryChannelConfigVRA = Memory(28);
Memory MemoryChannelConfigVRB = Memory(29);
Memory MemoryChannelConfigSWA = Memory(30);
Memory MemoryChannelConfigSWA1 = Memory(31);
Memory MemoryChannelConfigSWB = Memory(32);
Memory MemoryChannelConfigSWB1 = Memory(33);
Memory MemoryLcdFreq = Memory(34);
Memory MemoryBatteryFreq = Memory(35);

Memory MemoryCalibrationRYmin = Memory(100,101);
Memory MemoryCalibrationRYmax = Memory(102,103);
Memory MemoryCalibrationLYmin = Memory(104,105);
Memory MemoryCalibrationLYmax = Memory(106,107);
Memory MemoryCalibrationLXmin = Memory(108,109);
Memory MemoryCalibrationLXmax = Memory(110,111);
Memory MemoryCalibrationRXmin = Memory(112,113);
Memory MemoryCalibrationRXmax = Memory(114,115);

Memory MemoryLimitVRA = Memory(200);
Memory MemoryLimitVRB = Memory(202);
Memory MemoryLimitRY = Memory(204);
Memory MemoryLimitLY = Memory(206);
Memory MemoryLimitLX = Memory(208);
Memory MemoryLimitRX = Memory(210);

Memory MemoryTrimRY = Memory(301);
Memory MemoryTrimLY = Memory(302);
Memory MemoryTrimLX = Memory(303);
Memory MemoryTrimRX = Memory(304);

typedef enum { LCD = 1, CALIBRATION, TRIMMED, SOUND, BATTERY, TRANSMISSION, LIMITS, MIXER, MODEL, VERSION, T433, T24, SYSTEM };
typedef enum { LXMIN = 1, LXMAX, LYMIN, LYMAX, RXMIN, RXMAX, RYMIN, RYMAX };
typedef enum { OFF = 1, NOR, INV, LX, LY, RX, RY, VRA, VRB };

uint8_t mainLX = 0;
uint8_t mainLY = 0;
uint8_t mainRX = 0;
uint8_t mainRY = 0;
uint8_t mainVRA = 0;
uint8_t mainVRB = 0;
uint8_t keySwitch = 0;

float bat = 0;
float rateNRF24 = 0;
float rate433 = 0;
uint8_t rateLCD = 0;
uint16_t cCount = 0;
uint16_t cps = 0;
uint8_t bat_lvl = 0;
int navPanel = 0;          // 0,1,2,3... lvl panel
int navMenu = 0;           // 0 - off , 1,2,3... lvl menu
int navSubMenu = 0;        // 0 - off , 1,2,3... lvl submenu
boolean navSubMenuSel = 0; // 0 - off, 1 - on

float accPitch = 0;
float accRoll = 0;

float kalPitch = 0;
float kalRoll = 0;

void setup()   {

#if defined(DEBUG)
  Serial.begin(115200);
#endif
  printf_begin();
  display.init(MemoryLcdContrast.value, MemoryLcdBacklight.value);

  display.startPanel();
  delay(2000);
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
  
  mpu.calibrateGyro();

  timer.attach(0, 200, Switch);
  timer.attach(1, 1000, calcRate);
  timer.attach(2, (1000 / MemoryBatteryFreq.value), Battery);
  timer.attach(3, (1000 / MemoryLcdFreq.value), Display);

  Transmission433.init(MemorySpeed433.value16bit);
  TransmissionNRF24.init(MemoryChannel24.value, MemoryPAlvl24.value, MemoryRate24.value, MemoryAutoAck24.value, MemoryDelay24.value, MemoryCount24.value, MemoryCRC24.value);
}

void loop() {
  
  Navigation();
  Trimmed();
  timer.process();
  AnalogProcess();
  TransmissionProcess();
  Buzz.process();

#if defined(DEBUG)
  /*Serial.print("LX:"); Serial.print(mainLX); 
  Serial.print(",LY:"); Serial.print(mainLY); 
  Serial.print(",RX:"); Serial.print(mainRX); 
  Serial.print(",RY:"); Serial.print(mainRY); 
  Serial.print(",VRA:"); Serial.print(mainVRA);
  Serial.print(",VRB:"); Serial.print(mainVRB);
  Serial.print(",KEY:"); Serial.println(keySwitch);
  Serial.print("navPanel:"); Serial.print(navPanel); 
  Serial.print(" navMenu:"); Serial.print(navMenu); 
  Serial.print(" navSubMenu:"); Serial.print(navSubMenu);
  Serial.print(" navSubMenuSel:"); Serial.println(navSubMenuSel);*/
  Vector acc = mpu.readNormalizeAccel();
  Vector gyr = mpu.readNormalizeGyro();

  // Calculate Pitch & Roll from accelerometer (deg)
  accPitch = -(atan2(acc.XAxis, sqrt(acc.YAxis*acc.YAxis + acc.ZAxis*acc.ZAxis))*180.0)/M_PI;
  accRoll  = (atan2(acc.YAxis, acc.ZAxis)*180.0)/M_PI;

  // Kalman filter
  kalPitch = kalmanY.update(accPitch, gyr.YAxis);
  kalRoll = kalmanX.update(accRoll, gyr.XAxis);

  Serial.print(accPitch);
  Serial.print(":");
  Serial.print(accRoll);
  Serial.print(":");
  Serial.print(kalPitch);
  Serial.print(":");
  Serial.print(kalRoll);
  Serial.print(":");
  Serial.print(acc.XAxis);
  Serial.print(":");
  Serial.print(acc.YAxis);
  Serial.print(":");
  Serial.print(acc.ZAxis);
  Serial.print(":");
  Serial.print(gyr.XAxis);
  Serial.print(":");
  Serial.print(gyr.YAxis);
  Serial.print(":");
  Serial.print(gyr.ZAxis);

  Serial.println();
#endif
  cCount++;
}

void AnalogProcess() {
  
  if(MemoryChannelConfigLX.value == OFF) {
    mainLX = 128;
  } else if(MemoryChannelConfigLX.value == NOR) {
    mainLX = map(AnalogLX.read8BIT(MemoryCalibrationLXmin.value16bit, MemoryCalibrationLXmax.value16bit), 0, 255, 127 - MemoryLimitLX.value, 128 + MemoryLimitLX.value);
    mainLX = max(min(mainLX + map(MemoryTrimLX.value,0,255,-128,+128),255),0);
  } else if(MemoryChannelConfigLX.value == INV) {
  } else if(MemoryChannelConfigLX.value == LX) {
  } else if(MemoryChannelConfigLX.value == LY) {
  } else if(MemoryChannelConfigLX.value == RX) {
  } else if(MemoryChannelConfigLX.value == RY) {
  } else if(MemoryChannelConfigLX.value == VRA) {
  } else if(MemoryChannelConfigLX.value == VRB) {
  }
    
  if(MemoryChannelConfigLY.value == OFF) {
    mainLY = 128;
  } else if(MemoryChannelConfigLY.value == NOR) {
    mainLY = map(AnalogLY.read8BIT(MemoryCalibrationLYmin.value16bit, MemoryCalibrationLYmax.value16bit), 0, 255, 127 - MemoryLimitLY.value, 128 + MemoryLimitLY.value);
    mainLY = max(min(mainLY + map(MemoryTrimLY.value,0,255,-128,+128),255),0);
  } else if(MemoryChannelConfigLY.value == INV) {
  } else if(MemoryChannelConfigLY.value == LX) {
  } else if(MemoryChannelConfigLY.value == LY) {
  } else if(MemoryChannelConfigLY.value == RX) {
  } else if(MemoryChannelConfigLY.value == RY) {
  } else if(MemoryChannelConfigLY.value == VRA) {
  } else if(MemoryChannelConfigLY.value == VRB) {
  }
  if(MemoryChannelConfigRX.value == OFF) {
    mainRX = 128;
  } else if(MemoryChannelConfigRX.value == NOR) {
    mainRX = map(AnalogRX.read8BIT(MemoryCalibrationRXmin.value16bit, MemoryCalibrationRXmax.value16bit), 0, 255, 127 - MemoryLimitRX.value, 128 + MemoryLimitRX.value);
    mainRX = max(min(mainRX + map(MemoryTrimRX.value,0,255,-128,+128),255),0);
  } else if(MemoryChannelConfigRX.value == INV) { 
  } else if(MemoryChannelConfigRX.value == LX) {
  } else if(MemoryChannelConfigRX.value == LY) {
  } else if(MemoryChannelConfigRX.value == RX) {
  } else if(MemoryChannelConfigRX.value == RY) {
  } else if(MemoryChannelConfigRX.value == VRA) {
  } else if(MemoryChannelConfigRX.value == VRB) {
  }
  if(MemoryChannelConfigRY.value == OFF) {
    mainRY = 128;
  } else if(MemoryChannelConfigRY.value == NOR) {
     mainRY = map(AnalogRY.read8BIT(MemoryCalibrationRYmin.value16bit, MemoryCalibrationRYmax.value16bit), 0, 255, 127 - MemoryLimitRY.value, 128 + MemoryLimitRY.value);
     mainRY = max(min(mainRY + map(MemoryTrimRY.value,0,255,-128,+128),255),0);
  } else if(MemoryChannelConfigRY.value == INV) {
  } else if(MemoryChannelConfigRY.value == LX) {
  } else if(MemoryChannelConfigRY.value == LY) {
  } else if(MemoryChannelConfigRY.value == RX) {
  } else if(MemoryChannelConfigRY.value == RY) {
  } else if(MemoryChannelConfigRY.value == VRA) {
  } else if(MemoryChannelConfigRY.value == VRB) {
  }
  if(MemoryChannelConfigVRA.value == OFF) {
    mainVRA = 128;
  } else if(MemoryChannelConfigVRA.value == NOR) {
    mainVRA = map(AnalogVRA.read8BIT(), 0, 255, 127 - MemoryLimitVRA.value, 128 + MemoryLimitVRA.value);
  } else if(MemoryChannelConfigVRA.value == INV) {
  } else if(MemoryChannelConfigVRA.value == LX) {
  } else if(MemoryChannelConfigVRA.value == LY) {
  } else if(MemoryChannelConfigVRA.value == RX) {
  } else if(MemoryChannelConfigVRA.value == RY) {
  } else if(MemoryChannelConfigVRA.value == VRA) {
  } else if(MemoryChannelConfigVRA.value == VRB) {
  }
  if(MemoryChannelConfigVRB.value == OFF) {
    mainVRB = 128;
  } else if(MemoryChannelConfigVRB.value == NOR) {
    mainVRB = map(AnalogVRB.read8BIT(), 0, 255, 127 - MemoryLimitVRB.value, 128 + MemoryLimitVRB.value);
  } else if(MemoryChannelConfigVRB.value == INV) {
  } else if(MemoryChannelConfigVRB.value == LX) {
  } else if(MemoryChannelConfigVRB.value == LY) {
  } else if(MemoryChannelConfigVRB.value == RX) {
  } else if(MemoryChannelConfigVRB.value == RY) {
  } else if(MemoryChannelConfigVRB.value == VRA) {
  } else if(MemoryChannelConfigVRB.value == VRB) {
  }  
}

void Battery() {
  
  bat = AnalogBattery.readVoltage();
  if(bat < (MemoryBatteryLevel0.value / 10.0)) {
    bat_lvl = 0;
  } else if(bat < (MemoryBatteryLevel1.value / 10.0)) {
    bat_lvl = 1;
  } else if(bat < (MemoryBatteryLevel2.value / 10.0)) {
    bat_lvl = 2;
  } else if(bat < (MemoryBatteryLevel3.value / 10.0)) {
    bat_lvl = 3;
  } else if(bat < (MemoryBatteryLevel4.value / 10.0)) {
    bat_lvl = 4; 
  } 
}

void TransmissionProcess() {
  
  if(MemoryControlTX.value) {
    if(MemoryControl433.value) {
      Transmission433.sendData(mainLX, mainLY, mainRX, mainRY, mainVRA, mainVRB, keySwitch);
    }
    if(MemoryControl24.value) {
      TransmissionNRF24.sendData(mainLX, mainLY, mainRX, mainRY, mainVRA, mainVRB, keySwitch);
    }  
  }
}

void calcRate() {
  
  rateNRF24 = TransmissionNRF24.transferCounter;  // B/s
  rate433 = Transmission433.transferCounter;      // B/s
  TransmissionNRF24.transferCounter = 0;
  Transmission433.transferCounter = 0;
  rateLCD = display.freqCount;
  display.freqCount = 0;
  cps = cCount;
  cCount = 0;
}

void Navigation() {
  
  if(KeyMenu.pressed()) {
    if(KeyMenu.status) {
      pressMenu();
      if(MemoryBuzzerMode.value == 1) Buzz.on(MemoryBuzzerVolume.value);
      KeyMenu.status = 0;
    }
  } else KeyMenu.status = 1;
  if(KeySel.pressed()) {
    if(KeySel.status) {
      pressSel();
      if(MemoryBuzzerMode.value == 1) Buzz.on(MemoryBuzzerVolume.value);
      KeySel.status = 0;
    }
  } else KeySel.status = 1;
  if(KeyPlus.pressed()) {
    if(KeyPlus.status) {
      pressPlus();
      if(MemoryBuzzerMode.value == 1) Buzz.on(MemoryBuzzerVolume.value);
      KeyPlus.status = 0;
    }
  } else KeyPlus.status = 1;
  if(KeyMinus.pressed()) {
    if(KeyMinus.status) {
      pressMinus();
      if(MemoryBuzzerMode.value == 1) Buzz.on(MemoryBuzzerVolume.value);
      KeyMinus.status = 0;
    }
  } else KeyMinus.status = 1;
}

void pressMenu() {
  if(navSubMenuSel) {
    navSubMenuSel = 0;
  } else if(navSubMenu) {
    navSubMenu = 0;
  } else if(navMenu) {
    navMenu = 0;
  } else {
    navMenu = 1;
  }
}
void pressSel() {
  if(navSubMenuSel) {
    switch(navMenu) {
      case LCD:
        if(navSubMenu == 1) {
          MemoryLcdBacklight.write8bit();
        } else if(navSubMenu == 2) {
          MemoryLcdContrast.write8bit();
        } else if(navSubMenu == 3) {
          MemoryLcdFreq.write8bit();
          timer.attach(3, (1000 / MemoryLcdFreq.value), Display);
        }
        break;
      case CALIBRATION:
        if(navSubMenu == LXMIN) {
          MemoryCalibrationLXmin.value16bit = AnalogLX.raw;
          MemoryCalibrationLXmin.write16bit();
        } else if(navSubMenu == LXMAX) {
          MemoryCalibrationLXmax.value16bit = AnalogLX.raw;
          MemoryCalibrationLXmax.write16bit();
        } else if(navSubMenu == LYMIN) {
          MemoryCalibrationLYmin.value16bit = AnalogLY.raw;
          MemoryCalibrationLYmin.write16bit();
        } else if(navSubMenu == LYMAX) {
          MemoryCalibrationLYmax.value16bit = AnalogLY.raw;
          MemoryCalibrationLYmax.write16bit();
        } else if(navSubMenu == RXMIN) {
          MemoryCalibrationRXmin.value16bit = AnalogRX.raw;
          MemoryCalibrationRXmin.write16bit();
        } else if(navSubMenu == RXMAX) {
          MemoryCalibrationRXmax.value16bit = AnalogRX.raw;
          MemoryCalibrationRXmax.write16bit();
        } else if(navSubMenu == RYMIN) {
          MemoryCalibrationRYmin.value16bit = AnalogRY.raw;
          MemoryCalibrationRYmin.write16bit();
        } else if(navSubMenu == RYMAX) {
          MemoryCalibrationRYmax.value16bit = AnalogRY.raw;
          MemoryCalibrationRYmax.write16bit();
        }
        break;
      case TRIMMED:
        if(navSubMenu == 1) {
          MemoryTrimPrecision.write8bit();  
        }
        break;
      case SOUND:
        if(navSubMenu == 1) {
          MemoryBuzzerMode.write8bit();
        } else if(navSubMenu == 2) {
          MemoryBuzzerVolume.write8bit();
        }
        break;
      case BATTERY:
        if(navSubMenu == 1) {
          MemoryBatteryWarning.write8bit();
        } else if(navSubMenu == 2) {
          MemoryBatteryLevel0.write8bit();
        } else if(navSubMenu == 3) {
          MemoryBatteryLevel1.write8bit();
        } else if(navSubMenu == 4) {
          MemoryBatteryLevel2.write8bit();
        } else if(navSubMenu == 5) {
          MemoryBatteryLevel3.write8bit();
        } else if(navSubMenu == 6) {
          MemoryBatteryLevel4.write8bit();
        } else if(navSubMenu == 7) {
          MemoryBatteryFreq.write8bit();
          timer.attach(2, (1000 / MemoryBatteryFreq.value), Battery);
        }
        break;
      case TRANSMISSION:
        if(navSubMenu == 1) {
          MemoryControlTX.write8bit();
        } else if(navSubMenu == 2) {
          MemoryControl433.write8bit();
        } else if(navSubMenu == 3) {
          MemoryControl24.write8bit();
        }
        break;
      case LIMITS:
        if(navSubMenu == 1) {
          MemoryLimitLX.write8bit();
        } else if(navSubMenu == 2) {
          MemoryLimitLY.write8bit();
        } else if(navSubMenu == 3) {
          MemoryLimitRX.write8bit();
        } else if(navSubMenu == 4) {
          MemoryLimitRY.write8bit();
        } else if(navSubMenu == 5) {
          MemoryLimitVRA.write8bit();
        } else if(navSubMenu == 6) {
          MemoryLimitVRB.write8bit();
        }
        break;
      case MIXER:
        if(navSubMenu == 1) {
          MemoryChannelConfigLX.write8bit();
        } else if(navSubMenu == 2) {
          MemoryChannelConfigLY.write8bit();
        } else if(navSubMenu == 3) {
          MemoryChannelConfigRX.write8bit();
        } else if(navSubMenu == 4) {
          MemoryChannelConfigRY.write8bit();
        } else if(navSubMenu == 5) {
          MemoryChannelConfigVRA.write8bit();
        } else if(navSubMenu == 6) {
          MemoryChannelConfigVRB.write8bit();
        } else if(navSubMenu == 7) {
          MemoryChannelConfigSWA.write8bit();
        } else if(navSubMenu == 8) {
          MemoryChannelConfigSWA1.write8bit();
        } else if(navSubMenu == 9) {
          MemoryChannelConfigSWB.write8bit();
        } else if(navSubMenu == 10) {
          MemoryChannelConfigSWB1.write8bit();
        }
        break;
      case MODEL:
        if(navSubMenu == 1) {
          MemoryModelSel.write8bit();  
        }
        break;
      case VERSION:
        break;
      case T433:
        if(navSubMenu == 1) {
          MemorySpeed433.write16bit();
          uint8_t temp433 = MemoryControl433.value;
          MemoryControl433.value = 0;
          Transmission433.init(MemorySpeed433.value16bit);
          MemoryControl433.value = temp433;
        }
        break;
      case T24:
      {
        if(navSubMenu == 1) {
          MemoryChannel24.write8bit();
        } else if(navSubMenu == 2) {
          MemoryPAlvl24.write8bit();
        } else if(navSubMenu == 3) {
          MemoryRate24.write8bit();
        } else if(navSubMenu == 4) {
          MemoryAutoAck24.write8bit();
        } else if(navSubMenu == 5) {
          MemoryDelay24.write8bit();
        } else if(navSubMenu == 6) {
          MemoryCount24.write8bit();
        } else if(navSubMenu == 7) {
          MemoryCRC24.write8bit();
        }
        uint8_t temp24 = MemoryControl24.value;
        MemoryControl24.value = 0;
        TransmissionNRF24.init(MemoryChannel24.value, MemoryPAlvl24.value, MemoryRate24.value, MemoryAutoAck24.value, MemoryDelay24.value, MemoryCount24.value, MemoryCRC24.value);
        MemoryControl24.value = temp24;
      }
        break;
      case SYSTEM:
        break;
    }
    navSubMenuSel = 0;
  } else if(navSubMenu) {
    navSubMenuSel = 1;
  } else if(navMenu) {
    navSubMenu = 1;
  } else {
    navPanel++; if(navPanel > 5) navPanel = 0;
  }
}
void pressPlus() {
  if(navSubMenuSel) {
    switch(navMenu) {
      case LCD:
        if(navSubMenu == 1) {
          MemoryLcdBacklight.value+=2;
          if(MemoryLcdBacklight.value > 253) MemoryLcdBacklight.value = 253;
          display.setBacklight(MemoryLcdBacklight.value);
        } else if(navSubMenu == 2) {
          MemoryLcdContrast.value++;
          if(MemoryLcdContrast.value > 126) MemoryLcdContrast.value = 126;
          display.setContrast(MemoryLcdContrast.value);
        } else if(navSubMenu == 3) {
          MemoryLcdFreq.value++;
          if(MemoryLcdFreq.value > 99) MemoryLcdFreq.value = 99;
        }
        break;
      case CALIBRATION:
        break;
      case TRIMMED:
        if(navSubMenu == 1) {
          MemoryTrimPrecision.value++; 
          if(MemoryTrimPrecision.value > 9) MemoryTrimPrecision.value = 9;
        }
        break;
      case SOUND:
        if(navSubMenu == 1) {
          MemoryBuzzerMode.value++;
          if(MemoryBuzzerMode.value > 2) MemoryBuzzerMode.value = 2;
        } else if(navSubMenu == 2) {
          MemoryBuzzerVolume.value+=2;
          if(MemoryBuzzerVolume.value > 253) MemoryBuzzerVolume.value = 253;
        }
        break;
      case BATTERY:
        if(navSubMenu == 1) {
          MemoryBatteryWarning.value++;
          if(MemoryBatteryWarning.value > 200) MemoryBatteryWarning.value = 200;
        } else if(navSubMenu == 2) {
          MemoryBatteryLevel0.value++;
          if(MemoryBatteryLevel0.value > 200) MemoryBatteryLevel0.value = 200;
        } else if(navSubMenu == 3) {
          MemoryBatteryLevel1.value++;
          if(MemoryBatteryLevel1.value > 200) MemoryBatteryLevel1.value = 200;
        } else if(navSubMenu == 4) {
          MemoryBatteryLevel2.value++;
          if(MemoryBatteryLevel2.value > 200) MemoryBatteryLevel2.value = 200;
        } else if(navSubMenu == 5) {
          MemoryBatteryLevel3.value++;
          if(MemoryBatteryLevel3.value > 200) MemoryBatteryLevel3.value = 200;
        } else if(navSubMenu == 6) {
          MemoryBatteryLevel4.value++;
          if(MemoryBatteryLevel4.value > 200) MemoryBatteryLevel4.value = 200;
        } else if(navSubMenu == 7) {
          MemoryBatteryFreq.value++;
          if(MemoryBatteryFreq.value > 99) MemoryBatteryFreq.value = 99;
        }
        break;
      case TRANSMISSION:
        if(navSubMenu == 1) {
          MemoryControlTX.value++;
          if(MemoryControlTX.value > 1) MemoryControlTX.value = 1;
        } else if(navSubMenu == 2) {
          MemoryControl433.value++;
          if(MemoryControl433.value > 1) MemoryControl433.value = 1;
        } else if(navSubMenu == 3) {
          MemoryControl24.value++;
          if(MemoryControl24.value > 1) MemoryControl24.value = 1;
        }
        break;
      case LIMITS:
        if(navSubMenu == 1) {
          MemoryLimitLX.value++;
          if(MemoryLimitLX.value > 127) MemoryLimitLX.value = 127;
        } else if(navSubMenu == 2) {
          MemoryLimitLY.value++;
          if(MemoryLimitLY.value > 127) MemoryLimitLY.value = 127;
        } else if(navSubMenu == 3) {
          MemoryLimitRX.value++;
          if(MemoryLimitRX.value > 127) MemoryLimitRX.value = 127;
        } else if(navSubMenu == 4) {
          MemoryLimitRY.value++;
          if(MemoryLimitRY.value > 127) MemoryLimitRY.value = 127;
        } else if(navSubMenu == 5) {
          MemoryLimitVRA.value++;
          if(MemoryLimitVRA.value > 127) MemoryLimitVRA.value = 127;
        } else if(navSubMenu == 6) {
          MemoryLimitVRB.value++;
          if(MemoryLimitVRB.value > 127) MemoryLimitVRB.value = 127;
        }
        break;
      case MIXER:
        if(navSubMenu == 1) {
          MemoryChannelConfigLX.value++;
          if(MemoryChannelConfigLX.value > 9) MemoryChannelConfigLX.value = 9;
        } else if(navSubMenu == 2) {
          MemoryChannelConfigLY.value++;
          if(MemoryChannelConfigLY.value > 9) MemoryChannelConfigLY.value = 9;
        } else if(navSubMenu == 3) {
          MemoryChannelConfigRX.value++;
          if(MemoryChannelConfigRX.value > 9) MemoryChannelConfigRX.value = 9;
        } else if(navSubMenu == 4) {
          MemoryChannelConfigRY.value++;
          if(MemoryChannelConfigRY.value > 9) MemoryChannelConfigRY.value = 9;
        } else if(navSubMenu == 5) {
          MemoryChannelConfigVRA.value++;
          if(MemoryChannelConfigVRA.value > 9) MemoryChannelConfigVRA.value = 9;
        } else if(navSubMenu == 6) {
          MemoryChannelConfigVRB.value++;
          if(MemoryChannelConfigVRB.value > 9) MemoryChannelConfigVRB.value = 9;
        } else if(navSubMenu == 7) {
          MemoryChannelConfigSWA.value++;
          if(MemoryChannelConfigSWA.value > 3) MemoryChannelConfigSWA.value = 3;
        } else if(navSubMenu == 8) {
          MemoryChannelConfigSWA1.value++;
          if(MemoryChannelConfigSWA1.value > 3) MemoryChannelConfigSWA1.value = 3;
        } else if(navSubMenu == 9) {
          MemoryChannelConfigSWB.value++;
          if(MemoryChannelConfigSWB.value > 3) MemoryChannelConfigSWB.value = 3;
        } else if(navSubMenu == 10) {
          MemoryChannelConfigSWB1.value++;
          if(MemoryChannelConfigSWB1.value > 3) MemoryChannelConfigSWB1.value = 3;
        }
        break;
      case MODEL:
        if(navSubMenu == 1) {
          MemoryModelSel.value++;
          if(MemoryModelSel.value > 2) MemoryModelSel.value = 2;
        }
        break;
      case VERSION:
        break;
      case T433:
        if(navSubMenu == 1) {
          MemorySpeed433.value16bit+=100;
          if(MemorySpeed433.value16bit > 9900) MemorySpeed433.value16bit = 9900;
        }
        break;
      case T24:
        if(navSubMenu == 1) {
          MemoryChannel24.value++;
          if(MemoryChannel24.value > 127) MemoryChannel24.value = 127;
        } else if(navSubMenu == 2) {
          MemoryPAlvl24.value++;
          if(MemoryPAlvl24.value > 4) MemoryPAlvl24.value = 4;
        } else if(navSubMenu == 3) {
          MemoryRate24.value++;
          if(MemoryRate24.value > 2) MemoryRate24.value = 2;
        } else if(navSubMenu == 4) {
          MemoryAutoAck24.value++;
          if(MemoryAutoAck24.value > 1) MemoryAutoAck24.value = 1;
        } else if(navSubMenu == 5) {
          MemoryDelay24.value++;
          if(MemoryDelay24.value > 254) MemoryDelay24.value = 254;
        } else if(navSubMenu == 6) {
          MemoryCount24.value++;
          if(MemoryCount24.value > 254) MemoryCount24.value = 254;
        } else if(navSubMenu == 7) {
          MemoryCRC24.value++;
          if(MemoryCRC24.value > 2) MemoryCRC24.value = 2;
        }
        break;
      case SYSTEM:
        break;
    }  
  } else if(navSubMenu) {
    navSubMenu--;
    if(navSubMenu < 1) navSubMenu = 1;
  } else if(navMenu) {
    navMenu--; if(navMenu < 1) navMenu = 1;
  } else {
    if(navPanel == 5) {
      if(MemoryLimitRX.value != MemoryLimitRY.value) MemoryLimitRX.value = MemoryLimitRY.value;
      MemoryLimitRX.value++;
      MemoryLimitRY.value++;
      if(MemoryLimitRY.value > 127) {
        MemoryLimitRY.value = 127;
        MemoryLimitRX.value = 127;
      }
    } 
  }
}
void pressMinus() {
  if(navSubMenuSel) {
    switch(navMenu) {
      case LCD:
        if(navSubMenu == 1) {
          MemoryLcdBacklight.value-=2;
          if(MemoryLcdBacklight.value < 1 || MemoryLcdBacklight.value == 255) MemoryLcdBacklight.value = 1;
          display.setBacklight(MemoryLcdBacklight.value);
        } else if(navSubMenu == 2) {
          MemoryLcdContrast.value--;
          if(MemoryLcdContrast.value < 1) MemoryLcdContrast.value = 1;
          display.setContrast(MemoryLcdContrast.value);
        } else if(navSubMenu == 3) {
          MemoryLcdFreq.value--;
          if(MemoryLcdFreq.value < 1) MemoryLcdFreq.value = 1;
        }
        break;
      case CALIBRATION:
        break;
      case TRIMMED:
        if(navSubMenu == 1) {
          MemoryTrimPrecision.value--; 
          if(MemoryTrimPrecision.value < 1) MemoryTrimPrecision.value = 1;
        }
        break;
      case SOUND:
        if(navSubMenu == 1) {
          MemoryBuzzerMode.value--;
          if(MemoryBuzzerMode.value < 1) MemoryBuzzerMode.value = 1;
        } else if(navSubMenu == 2) {
          MemoryBuzzerVolume.value-=2;
          if(MemoryBuzzerVolume.value < 1 || MemoryBuzzerVolume.value == 255) MemoryBuzzerVolume.value = 1;
        }
        break;
      case BATTERY:
        if(navSubMenu == 1) {
          MemoryBatteryWarning.value--;
          if(MemoryBatteryWarning.value < 1) MemoryBatteryWarning.value = 1;
        } else if(navSubMenu == 2) {
          MemoryBatteryLevel0.value--;
          if(MemoryBatteryLevel0.value < 1) MemoryBatteryLevel0.value = 1;
        } else if(navSubMenu == 3) {
          MemoryBatteryLevel1.value--;
          if(MemoryBatteryLevel1.value < 1) MemoryBatteryLevel1.value = 1;
        } else if(navSubMenu == 4) {
          MemoryBatteryLevel2.value--;
          if(MemoryBatteryLevel2.value < 1) MemoryBatteryLevel2.value = 1;
        } else if(navSubMenu == 5) {
          MemoryBatteryLevel3.value--;
          if(MemoryBatteryLevel3.value < 1) MemoryBatteryLevel3.value = 1;
        } else if(navSubMenu == 6) {
          MemoryBatteryLevel4.value--;
          if(MemoryBatteryLevel4.value < 1) MemoryBatteryLevel4.value = 1;
        } else if(navSubMenu == 7) {
          MemoryBatteryFreq.value--;
          if(MemoryBatteryFreq.value < 1) MemoryBatteryFreq.value = 1;
        }
        break;
      case TRANSMISSION:
        if(navSubMenu == 1) {
          MemoryControlTX.value--;
          if(MemoryControlTX.value == 255) MemoryControlTX.value = 0;
        } else if(navSubMenu == 2) {
          MemoryControl433.value--;
          if(MemoryControl433.value == 255) MemoryControl433.value = 0;
        } else if(navSubMenu == 3) {
          MemoryControl24.value--;
          if(MemoryControl24.value == 255) MemoryControl24.value = 0;
        }
        break;
      case LIMITS:
        if(navSubMenu == 1) {
          MemoryLimitLX.value--;
          if(MemoryLimitLX.value < 10) MemoryLimitLX.value = 10;
        } else if(navSubMenu == 2) {
          MemoryLimitLY.value--;
          if(MemoryLimitLY.value < 10) MemoryLimitLY.value = 10;
        } else if(navSubMenu == 3) {
          MemoryLimitRX.value--;
          if(MemoryLimitRX.value < 10) MemoryLimitRX.value = 10;
        } else if(navSubMenu == 4) {
          MemoryLimitRY.value--;
          if(MemoryLimitRY.value < 10) MemoryLimitRY.value = 10;
        } else if(navSubMenu == 5) {
          MemoryLimitVRA.value--;
          if(MemoryLimitVRA.value < 10) MemoryLimitVRA.value = 10;
        } else if(navSubMenu == 6) {
          MemoryLimitVRB.value--;
          if(MemoryLimitVRB.value < 10) MemoryLimitVRB.value = 10;
        }
        break;
      case MIXER:
        if(navSubMenu == 1) {
          MemoryChannelConfigLX.value--;
          if(MemoryChannelConfigLX.value < 1) MemoryChannelConfigLX.value = 1;
        } else if(navSubMenu == 2) {
          MemoryChannelConfigLY.value--;
          if(MemoryChannelConfigLY.value < 1) MemoryChannelConfigLY.value = 1;
        } else if(navSubMenu == 3) {
          MemoryChannelConfigRX.value--;
          if(MemoryChannelConfigRX.value < 1) MemoryChannelConfigRX.value = 1;
        } else if(navSubMenu == 4) {
          MemoryChannelConfigRY.value--;
          if(MemoryChannelConfigRY.value < 1) MemoryChannelConfigRY.value = 1;
        } else if(navSubMenu == 5) {
          MemoryChannelConfigVRA.value--;
          if(MemoryChannelConfigVRA.value < 1) MemoryChannelConfigVRA.value = 1;
        } else if(navSubMenu == 6) {
          MemoryChannelConfigVRB.value--;
          if(MemoryChannelConfigVRB.value < 1) MemoryChannelConfigVRB.value = 1;
        } else if(navSubMenu == 7) {
          MemoryChannelConfigSWA.value--;
          if(MemoryChannelConfigSWA.value < 1) MemoryChannelConfigSWA.value = 1;
        } else if(navSubMenu == 8) {
          MemoryChannelConfigSWA1.value--;
          if(MemoryChannelConfigSWA1.value < 1) MemoryChannelConfigSWA1.value = 1;
        } else if(navSubMenu == 9) {
          MemoryChannelConfigSWB.value--;
          if(MemoryChannelConfigSWB.value < 1) MemoryChannelConfigSWB.value = 1;
        } else if(navSubMenu == 10) {
          MemoryChannelConfigSWB1.value--;
          if(MemoryChannelConfigSWB1.value < 1) MemoryChannelConfigSWB1.value = 1;
        }
        break;
      case MODEL:
        if(navSubMenu == 1) {
          MemoryModelSel.value--;
          if(MemoryModelSel.value < 1) MemoryModelSel.value = 1;
        }
        break;
      case VERSION:
        break;
      case T433:
        if(navSubMenu == 1) {
          MemorySpeed433.value16bit-=100;
          if(MemorySpeed433.value16bit < 200) MemorySpeed433.value16bit = 200;
        }
        break;
      case T24:
        if(navSubMenu == 1) {
          MemoryChannel24.value--;
          if(MemoryChannel24.value < 1) MemoryChannel24.value = 1;
        } else if(navSubMenu == 2) {
          MemoryPAlvl24.value--;
          if(MemoryPAlvl24.value == 255) MemoryPAlvl24.value = 0;
        } else if(navSubMenu == 3) {
          MemoryRate24.value--;
          if(MemoryRate24.value == 255) MemoryRate24.value = 0;
        } else if(navSubMenu == 4) {
          MemoryAutoAck24.value--;
          if(MemoryAutoAck24.value == 255) MemoryAutoAck24.value = 0;
        } else if(navSubMenu == 5) {
          MemoryDelay24.value--;
          if(MemoryDelay24.value == 255) MemoryDelay24.value = 0;
        } else if(navSubMenu == 6) {
          MemoryCount24.value--;
          if(MemoryCount24.value == 255) MemoryCount24.value = 0;
        } else if(navSubMenu == 7) {
          MemoryCRC24.value--;
          if(MemoryCRC24.value == 255) MemoryCRC24.value = 0;
        }
        break;
      case SYSTEM:
        break;
    }  
  } else if(navSubMenu) {
    navSubMenu++;
    switch(navMenu) {
      case LCD:
        if(navSubMenu > 3) navSubMenu = 3;
        break;
      case CALIBRATION:
        if(navSubMenu > 8) navSubMenu = 8;
        break;
      case TRIMMED:
        if(navSubMenu > 1) navSubMenu = 1;
        break;
      case SOUND:
        if(navSubMenu > 2) navSubMenu = 2;
        break;
      case BATTERY:
        if(navSubMenu > 7) navSubMenu = 7;
        break;
      case TRANSMISSION:
        if(navSubMenu > 3) navSubMenu = 3;
        break;
      case LIMITS:
        if(navSubMenu > 6) navSubMenu = 6;
        break;
      case MIXER:
        if(navSubMenu > 10) navSubMenu = 10;
        break;
      case MODEL:
        if(navSubMenu > 1) navSubMenu = 1;
        break;
      case VERSION:
        break;
      case T433:
        if(navSubMenu > 1) navSubMenu = 1;
        break;
      case T24:
        if(navSubMenu > 7) navSubMenu = 7;
        break;
      case SYSTEM:
        break;
    } 
  } else if(navMenu) {
    navMenu++; if(navMenu > 13) navMenu = 13;
  } else {
    if(navPanel == 5) {
      if(MemoryLimitRX.value != MemoryLimitRY.value) MemoryLimitRX.value = MemoryLimitRY.value;
      MemoryLimitRX.value--;
      MemoryLimitRY.value--;
      if(MemoryLimitRY.value < 10) {
        MemoryLimitRY.value = 10;
        MemoryLimitRX.value = 10;
      }
    } 
  }
}
void Trimmed() {
  
  if (KeyTrimLYup.pressed()) {
    if(KeyTrimLYup.status) {
      MemoryTrimLY.value += MemoryTrimPrecision.value;
      KeyTrimLYup.status = 0;
    }
  } else KeyTrimLYup.status = 1;
  if (KeyTrimLYdown.pressed()) {
    if(KeyTrimLYdown.status) {
      MemoryTrimLY.value -= MemoryTrimPrecision.value;
      KeyTrimLYdown.status = 0;
    }
  } else KeyTrimLYdown.status = 1;
  if (KeyTrimLXleft.pressed()) {
    if(KeyTrimLXleft.status) {
      MemoryTrimLX.value -= MemoryTrimPrecision.value;
      KeyTrimLXleft.status = 0;
    }
  } else KeyTrimLXleft.status = 1;
  if (KeyTrimLXright.pressed()) {
    if(KeyTrimLXright.status) {
      MemoryTrimLX.value += MemoryTrimPrecision.value;
      KeyTrimLXright.status = 0;
    }
  } else KeyTrimLXright.status = 1;
  if (KeyTrimRYup.pressed()) {
    if(KeyTrimRYup.status) {
      MemoryTrimRY.value += MemoryTrimPrecision.value;
      KeyTrimRYup.status = 0;
    }
  } else KeyTrimRYup.status = 1;
  if (KeyTrimRYdown.pressed()) {
    if(KeyTrimRYdown.status) {
      MemoryTrimRY.value -= MemoryTrimPrecision.value;
      KeyTrimRYdown.status = 0;
    }
  } else KeyTrimRYdown.status = 1;
  if (KeyTrimRXleft.pressed()) {
    if(KeyTrimRXleft.status) {
      MemoryTrimRX.value -= MemoryTrimPrecision.value;
      KeyTrimRXleft.status = 0;
    }
  } else KeyTrimRXleft.status = 1;
  if (KeyTrimRXright.pressed()) {
    if(KeyTrimRXright.status) {
      MemoryTrimRX.value += MemoryTrimPrecision.value;
      KeyTrimRXright.status = 0;
    }
  } else KeyTrimRXright.status = 1;
}

void Switch() {
  
  if(MemoryChannelConfigSWA.value == OFF) {
    bitClear(keySwitch, 0);
  } else if(MemoryChannelConfigSWA.value == NOR) {
    if (KeySwA.pressed()) {
      bitSet(keySwitch, 0);
    } else {
      bitClear(keySwitch, 0);
    }
  } else if(MemoryChannelConfigSWA.value == INV) {
    if (!KeySwA.pressed()) {
      bitSet(keySwitch, 0);
    } else {
      bitClear(keySwitch, 0);
    }
  }
  if(MemoryChannelConfigSWA1.value == OFF) {
    bitClear(keySwitch, 1);
  } else if(MemoryChannelConfigSWA1.value == NOR) {
    if (KeySwA1.pressed()) {
      bitSet(keySwitch, 1);
    } else {
      bitClear(keySwitch, 1); 
    }
  } else if(MemoryChannelConfigSWA1.value == INV) {
    if (!KeySwA1.pressed()) {
      bitSet(keySwitch, 1);
    } else {
      bitClear(keySwitch, 1); 
    }
  }
  if(MemoryChannelConfigSWB.value == OFF) {
    bitClear(keySwitch, 2);
  } else if(MemoryChannelConfigSWB.value == NOR) {
    if (KeySwB.pressed()) {
      bitSet(keySwitch, 2);
    } else {
      bitClear(keySwitch, 2); 
    }
  } else if(MemoryChannelConfigSWB.value == INV) {
    if (!KeySwB.pressed()) {
      bitSet(keySwitch, 2);
    } else {
      bitClear(keySwitch, 2); 
    }
  }
  if(MemoryChannelConfigSWB1.value == OFF) {
    bitClear(keySwitch, 3);
  } else if(MemoryChannelConfigSWB1.value == NOR) {
    if (KeySwB1.pressed()) {
      bitSet(keySwitch, 3);
    } else {
      bitClear(keySwitch, 3);
    }
  } else if(MemoryChannelConfigSWB1.value == INV) {
    if (!KeySwB1.pressed()) {
      bitSet(keySwitch, 3);
    } else {
      bitClear(keySwitch, 3);
    }
  } 
}

void Display() {
  if(navSubMenu) {
    if(navMenu == LCD) {
      display.subMenuLCD(MemoryLcdBacklight.value, MemoryLcdContrast.value, MemoryLcdFreq.value, navSubMenu, navSubMenuSel);  
    } else if(navMenu == CALIBRATION) {
      display.subMenuCalibration(MemoryCalibrationLXmin.value16bit, MemoryCalibrationLXmax.value16bit, MemoryCalibrationLYmin.value16bit, MemoryCalibrationLYmax.value16bit, MemoryCalibrationRXmin.value16bit, MemoryCalibrationRXmax.value16bit, MemoryCalibrationRYmin.value16bit, MemoryCalibrationRYmax.value16bit, AnalogLX.raw, AnalogLY.raw, AnalogRX.raw, AnalogRY.raw, navSubMenu, navSubMenuSel);
    } else if(navMenu == TRIMMED) {
      display.subMenuTrimmed(MemoryTrimPrecision.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == SOUND) {
      display.subMenuSound(MemoryBuzzerMode.value, MemoryBuzzerVolume.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == BATTERY) {
      display.subMenuBattery(MemoryBatteryWarning.value, MemoryBatteryLevel0.value, MemoryBatteryLevel1.value, MemoryBatteryLevel2.value, MemoryBatteryLevel3.value, MemoryBatteryLevel4.value, MemoryBatteryFreq.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == TRANSMISSION) {
      display.subMenuTransmission(MemoryControlTX.value, MemoryControl433.value, MemoryControl24.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == LIMITS) {
      display.subMenuLimits(MemoryLimitLX.value, MemoryLimitLY.value, MemoryLimitRX.value, MemoryLimitRY.value, MemoryLimitVRA.value, MemoryLimitVRB.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == MIXER) {
      display.subMenuMixer(MemoryChannelConfigLX.value, MemoryChannelConfigLY.value, MemoryChannelConfigRX.value, MemoryChannelConfigRY.value, MemoryChannelConfigVRA.value, MemoryChannelConfigVRB.value, MemoryChannelConfigSWA.value, MemoryChannelConfigSWA1.value, MemoryChannelConfigSWB.value, MemoryChannelConfigSWB1.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == MODEL) {
      display.subMenuModel(MemoryModelSel.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == VERSION) {
      display.subMenuVersion(git, ver, date ,navSubMenu, navSubMenuSel);
    } else if(navMenu == T433) {
      display.subMenu433(MemorySpeed433.value16bit, navSubMenu, navSubMenuSel);
    } else if(navMenu == T24) {
      display.subMenu24(MemoryChannel24.value, MemoryPAlvl24.value, MemoryRate24.value, MemoryAutoAck24.value, MemoryDelay24.value, MemoryCount24.value, MemoryCRC24.value, navSubMenu, navSubMenuSel);
    } else if(navMenu == SYSTEM) {
      display.subMenuSystem(navSubMenu, navSubMenuSel);
    }
  } else if(navMenu) {
    display.mainMenu(navMenu);
  } else {
    if(navPanel == 0) {
      display.mainPanel0(bat_lvl, MemoryControlTX.value, MemoryControl24.value, MemoryControl433.value, MemoryTrimLY.value, MemoryTrimLX.value, MemoryTrimRX.value, MemoryTrimRY.value, mainLY, mainLX, mainRX, mainRY, keySwitch);
    } else if(navPanel == 1) {
      display.mainPanel1(mainLY, mainLX, mainRX, mainRY, mainVRA, mainVRB);
    } else if(navPanel == 2) {
      display.mainPanel2(bat, MemoryTrimLY.value, MemoryTrimLX.value, MemoryTrimRX.value, MemoryTrimRY.value, mainLY, mainLX, mainRX, mainRY, mainVRA, mainVRB);
    } else if(navPanel == 3) {
      display.mainPanel3(MemoryTrimLY.value, MemoryTrimLX.value, MemoryTrimRX.value, MemoryTrimRY.value, mainLY, mainLX, mainRX, mainRY, mainVRA, mainVRB);
    } else if(navPanel == 4) {
      display.mainPanel4(bat_lvl, MemoryControlTX.value, MemoryControl24.value, MemoryControl433.value, keySwitch, rateNRF24, rate433, cps, rateLCD);
    } else if(navPanel == 5) {
      display.mainPanel5(bat_lvl, MemoryControlTX.value, MemoryControl24.value, MemoryControl433.value, keySwitch, MemoryLimitRX.value, MemoryLimitRY.value);
    }
  }
  display.freqCount++;
}
