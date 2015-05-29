/*	charsets.h Declaration of the character sets for riban OLED library with LiquidCrystal library compatible API for Arduino using I2C interface
 *	Copyright (c) riban.co.uk 2015
 */

#pragma once

//Uncomment next line to use ASCII character set instead of HD44780 character set or add "-D OLED_USE_ASCII" to C++ compile options
//#define OLED_USE_ASCII

#ifdef OLED_USE_ASCII
/*	5 x 7 pixel font ASCII 32 - 127, vertically stripped, i.e. each byte represents a column of pixels. LSB at top.
 MSB of each byte is clear providing one pixel line spacing and space for underscore cursor.
 Array contains just characters with no inter-character spacing. Application must add space between characters.
 Derived from OzOLED character set with following licence:
 This font be freely used without any restriction(It is placed in public domain)
 */
const byte FONT_5x7[][5] PROGMEM =
{
  { 0x00,0x00,0x00,0x00,0x00}, // space
  { 0x00,0x5F,0x00,0x00,0x00}, // !
  { 0x00,0x07,0x00,0x07,0x00}, // "
  { 0x14,0x7F,0x14,0x7F,0x14}, // #
  { 0x24,0x2A,0x7F,0x2A,0x12}, // $
  { 0x23,0x13,0x08,0x64,0x62}, // %
  { 0x36,0x49,0x55,0x22,0x50}, // &
  { 0x00,0x05,0x03,0x00,0x00}, // '
  { 0x1C,0x22,0x41,0x00,0x00}, // (
  { 0x41,0x22,0x1C,0x00,0x00}, // )
  { 0x08,0x2A,0x1C,0x2A,0x08}, // *
  { 0x08,0x08,0x3E,0x08,0x08}, // +
  { 0xA0,0x60,0x00,0x00,0x00}, // ,
  { 0x08,0x08,0x08,0x08,0x08}, // -
  { 0x60,0x60,0x00,0x00,0x00}, // .
  { 0x20,0x10,0x08,0x04,0x02}, // /
  { 0x3E,0x51,0x49,0x45,0x3E}, // 0
  { 0x00,0x42,0x7F,0x40,0x00}, // 1
  { 0x62,0x51,0x49,0x49,0x46}, // 2
  { 0x22,0x41,0x49,0x49,0x36}, // 3
  { 0x18,0x14,0x12,0x7F,0x10}, // 4
  { 0x27,0x45,0x45,0x45,0x39}, // 5
  { 0x3C,0x4A,0x49,0x49,0x30}, // 6
  { 0x01,0x71,0x09,0x05,0x03}, // 7
  { 0x36,0x49,0x49,0x49,0x36}, // 8
  { 0x06,0x49,0x49,0x29,0x1E}, // 9
  { 0x00,0x36,0x36,0x00,0x00}, // :
  { 0x00,0xAC,0x6C,0x00,0x00}, // ;
  { 0x08,0x14,0x22,0x41,0x00}, // <
  { 0x14,0x14,0x14,0x14,0x14}, // =
  { 0x41,0x22,0x14,0x08,0x00}, // >
  { 0x02,0x01,0x51,0x09,0x06}, // ?
  { 0x32,0x49,0x79,0x41,0x3E}, // @
  { 0x7E,0x09,0x09,0x09,0x7E}, // A
  { 0x7F,0x49,0x49,0x49,0x36}, // B
  { 0x3E,0x41,0x41,0x41,0x22}, // C
  { 0x7F,0x41,0x41,0x22,0x1C}, // D
  { 0x7F,0x49,0x49,0x49,0x41}, // E
  { 0x7F,0x09,0x09,0x09,0x01}, // F
  { 0x3E,0x41,0x41,0x51,0x72}, // G
  { 0x7F,0x08,0x08,0x08,0x7F}, // H
  { 0x00,0x41,0x7F,0x41,0x00}, // I (changed by riban - centred)
  { 0x20,0x40,0x41,0x3F,0x01}, // J
  { 0x7F,0x08,0x14,0x22,0x41}, // K
  { 0x7F,0x40,0x40,0x40,0x40}, // L
  { 0x7F,0x02,0x0C,0x02,0x7F}, // M
  { 0x7F,0x04,0x08,0x10,0x7F}, // N
  { 0x3E,0x41,0x41,0x41,0x3E}, // O
  { 0x7F,0x09,0x09,0x09,0x06}, // P
  { 0x3E,0x41,0x51,0x21,0x5E}, // Q
  { 0x7F,0x09,0x19,0x29,0x46}, // R
  { 0x26,0x49,0x49,0x49,0x32}, // S
  { 0x01,0x01,0x7F,0x01,0x01}, // T
  { 0x3F,0x40,0x40,0x40,0x3F}, // U
  { 0x1F,0x20,0x40,0x20,0x1F}, // V
  { 0x3F,0x40,0x38,0x40,0x3F}, // W
  { 0x63,0x14,0x08,0x14,0x63}, // X
  { 0x03,0x04,0x78,0x04,0x03}, // Y
  { 0x61,0x51,0x49,0x45,0x43}, // Z
  { 0x7F,0x41,0x41,0x00,0x00}, // [
  { 0x02,0x04,0x08,0x10,0x20}, // '/' (HD44780 has non-Latin character here)
  { 0x41,0x41,0x7F,0x00,0x00}, // ]
  { 0x04,0x02,0x01,0x02,0x04}, // ^
  { 0x80,0x80,0x80,0x80,0x80}, // _
  { 0x01,0x02,0x04,0x00,0x00}, // `
  { 0x20,0x54,0x54,0x54,0x78}, // a
  { 0x7F,0x48,0x44,0x44,0x38}, // b
  { 0x38,0x44,0x44,0x28,0x00}, // c
  { 0x38,0x44,0x44,0x48,0x7F}, // d
  { 0x38,0x54,0x54,0x54,0x18}, // e
  { 0x08,0x7E,0x09,0x02,0x00}, // f
  { 0x18,0xA4,0xA4,0xA4,0x7C}, // g
  { 0x7F,0x08,0x04,0x04,0x78}, // h
  { 0x00,0x00,0x7D,0x00,0x00}, // i (changed by riban - centred)
  { 0x80,0x84,0x7D,0x00,0x00}, // j
  { 0x7F,0x10,0x28,0x44,0x00}, // k
  { 0x41,0x7F,0x40,0x00,0x00}, // l
  { 0x7C,0x04,0x18,0x04,0x78}, // m
  { 0x7C,0x08,0x04,0x7C,0x00}, // n
  { 0x38,0x44,0x44,0x38,0x00}, // o
  { 0xFC,0x24,0x24,0x18,0x00}, // p
  { 0x18,0x24,0x24,0xFC,0x00}, // q
  { 0x00,0x7C,0x08,0x04,0x00}, // r
  { 0x48,0x54,0x54,0x24,0x00}, // s
  { 0x04,0x7F,0x44,0x00,0x00}, // t
  { 0x3C,0x40,0x40,0x7C,0x00}, // u
  { 0x1C,0x20,0x40,0x20,0x1C}, // v
  { 0x3C,0x40,0x30,0x40,0x3C}, // w
  { 0x44,0x28,0x10,0x28,0x44}, // x
  { 0x1C,0xA0,0xA0,0x7C,0x00}, // y
  { 0x44,0x64,0x54,0x4C,0x44}, // z
  { 0x08,0x36,0x41,0x00,0x00}, // {
  { 0x00,0x7F,0x00,0x00,0x00}, // |
  { 0x41,0x36,0x08,0x00,0x00}, // }
  { 0x02,0x01,0x01,0x02,0x01}, // ~ (HD44780 has right arrow here)
  { 0x02,0x05,0x05,0x02,0x00}  // ° (HD44780 has left arrow here)
};

#else
/*	5 x 7 pixel font ASCII 32 - 127, vertically stripped, i.e. each byte represents a column of pixels. LSB at top.
 MSB of each byte is clear providing one pixel line spacing and space for underscore cursor.
 Array contains just characters with no inter-character spacing. Application must add space between characters.
 Derived from OzOLED character set with following licence:
 This font be freely used without any restriction(It is placed in public domain)
 */
const byte FONT_5x7[][5] PROGMEM =
{
  { 0x00,0x00,0x00,0x00,0x00}, // space
  { 0x00,0x5F,0x00,0x00,0x00}, // !
  { 0x00,0x07,0x00,0x07,0x00}, // "
  { 0x14,0x7F,0x14,0x7F,0x14}, // #
  { 0x24,0x2A,0x7F,0x2A,0x12}, // $
  { 0x23,0x13,0x08,0x64,0x62}, // %
  { 0x36,0x49,0x55,0x22,0x50}, // &
  { 0x00,0x05,0x03,0x00,0x00}, // '
  { 0x1C,0x22,0x41,0x00,0x00}, // (
  { 0x41,0x22,0x1C,0x00,0x00}, // )
  { 0x08,0x2A,0x1C,0x2A,0x08}, // *
  { 0x08,0x08,0x3E,0x08,0x08}, // +
  { 0xA0,0x60,0x00,0x00,0x00}, // ,
  { 0x08,0x08,0x08,0x08,0x08}, // -
  { 0x60,0x60,0x00,0x00,0x00}, // .
  { 0x20,0x10,0x08,0x04,0x02}, // /
  { 0x3E,0x51,0x49,0x45,0x3E}, // 0
  { 0x00,0x42,0x7F,0x40,0x00}, // 1
  { 0x62,0x51,0x49,0x49,0x46}, // 2
  { 0x22,0x41,0x49,0x49,0x36}, // 3
  { 0x18,0x14,0x12,0x7F,0x10}, // 4
  { 0x27,0x45,0x45,0x45,0x39}, // 5
  { 0x3C,0x4A,0x49,0x49,0x30}, // 6
  { 0x01,0x71,0x09,0x05,0x03}, // 7
  { 0x36,0x49,0x49,0x49,0x36}, // 8
  { 0x06,0x49,0x49,0x29,0x1E}, // 9
  { 0x00,0x36,0x36,0x00,0x00}, // :
  { 0x00,0xAC,0x6C,0x00,0x00}, // ;
  { 0x08,0x14,0x22,0x41,0x00}, // <
  { 0x14,0x14,0x14,0x14,0x14}, // =
  { 0x41,0x22,0x14,0x08,0x00}, // >
  { 0x02,0x01,0x51,0x09,0x06}, // ?
  { 0x32,0x49,0x79,0x41,0x3E}, // @
  { 0x7E,0x09,0x09,0x09,0x7E}, // A
  { 0x7F,0x49,0x49,0x49,0x36}, // B
  { 0x3E,0x41,0x41,0x41,0x22}, // C
  { 0x7F,0x41,0x41,0x22,0x1C}, // D
  { 0x7F,0x49,0x49,0x49,0x41}, // E
  { 0x7F,0x09,0x09,0x09,0x01}, // F
  { 0x3E,0x41,0x41,0x51,0x72}, // G
  { 0x7F,0x08,0x08,0x08,0x7F}, // H
  { 0x00,0x41,0x7F,0x41,0x00}, // I (changed by riban - centred)
  { 0x20,0x40,0x41,0x3F,0x01}, // J
  { 0x7F,0x08,0x14,0x22,0x41}, // K
  { 0x7F,0x40,0x40,0x40,0x40}, // L
  { 0x7F,0x02,0x0C,0x02,0x7F}, // M
  { 0x7F,0x04,0x08,0x10,0x7F}, // N
  { 0x3E,0x41,0x41,0x41,0x3E}, // O
  { 0x7F,0x09,0x09,0x09,0x06}, // P
  { 0x3E,0x41,0x51,0x21,0x5E}, // Q
  { 0x7F,0x09,0x19,0x29,0x46}, // R
  { 0x26,0x49,0x49,0x49,0x32}, // S
  { 0x01,0x01,0x7F,0x01,0x01}, // T
  { 0x3F,0x40,0x40,0x40,0x3F}, // U
  { 0x1F,0x20,0x40,0x20,0x1F}, // V
  { 0x3F,0x40,0x38,0x40,0x3F}, // W
  { 0x63,0x14,0x08,0x14,0x63}, // X
  { 0x03,0x04,0x78,0x04,0x03}, // Y
  { 0x61,0x51,0x49,0x45,0x43}, // Z
  { 0x7F,0x41,0x41,0x00,0x00}, // [
  { 0x15,0x16,0x7C,0x16,0x15}, // non-Latin character
  { 0x41,0x41,0x7F,0x00,0x00}, // ]
  { 0x04,0x02,0x01,0x02,0x04}, // ^
  { 0x80,0x80,0x80,0x80,0x80}, // _
  { 0x01,0x02,0x04,0x00,0x00}, // `
  { 0x20,0x54,0x54,0x54,0x78}, // a
  { 0x7F,0x48,0x44,0x44,0x38}, // b
  { 0x38,0x44,0x44,0x28,0x00}, // c
  { 0x38,0x44,0x44,0x48,0x7F}, // d
  { 0x38,0x54,0x54,0x54,0x18}, // e
  { 0x08,0x7E,0x09,0x02,0x00}, // f
  { 0x18,0xA4,0xA4,0xA4,0x7C}, // g
  { 0x7F,0x08,0x04,0x04,0x78}, // h
  { 0x00,0x00,0x7D,0x00,0x00}, // i (changed by riban - centred)
  { 0x80,0x84,0x7D,0x00,0x00}, // j
  { 0x7F,0x10,0x28,0x44,0x00}, // k
  { 0x41,0x7F,0x40,0x00,0x00}, // l
  { 0x7C,0x04,0x18,0x04,0x78}, // m
  { 0x7C,0x08,0x04,0x7C,0x00}, // n
  { 0x38,0x44,0x44,0x38,0x00}, // o
  { 0xFC,0x24,0x24,0x18,0x00}, // p
  { 0x18,0x24,0x24,0xFC,0x00}, // q
  { 0x00,0x7C,0x08,0x04,0x00}, // r
  { 0x48,0x54,0x54,0x24,0x00}, // s
  { 0x04,0x7F,0x44,0x00,0x00}, // t
  { 0x3C,0x40,0x40,0x7C,0x00}, // u
  { 0x1C,0x20,0x40,0x20,0x1C}, // v
  { 0x3C,0x40,0x30,0x40,0x3C}, // w
  { 0x44,0x28,0x10,0x28,0x44}, // x
  { 0x1C,0xA0,0xA0,0x7C,0x00}, // y
  { 0x44,0x64,0x54,0x4C,0x44}, // z
  { 0x08,0x36,0x41,0x00,0x00}, // {
  { 0x00,0x7F,0x00,0x00,0x00}, // |
  { 0x41,0x36,0x08,0x00,0x00}, // }
  { 0x08,0x08,0x2A,0x1C,0x08}, // right arrow
  { 0x08,0x1C,0x2A,0x08,0x08}  // left arrow
};

#endif
