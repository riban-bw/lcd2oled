/*	constants.h Declaration of the constants for riban OLED library with LiquidCrystal library compatible API for Arduino using I2C interface
*	Copyright (c) riban.co.uk 2015	
*/

#pragma once

//Mode: D/C# bit (b6) = 0 for data or 1 for command
//Fundamental commands
#define OLED_CMD_MODE				0x80 //Sets display to command mode
#define OLED_DATA_MODE				0x40 //Sets display to data mode (to write to GDDRAM)
//Display control commands
#define OLED_CMD_CONTRAST			0x81 //1 data word. Set display contrast (0-255)
#define OLED_CMD_ENTIREON_DISABLE	0xA4 //0 data word. Use normal graphics memory for display
#define OLED_CMD_ENTIREON_ENABLE	0xA5 //0 data word. Turns on all display pixels
#define OLED_CMD_NORMAL				0xA6 //0 data word. Restores inverted display to normal
#define OLED_CMD_INVERSE			0xA7 //0 data word. Inverts display colours (negative)
#define OLED_CMD_DISPLAY_OFF		0xAE //0 data word. Turns display off
#define OLED_CMD_DISPLAY_ON			0xAF //0 data word. Turns display on
//Scrolling commands
#define OLED_CMD_SCROLL_RIGHT		0x26 //6 data words. Configures horizontal scroll mode (see below for configuration data)
#define OLED_CMD_SCROLL_LEFT		0x27 //6 data words. Configures horizontal scroll mode (see below for configuration data)
#define OLED_CMD_SCROLL_VERT_RIGHT	0x29 //6 data words. Configures vertical and horizontal scroll mode (see below for configuration data)
#define OLED_CMD_SCROLL_VERT_LEFT	0x2A //6 data words. Configures vertical and horizontal scroll mode (see below for configuration data)
											//D0=0x00
											//D1=Start page
											//D2=Interval between scroll steps (0=5frames, 1=64frames, 2=128frames, 3=256frames, 4=3frames, 5=4frames, 6=25frames, 7=2frames)
											//D3=End page (>=start page)
											//D4=Vertical scroll effect b0:5 identify rows to scroll (0x00 for scroll left / right)
											//D5=0xFF
#define OLED_CMD_SCROLL_STOP		0x2E //0 data word. Stops scrolling. GDDRAM must be rewritten after scrolling stopped
#define OLED_CMD_SCROLL_START		0x2F //0 data word. Starts scrolling. Use immediately after configuring scrolling effect
#define OLED_CMD_SCROLL_WINDOW		0xA3 //2 data words. Configure window that will scroll vertically.
											//D0[0:5]=Quantity of rows fixed at top that will not scroll
											//D1[0:6]=Height of window in rows
//Address setting commands
#define OLED_CMD_COLUMN_LOW			0x00 //0 data word. b0:3 define the lower column start address (only for page addressing mode) (0x00-0x0F)
#define OLED_CMD_COLUMN_HIGH		0x10 //0 data word. b0:3 define the upper column start address (only for page addressing mode) (0x10-0x1F)
#define OLED_CMD_MEMORY_ADDRESS_MODE 0x20 //1 data word. Sets the GDDRAM addressing mode.
	#define OLED_MODE_HORIZONTAL		0x00 	//D0=0x00 Horizontal address mode
	#define OLED_MODE_VERTICAL			0x01 	//D0=0x01 Vertical address mode
	#define OLED_MODE_PAGE				0x02 	//D0=0x02 Page address mode (default)
#define OLED_CMD_COLUMN_RANGE		0x21 //2 data words. Set column range (only for horizontal or vertical addressing mode)
											//D0=Column start address range (0-127)
											//D1=Column end address range (0-127)
#define OLED_CMD_PAGE_ADDRESS		0x22 //2 data words. Set page range (only for page addressing mode)
											//D0=Page start address (0-7)
											//D1=Page end address (0-7)
#define OLED_CMD_PAGE_START			0xB0 //0 data word. [b0:2] Set GDDRAM page start address (only for page addressing mode) (0xB0-0xB7)
//Hardware commands
#define OLED_CMD_START_LINE			0x40 //0 data word. [b0:b5] Set the display start line (0x40-0x7F)
#define OLED_CMD_SCAN_LEFT2RIGHT	0xA0 //0 data word. Column address 0 is mapped to SEG0 (default)
#define OLED_CMD_SCAN_RIGHT2LEFT	0xA1 //0 data word. Column address 127 is mapped to SEG0
#define OLED_CMD_MUX_RATIO			0xA8 //1 data word. Sets the ratio used for multiplexing screen redraws (value is one less than mux value)
											//D0=ratio (15-63)
#define OLED_CMD_SCAN_TOP2BOTTOM	0xC0 //0 data word. Normal scan direction from COM0 to COM[n-1] (where n is multiplex ratio)
#define OLED_CMD_SCAN_BOTTOM2TOP	0xC8 //0 data word. Reverse scan direction from COM[n-1] to COM0 (where n is multiplex ratio)

#define OLED_CMD_OFFSET				0xD3 //1 data word. Set vertical shift.
											//D0=Shift (0-63)
#define OLED_CMD_PIN_CONFIG			0xDA //1 data word. Sets the hardware pin configuration for COM pins
	#define OLED_PIN_SEQ				0x00 //D0[b4]=0 Sequential pin configuration (default)
	#define OLED_PIN_SEQ_REVERSE		0x20 //D0[b4]=1 Alternative pin configuration
	#define OLED_PIN_ALT				0x10 //D0[b5]=0 Disable COM left / right remap (default)
	#define OLED_PIN_ALT_REVERSE		0x30 //D0[b5]=1 Enable COM left / right remap
#define OLED_CMD_CLOCK_DIVIDE		0xD5 //1 data word.
											//D0[b4:7]=Osc freq (0-15). [b0:3]=display clock divider (plus 1) 1-16
#define OLED_CMD_PRECHARGE_PERIOD	0xD9 //1 data word.
											//D0[b4:7]=Phase 2 period. [b0:3]=Phase 1 period. (DClk units)
#define OLED_CMD_VCOM_LEVEL			0xDB //1 data word. Set the Vcomh deselect level
	#define	OLED_VCOM_65			0x00 //D0=0x00 0.65 x Vcc
	#define	OLED_VCOM_77			0x20 //D0=0x20 0.77 x Vcc (default)
	#define	OLED_VCOM_83			0x30 //D0=0x30 0.83 x Vcc
#define OLED_CMD_CHARGE_PUMP		0x8D //1 data word. Turn charge pump on / off. Charge pump used to create higher voltage (than vcc) to drive display
											//D0=0x00=off, 0x14=on
#define OLED_CMD_NOP				0xE3 //0 data word. No operation

#define OLED_LEFT_BORDER 			1 //Quantity of pixels to offset display from left edge. Set to 1 to centre display (21 x 6 = 126, hence 1 pixel each side)
//Scroll rates in frames
#define OLED_SCROLLRATE_2 7
#define OLED_SCROLLRATE_3 4
#define OLED_SCROLLRATE_4 5
#define OLED_SCROLLRATE_5 0
#define OLED_SCROLLRATE_25 6
#define OLED_SCROLLRATE_64 1
#define OLED_SCROLLRATE_128 2
#define OLED_SCROLLRATE_256 3
//Rotation
#define OLED_ROTATE_0	0	//No rotation
#define OLED_ROTATE_180	1	//Rotation 180 degrees clockwise
#define OLED_ROTATE_90	2	//Rotation 90 degrees clockwise
#define OLED_ROTATE_270	3	//Rotation 270 degrees clockwise
