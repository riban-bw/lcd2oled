//#include "Arduino.h"


/*
 led2oled Library - display() and noDisplay()

 Demonstrates the use a 128 x 64 pixel (21 x 8 character) OLED display.  The lcd2oled
 library works with all OLED displays that are compatible with the
 Solomon Systech SSD1306 driver.

 This sketch prints "Hello World!" to the OLED and uses the
 display() and noDisplay() functions to turn on and off
 the display.

 The circuit:
 * OLED RES# pin to digital pin 12
 * OLED D/C# pin to ground (selects I2C address 0x3C
 * OLED D1 & D2 pins to SDA (A4 on Uno)
 * OLED D0 pin to SCL (A5 on Uno)

 This example code is in the public domain.

 https://github.com/riban-bw/lcd2oled
 Example code derived from LiquidCrystal example code

 */

// include the library code:
#include <lcd2oled.h>

// Initialise the library with the index of the OLED reset pin
lcd2oled lcd(12); //!@todo URGENT adding constructor stops lcd2oled from working

void setup() {

  // set up the OLED's number of columns and rows:
  lcd.begin(21, 8);

  // Print a message to the OLED.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}

