/*
  14 Segment Display Data for LC75823
  Created by Fırat SOYGÜL, 20 Aralık 200x11
  (https://github.com/firatsoygul/LC75823)
*/

#ifndef character_h
#define character_h

#include <avr/pgmspace.h>

const unsigned short character14SEG[95] PROGMEM = {
    0b0000000000000000, // SPACE - ASCII 32
    0b0000000110000000, // !
    0b0001000010000000, // "
    0b0111010111010011, // #
    0b0101010111010010, // $
    0b0001010110010010, // %
    0b0000011110110010, // &
    0b0001000000000000, // '
    0b0000000000101000, // (
    0b0000101000000000, // )
    0b0000111110111000, // *
    0b0000010110010000, // +
    0b0000100000000000, // ,
    0b0000010000010000, // -
    0b0010000000000000, // .
    0b0000100000001000, // /
    0b0111000001000011, // 0 - ASCII 48
    0b0000000000000011, // 1
    0b0110010001010001, // 2
    0b0100010001010011, // 3
    0b0001010000010011, // 4
    0b0101010001010010, // 5
    0b0111010001010010, // 6
    0b0000000001000011, // 7
    0b0111010001010011, // 8
    0b0101010001010011, // 9 - ASCII 57
    0b0000000110000000, // :
    0b0000100010000000, // ;
    0b0000000000101000, // >
    0b0100010000010000, // =
    0b0000101000000000, // <
    0b0010010001010001, // ?
    0b0111010011010001, // @
    0b0011010001010011, // A - ASCII 65
    0b0111000001010011, // B
    0b0111000001000000, // C
    0b0111000001000011, // D
    0b0111010001010000, // E
    0b0011010001010000, // F
    0b0111000001000010, // G
    0b0011010000010011, // H
    0b0000000000000011, // I
    0b0110000000000011, // J
    0b0000000110101000, // K
    0b0111000000000000, // L
    0b0011001000001011, // M
    0b0011001000100011, // N
    0b0111000001000011, // O
    0b0011010001010001, // P
    0b0111000001100011, // Q
    0b0011010001110001, // R
    0b0101010001010010, // S
    0b0000000111000000, // T
    0b0111000000000011, // U
    0b0111000000000011, // V
    0b0111000100000011, // W
    0b0000101000101000, // X
    0b0001010100010001, // Y
    0b0100100001001000, // Z
    0b0000000000101000, // ( - ASCII 91
    0b0000001000100000, //'\'
    0b0000101000000000, // )
    0b0000000001000000, // ^
    0b0100000000000000, // _
    0b0000001000000000, // `
    0b0011010001010011, // a - ASCII 96
    0b0111000001010011, // b
    0b0111000001000000, // c
    0b0111000001000011, // d
    0b0111010001010000, // e
    0b0011010001010000, // F
    0b0111000001000010, // g :)
    0b0011010000010011, // h
    0b0000000000000011, // i
    0b0110000000000011, // J
    0b0000000110101000, // K
    0b0111000000000000, // l
    0b0011001000001011, // M
    0b0011001000100011, // n
    0b0111000001000011, // o
    0b0011010001010001, // P
    0b0111000001100011, // Q
    0b0011010001110001, // r
    0b0101010001010010, // s
    0b0000000111000000, // T
    0b0111000000000011, // u
    0b0111000000000011, // v
    0b0111000100000011, // w
    0b0000101000101000, // X
    0b0001010100010001, // y
    0b0100100001001000, // z
    0b0000000000101000, // ( - ASCII 123
    0b0000000110000000, // |
    0b0000101000000000, // )
    0b0000010000010000, // ~ - ASCII 126
};

#endif
