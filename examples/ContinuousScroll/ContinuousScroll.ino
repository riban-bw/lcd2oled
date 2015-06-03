/*
  lcd2oled Library - ContinuousScroll

 Demonstrates the use a 128x64 pixel (21x8 character) OLED display.  The lcd2oled
 library works with OLED displays that are compatible with the
 Solomon SysTech SDD1306 driver.

 This sketch prints "Hello World!" to the OLED then scrolls left and right.

  The circuit:
 * OLED RES# pin to digital pin 12
 * OLED D0 to SLCK
 * OLED D1 to SDA
 * OLED D/C# pin to ground
 * OLED CS# pin to ground

 https://github.com/riban-bw/lcd2oled
 */

// include the library code:
#include <lcd2oled.h>

// Initialise the library with the numbers of the interface pins
lcd2oled lcd(12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(21, 8);
  // Print a message to the LCD.
  lcd.print("TITLE - no scroll");
  lcd.setCursor(0, 1);
  lcd.print("SubTitle - noscroll");
  lcd.setCursor(0, 2);
  lcd.print("This is the paragraph");
  lcd.setCursor(0, 3);
  lcd.print("which will scroll");
  lcd.setCursor(0, 4);
  lcd.print("continuously");
  lcd.setCursor(0, 5);
  lcd.print("FOOTER - no scroll");
  lcd.setCursor(0, 6);
  lcd.print("SubFooter - no scroll");
}

void loop() {
	delay(1000);
	lcd.ConfigureScrolling(0, true, 2, 4);
	lcd.StartScrolling();
	delay(1000);
	lcd.StopScrolling();
	lcd.ConfigureScrolling(0, false, 2, 4);
	lcd.StartScrolling();
	delay(1000);
}

