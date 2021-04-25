/*
  LC75823 Library for Arduino.
  Created by Fırat SOYGÜL, 20 Aralık 2017
  GNU General Public License v3.0
  (https://github.com/firatsoygul/LC75823/blob/master/LICENSE)
*/

#ifndef LC75823_h
#define LC75823_h
#include "Arduino.h"

enum Symbol {
  // top symbols
  AF,
  TP,
  TA,
  PTY,
  DVD,
  VCD,
  CD,
  WMA,
  RINGS,
  // bottom symbols
  RPT,
  EON,
  MP4,
  MP3,
  STEREO,
  // volume
  VOLUME_1,
  VOLUME_2,
  VOLUME_3,
  VOLUME_4,
  VOLUME_5,
  VOLUME_6,
  VOLUME_7,
  VOLUME_8,
  VOLUME_9
};

class LC75823 {
public:
  LC75823();
  void begin(int chipEnabledPin, int address);
  void text(char text[]);
  void sChart(boolean chartValue);
  void sText(char text[]);
  int textLoopCount();
  void symbol(enum Symbol symbolName, boolean status);
  void volumeChart(int volumeChartNo, boolean status);
  void volumeStartValue(int startValue);
  void volumeEndValue(int endValue);
  void volumeLevel(int levelValue);
  void speed(int textSpeed);
  void display();
  void noDisplay();
  void clear();
  void reset();

private:
  int _volumeLevel = 0;
  int _loopNumber = 0;
  int _tScroll = 0;
  byte _sScroll = 0;
  byte _container[19];
  int _containerSize = 19;
  int _n = 0;
  int _textLenght = 0;
  int _chipEnabledPin = 10;
  int _address = 130;
  int _textSpeed = 300; // Default speed
  void _textLoop();
  void _textSize(char text[]);
  void _letters(char gk[]);
  void _letters_ORJ(uint8_t gk[]);
  void _setLetters();
  void _setSymbols();
  void _print(int pAddress, byte pScreen[]);
  int _volumeStartValue = 0;
  int _volumeEndValue = 8;
  byte _screen[19];         // 19 SPI byte package for character and symbol data
  bool _symbols[14];        // stores status of symbols (switch on/off)
};

#endif
