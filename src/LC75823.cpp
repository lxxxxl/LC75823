/*
  LC75823 Library for Arduino.
  Created by Fırat SOYGÜL, 20 Aralık 2017
  GNU General Public License v3.0
  (https://github.com/firatsoygul/LC75823/blob/master/LICENSE)
*/

#include "LC75823.h"
#include <SPI.h>
#include "character.h"

LC75823::LC75823() {

}

/*
* Function Name: begin
 * Description : receives the SPI address and slaveSelect pin information, sets SPI settings and starts communication.
 * Input : int chipEnabledPin(pin no to which slaveSelect pin is connected), 
 *         int address(SPI data address).
 * Output : None
 */
void LC75823::begin(int chipEnabledPin, int address) {
  _chipEnabledPin = chipEnabledPin;
  _address = address;
  pinMode(_chipEnabledPin, OUTPUT);
  SPISettings(38000, MSBFIRST, SPI_MODE0);
  SPI.begin();
  //_setSymbol();
}

/*
* Function Name: textSize
 * Description : Calculates the character length of the text sent to the lcd and saves to global variable _textLenght.
 * Input : char array
 * Output : None
 */
void LC75823::_textSize(char text[]) {
  _textLenght = 0;
  while (text[_textLenght] != '\0') {
    _textLenght++;
  }
}

/*
* Function Name: speed
 * Description : Allows to enter lcd animation speed.  
 * Input : int
 * Output : None
 */
void LC75823::speed(int textSpeed) { _textSpeed = textSpeed; }

/*
* Function Name: clear
 * Description : Resets the _container array that carries the character data, the _loopNumber int variable that holds the number of rotations of the text on the screen
 *               and the _sScroll int variables that hold the animation number, and prints an empty container on the screen.
 *               (It only removes characters from the screen, symbols are not.)
 * Input : None
 * Output : None
 */
void LC75823::clear() {
  memset(_container, 0, _containerSize);
  memset(_screen, 0, sizeof(_screen));
  // memset(_symbol, 0, 4); // To delete symbols.
  _sScroll = 0;
  _loopNumber = 0;
  _print(_address, _screen);
}

/*
* Function Name: reset
 * Description : Reset all variables and arrays that carry the data sent to the screen.
 *               (Including characters and symbols.)
 * Input : None
 * Output : None
 */
void LC75823::reset() {
  memset(_screen, 0, sizeof(_screen));
  memset(_container, 0, _containerSize);
  _sScroll = 0;
  _tScroll = 0;
  _loopNumber = 0;
  _textLenght = 0;
  _textSpeed = 300;
  _volumeLevel = 0;
  _print(_address, _screen);
}

/*
* Function Name: display
 * Description : LCD POWER SAVING(BU DATA) mode is turn on with 0. 
 * Input : None
 * Output : None
 */
void LC75823::display() {
  bitWrite(_screen[18], 1, 0);
  _print(_address, _screen);
}

/*
* Function Name: noDisplay
 * Description : LCD POWER SAVING(BU DATA) mode is turn on with 1. 
 * Input : None
 * Output : None
 */
void LC75823::noDisplay() {
  bitWrite(_screen[18], 1, 1);
  _print(_address, _screen);
}

/*
* Function Name: volumeStartValue
 * Description : Sets the initial value of lcd volume indicators (Default = 0)
 * Input : int startValue
 * Output : None
 */
void LC75823::volumeStartValue(int startValue){
  _volumeStartValue = startValue;
}

/*
* Function Name: volumeEndValue
 * Description : Sets the end value of lcd volume indicators (Default = 8)
 * Input : int endValue
 * Output : None
 */
void LC75823::volumeEndValue(int endValue){
  _volumeEndValue = endValue;
}


/*
* Function Name: volumeRightLevel
 * Description : It determines the value of the volume indicators on the right. The range of values can be specified with the volumeStartValue and volumeEndValue methods.
 * Input : int levelValue (Volume level value on the right).
 * Output : None
 */
void LC75823::volumeLevel(int levelValue) {
  int convertedLevelValue = ((levelValue - _volumeStartValue) /
                             ((_volumeEndValue - _volumeStartValue) / 9));

  if (convertedLevelValue > _volumeLevel) {
    while (_volumeLevel <= convertedLevelValue) {
      symbol(_volumeLevel + VOLUME_1, 1);
      _volumeLevel++;
    }
  }

  else if (convertedLevelValue < _volumeLevel) {
    while (_volumeLevel > convertedLevelValue) {
      symbol(_volumeLevel + VOLUME_1, 0);
      _volumeLevel--;
    }
  }

  _volumeLevel = convertedLevelValue;
}

/*
* Function Name: textLoopCount
 * Description : Returns the number of repetitions of the entered text on the screen.
 * Input : None
 * Output : int
 */
int LC75823::textLoopCount() { return _loopNumber; }

/*
* Function Name: _textLoop
 * Description : Process the repetition count of the displayed text.
 * Input : None
 * Output : None
 */
void LC75823::_textLoop() {
  if (_sScroll > _textLenght) {
    _sScroll = 0;
    _loopNumber++;
  }
}

/*
* Function Name: text
 * Description : Prints the text.
 * Input : char text[] - Char array of text to be printed.
 * Output : None
 */
void LC75823::text(char text[]) {
  _textSize(text);
    char _screenText[8];
  for (int i = 0; i < 8; i++) {
    _screenText[i] = text[i];
    if (i >= _textLenght) {
      _screenText[i] = ' ';
    }
  }
  _letters(_screenText);
  _setLetters();
  _setSymbols();
  _print(_address, _screen);
}

/*
 * Function Name: sText (Scroll Text)
 * Description : Prints by scrolling the text from left to right
 * Input : char text[] - Char array of text to be printed.
 * Output : None
 */
void LC75823::sText(char text[]) {
  _textSize(text);
  char _screenText[8];
  for (int i = 0; i < 8; i++) {
    //int c = text[i + _tScroll] - 32;
    _screenText[i] = text[i + _tScroll];
    if ((i + _tScroll) >= _textLenght) {
      _screenText[i] = ' ';
    }
  }
  if (_tScroll == _textLenght) {
    _tScroll = 0;
  } else {
    _tScroll++;
  }
  _letters(_screenText);
  _setLetters();
  _textLoop();
  // TODO restore symbols state
  _print(_address, _screen);
}

/*
 * Function Name: _setSymbols
 * Description : Saves symbol states to the _screen byte array.
 * Input : None
 * Output : None
 */
void LC75823::_setSymbols() { /*bitWrite(_screen[0], 7, _iconSt);*/ }

/*
 * Function Name: _setLetters
 * Description : It performs the necessary bit shifting to make the ASCII codes of the entered text suitable for the SPI data package of the lcd driver.
 *               performs the necessary bit-shifting operations. Result is assigned to the _screen byte array.
 * Input : None
 * Output : None
 */
void LC75823::_setLetters() {
  byte j = 1;
  _n = 0;
  for (int i = 0; i <= 14; i += 2) {
    _screen[i] = (_container[_n] << j) | (_container[_n + 1] >> (8 - j));
    if (i < 2) {
      _screen[i + 1] = _container[_n + 1] << j;
    } else if (i >= _containerSize) {
      _screen[i] = _container[_n + 1];
      _screen[i + 1] = 0;
    } else {
      _screen[i + 1] =
          (_container[_n + 1] << j) | (_container[_n + 2] >> (7 - j));
    }
    if ((_n + 2) > _containerSize) {
      _n = 0;
      _screen[i + 1] =
          _container[_containerSize] << j | _container[0] >> (7 - j);
    } else {
      _n += 2;
    }
    j++;
  }
  _sScroll++;
}

/*
 * Function Name: _print
 * Description : Using the Arduino SPI library, it sends the _address int variable, _screen and _symbols byte strings to the driver.
 *               to send the strings to the lcd using the Arduino SPI library
 * Input : byte pScreen[] 
 * Output : None
 */
void LC75823::_print(int pAddress, byte pScreen[]) {
  digitalWrite(_chipEnabledPin, LOW);
  // Address Data (A1- A8)
  SPI.transfer(pAddress);
  digitalWrite(_chipEnabledPin, HIGH);

  // Character Segment Data (D1- D120) 15 Byte
  for (int i = 0; i <= 19; i++) {
    SPI.transfer(pScreen[i]);
  }

  digitalWrite(_chipEnabledPin, LOW);
  delay(_textSpeed);
}

/*
 * Function Name: symbol
 * Description : Shows the symbols the user wants.
 * Input : enum Symbol symbolName(symbol definition), 
 *         boolean status(visibility, 0 = Off, 1 = On )
 * Output : None
 */
void LC75823::symbol(enum Symbol symbolName, boolean status) {
  switch (symbolName) {
  // top symbols  
  case AF:
    bitWrite(_screen[1], 2, status);
    break;
  case TP:
    bitWrite(_screen[1], 6, status);
    break;
  case TA:
    bitWrite(_screen[1], 5, status);
    break;
  case PTY:
    bitWrite(_screen[1], 4, status);
    break;
  case DVD:
    bitWrite(_screen[3], 4, status);
    break;
  case VCD:
    bitWrite(_screen[5], 5, status);
    break;
  case CD:
    bitWrite(_screen[7], 6, status);
    break;
  case WMA:
    bitWrite(_screen[10], 0, status);
    break;
  case RINGS:
    bitWrite(_screen[16], 3, status);
    break;
  // bottom symbols
  case RPT:
    bitWrite(_screen[1], 3, status);
    break;
  case EON:
    bitWrite(_screen[1], 1, status);
    break;
  case MP4:
    bitWrite(_screen[9], 7, status);
    break;
  case MP3:
    bitWrite(_screen[14], 2, status);
    break;
  case STEREO:
    bitWrite(_screen[16], 0, status);
    break;
  // volume
  case VOLUME_1:
    bitWrite(_screen[18], 7, status);
    break;
  case VOLUME_2:
    bitWrite(_screen[18], 6, status);
    break;
  case VOLUME_3:
    bitWrite(_screen[18], 5, status);
    break;
  case VOLUME_4:
    bitWrite(_screen[1], 7, status);
    break;
  case VOLUME_5:
    bitWrite(_screen[0], 0, status);
    break;
  case VOLUME_6:
    bitWrite(_screen[0], 1, status);
    break;
  case VOLUME_7:
    bitWrite(_screen[0], 4, status);
    break;
  case VOLUME_8:
    bitWrite(_screen[0], 3, status);
    break;
  case VOLUME_9:
    bitWrite(_screen[0], 2, status);
    break;

  default:;
    break;
  }
  _print(_address, _screen);
}

/*
 * Function Name: _letters
 * Description : Compares the ASCII equivalents of the characters in the entered text with the character14SEG two-dimensional array in the character.h 
 *               file and transfers the values to the _container byte array.
 * Input : char gk[](First 8 characters of the text entered)
 * Output : None
 */
void LC75823::_letters(char gk[]) {
  int d = 0;
  for (int i = 0; i < 8; i++) {
    int c = gk[i] - 32;
    if (c >= 0 && c <= 94) {
      unsigned short word = pgm_read_word(&character14SEG[c]);
      _container[d + 1] = word & 0x00FF;
      _container[d] = word >> 8;
    } else {
      _container[d] = 0;
      _container[d + 1] = 0;
    }
    d += 2;
  }
}
