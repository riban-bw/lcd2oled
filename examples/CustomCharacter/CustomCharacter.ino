/*
  lcd2oled Library - Custom Characters

 Demonstrates the use a 128x64 pixel (21x8 character) OLED display.  The lcd2oled
 library works with OLED displays that are compatible with the
 Solomon SysTech SDD1306 driver.

 This sketch prints "I <heart> Arduino!" and a little dancing man
 to the LCD.

  The circuit:
 * OLED RES# pin to digital pin 12
 * OLED D0 to SLCK
 * OLED D1 to SDA
 * OLED D/C# pin to ground
 * OLED CS# pin to ground

 This example code is derived from LiquidCrystal example code and in the public domain.

 https://github.com/riban-bw/lcd2oled

 Also useful:
 http://icontexto.com/charactercreator/
 */

// include the library code:
#include <lcd2oled.h>

// Initialise the library with the numbers of the interface pins
lcd2oled lcd(12);

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup() {
  // initialize LCD and set up the number of columns and rows: 
  lcd.begin(16, 2);
  
  // create a new character
  lcd.createChar(0, heart);
  // create a new character
  lcd.createChar(1, smiley);
  // create a new character
  lcd.createChar(2, frownie);
  // create a new character
  lcd.createChar(3, armsDown);
  // create a new character
  lcd.createChar(4, armsUp);

  // Print a message to the lcd.
  lcd.print("I "); 
  lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  lcd.print(" Arduino! ");
  lcd.write((byte) 1);

}

void loop() {
  // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 5th position:
  lcd.setCursor(4, 1);
  // draw the little man, arms down:
  lcd.write(3);
  delay(delayTime);
  lcd.setCursor(4, 1);
  // draw him arms up:
  lcd.write(4);
  delay(delayTime);
}
