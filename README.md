# lcd2oled
An Arduino library providing communication with SDD1306 OLED display over I2C interface using same API as LiquidCrystal library.

# Introduction
lcd2oled is a library for Arduino to drive SDD1306 OLED displays. It supports different size displays but is tested with 128 x 64 pixel display.
The SDD1306 is a versatile OLED controller. It has several interfaces. This driver controls the I2C interface using the Arduino built in I2C interface plus one digital output pin used for reset.
I2C interfacing is provided by the Arduino Wire library which must be added to your project. (How to connect Arduino for I2C is detailed here: http://www.arduino.cc/en/reference/Wire.)

If you have a project that uses the HD44780 LCD interface, it may be fairly simply migrated to use SDD1306 OLED with this library. Changes required are:

Change include to:

```
#include <lcd2oled>
```

Initiator takes only one parameter: Digital pin connected to SDD1306 reset, e.g. change:

```
LiquidCrystal(3,4,5,6,7,8);
````

to

```
led2olde(3);
```

# Usage
The library is designed to use the same API as the LiquidCrystal library. Documentation for the LiquidCrystal library (and hence description on its use) may be found here: http://www.arduino.cc/en/Reference/LiquidCrystal.
There are some functions that are not implemented:

| Function      | Description                                 |
| ------------- | ------------------------------------------- |
| blink         | There is no feature within SDD1306 to flash |
| setRowOffsets | This is not documented in LiquidCrystal     |

lcd2oled provides extra functions, specific to the OLED.

* Reset - Reset to default settings
* SetBrightness -Sets the display brightness (0 - 255)
* Rotate - Rotates the display through 180 degrees
* ConfigureScrolling - Configures continuous scroll
* StartScrolling - Starts continuous scroll
* StopScrolling - Stops continuous scroll
* AllOn - Turns all pixels on
* ShowTest - Draws a hashed pattern slowly to whole screen

# Notes
Scrolling is implemented using a fragile method. It may not behave as expected and may be slower than LCD. It may block program flow for longer.

Small, low cost OLED displays typically have 128 columns of pixels and either 32 or 64 rows of pixels. This library uses a 5x7 pixel character set (font) similar to that used on HD44780 LCD displays, with a single pixel spacing between characters and rows. By default, it provides 21 characters per row with one pixel border on left and right (21 characters, each 6 pixels wide (5 pixels for the character plus one for inter-character spacing) results in 126 pixels, 2 fewer than the typical OLED width) and 8 rows (8 characters, each 8 pixels high (7 pixels for the character plus one for the inter-row spacing - also used for underscore cursor, results in 64 pixels).

The size of the display area may be set using the begin(Width, Height) function. This allows for the use of 128 x 32 displays, e.g. begin(21, 4). It also allows less of the display to be used, e.g. begin(16, 2) will present a 16 x 2 character display, using the upper left part of the OLED. (No scaling is included within the library.)

There is one pixel between each row. This space is also used for the underscore cursor. This may not be as obvious as a larger LCD display. There is no blinking cursor. (The author believes this could be implemented but would require modification to the userspace application to provide regular poking of the lcd2oled instance, e.g. lcd.poke() in main program loop. Such modification does not align with API compatibility but may be considered as an enhancement.

Similar to the LiquidCrystal library, led2oled intialises display to 21 x 8 (LiquidCrystal initialises to 16 x 1) so user only needs to call begin() to change display size.   

There are several other OLED libraries available which provide graphic capability. lcd2oled specifically avoids providing such functionality. It is targetted at developers who require text only display and who may already be familiar with the LiquidCrystal library or wish to port designs from HD 44780 LCD to SSD1306 OLED. The code within lcd2oled is not based on any other works. The character set is based on OzOLED character set which is provided for use without any restriction (It is placed in public domain). (This character set is slightly modified to centre the "i" and "I" characters.

The default character set is similar to that used by the HD44780. This differs from ASCII in three places:

| Character | HD44780 | ASCII |
| :-------: | :-----: | :---: |
| 92        | non-Latin char | / |
| 126 | Left arrow | ~ |
| 127 | Right arrow | BELL |

lcd2oled provides an ASCII character set (but with character 127 (BELL) replaced with a superscript o (degrees symbol)). This may be used by defining OLED_USE_ASCII as C++ preprocessor variable, e.g. by adding -DOLED_USE_ASCII to C++ compile options or by editing charsets.h and uncommenting the line:

```
#define OLED_USE_ASCII
```

