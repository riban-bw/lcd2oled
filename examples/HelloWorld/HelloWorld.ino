/*
  lcd2oled Library - Hello World

 Demonstrates the use a 128x64 pixel (21x8 character) OLED display.  The lcd2oled
 library works with OLED displays that are compatible with the
 Solomon SysTech SDD1306 driver.

 This sketch prints "Hello World!" to the OLED
 and shows the time.

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
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

