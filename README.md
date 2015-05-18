# lcd2oled
An Arduino library to drive a SDD1306 OLED using same API as LiquidCrystal library and I2C interface.

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

