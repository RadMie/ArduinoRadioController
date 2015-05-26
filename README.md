# **Arduino Radio Controller** #

*Universal RC*

#### Hardware

- Arduino Mega 2560 R3
- LCD PCD8544 - Nokia 5110
- XY-FST (FS1000A) - 433MHz
- nRF24L01+ 2.4GHz

#### Software

- Arduino 1.6.4 (Linux 64-bit)
- Fritzing 0.9.2b (Linux 64-bit)

#### RC

- MODELCRAFT MP-26-DT

#### Fritzing Schematic

#### Pin Function

| PIN    | MODE           | FUNCTION                       |
|--------|----------------|--------------------------------|
|    2   |  DIGITAL       |  KEY MINUS                     |
|    3   |  DIGITAL       |  KEY SEL                       |
|    4   |  DIGITAL       |  KEY MENU                      |
|    5   |  DIGITAL       |  KEY PLUS                      |
|    6   |  DIGITAL       |  CE - nRF24L01+                |
|    7   |  DIGITAL       |  CS - nRF24L01+                |
|    8   |  PWM           |  BUZZER                        |
|    9   |  PWM           |  BL - PCD8544                  |
|   10   |  DIGITAL       |  PTT - XY-FST                  |
|   11   |  DIGITAL       |  RX - XY-FST                   |
|   12   |  DIGITAL       |  TX - XY-FST                   |
|   A0   |  ANALOG        |  VRB                           |
|   A1   |  ANALOG        |  VRA                           |
|   A2   |  ANALOG        |  RY                            |
|   A3   |  ANALOG        |  LY                            |
|   A4   |  ANALOG        |  LX                            |
|   A5   |  ANALOG        |  RX                            |
|   A6   |  ANALOG        |  BATTERY                       |
|   22   |  DIGITAL       |  KEY TRIM LY UP                |
|   24   |  DIGITAL       |  KEY TRIM LY DOWN              |
|   26   |  DIGITAL       |  KEY TRIM RY DOWN              |
|   28   |  DIGITAL       |  KEY TRIM RY UP                |
|   30   |  DIGITAL       |  KEY SWA                       |
|   32   |  DIGITAL       |  KEY SWB                       |
|   34   |  DIGITAL       |  KEY SWA1                      |
|   36   |  DIGITAL       |  KEY SWB1                      |
|   37   |  DIGITAL       |  KEY TRIM LX LEFT              |
|   38   |  DIGITAL       |  KEY TRIM LX RIGHT             |
|   40   |  DIGITAL       |  KEY TRIM RX LEFT              |
|   42   |  DIGITAL       |  KEY TRIM RX RIGHT             |
|   44   |  DIGITAL       |  RST - PCD8544                 |
|   46   |  DIGITAL       |  CS - PCD8544                  |
|   48   |  DIGITAL       |  DC - PCD8544                  |
|   50   |  SPI MISO      |  MISO - nRF24L01+              |
|   51   |  SPI MOSI      |  MOSI - PCD8544, nRF24L01+     |
|   52   |  SPI SCK       |  SCK - PCD8544, nRF24L01+      |