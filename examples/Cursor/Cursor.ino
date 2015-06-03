/*
  lcd2oled Library - Cursor

 Demonstrates the use a 128x64 pixel (21x8 character) OLED display.  The lcd2oled
 library works with OLED displays that are compatible with the
 Solomon SysTech SDD1306 driver.

 This sketch prints "Hello World!" to the LCD and
 uses the cursor()  and noCursor() methods to turn
 on and off the cursor.

  The circuit:
 * OLED RES# pin to digital pin 12
 * OLED D0 to SLCK
 * OLED D1 to SDA
 * OLED D/C# pin to ground
 * OLED CS# pin to ground

 This example code is derived from LiquidCrystal example code and in the public domain.

 https://github.com/riban-bw/lcd2oled
 */

// include the library code:
#include <lcd2oled.h>

// Initialise the library with the numbers of the interface pins
lcd2oled lcd(12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the cursor:
  lcd.noCursor();
  delay(500);
  // Turn on the cursor:
  lcd.cursor();
  delay(500);
}

