/*	lcd2oled.h Declaration of OLED library with LiquidCrystal library compatible API for Arduino using I2C interface
 *	Copyright (c) riban.co.uk 2015
 *
 *	Provides emulation of 21x8 LCD (HD44870) character interface
 *	Based on Solomon Systech datasheet SSD1306 Rev 1.1
 *
 *	@note Depends on Wire library
 */

//!@todo	setRowOffsets(int row0, int row1, int row2, int row3) is implemented in LiquidCrystal but not documented - not implemented in lcd2oled
//!@todo	blink() and noBlink() are not implemented - there is no flashing feature built in to SSD1306 so flashing may require timer functions - may not be simple to implement
#pragma once
#include "constants.h"

#if defined(ARDUINO) && ARDUINO < 100
#include <WProgram.h>
#else
#include "Arduino.h"
#endif

#define OLED_I2C_ADDRESS 0x3C //I2C address - may be 0x3C or 0x3D, depending on hardware configuration
#define OLED_CUSTOM_CHARS 8 //Quantity of custom characters (max=32)

class lcd2oled : public Print
{
  public:
    //OLED specific functions

    /**	@brief	Constructor
     *	@param	ResetPin Pin connected to OLED reset. Default not use reset pin
     */
    lcd2oled(uint8_t ResetPin = 0xFF);

    /**	@brief	Destructor
     *
     */
    virtual ~lcd2oled();

    /**	@brief	Reset OLED modules
     *	@note	If reset pin not configured then this does nothing
     *	@todo	Perform software reset if hardware reset not configured
     */
    void Reset();

    /**	@brief	Draws test pattern
     */
    void ShowTest();

    /**	@brief	Turns all pixels on
     *	@param	bEnable True to turn all pixels on. False to use graphics memory
     */
    void AllOn(bool bEnable = true);

    /**	@brief	Set display brightness
     *	@param	nBrightness Value of brightness (0 - 255)
     *	@note	Minimum brightness (0) does dims display but does not extinguish it
     */
    void SetBrightness(uint8_t nBrightness);

    /**	@brief	Rotates display through 180 degrees
     *	@param	nRotate Rotation degree (OLED_ROTATE_0 | OLED_ROTATE_90 | OLED_ROTATE_180 | OLED_ROTATE_270)
     *	@note	Only OLED_ROTATE_0 and OLED_ROTATE_180 are currently implemented
     */
    void Rotate(uint8_t nRotate = OLED_ROTATE_180);

    /**	@brief	Configures continuous scroll
     *	@param	nSpeed Rate of scrolling [OLED_SCROLLRATE_2 | OLED_SCROLLRATE_3 | OLED_SCROLLRATE_4 | OLED_SCROLLRATE_5 (default) | OLED_SCROLLRATE_25 | OLED_SCROLLRATE_64 | OLED_SCROLLRATE_128 | OLED_SCROLLRATE_256]
     *	@param	bRight True to scroll right. False to scroll left. Default is false (scroll left)
     *	@param	nTopRow Index of the first row to scroll. Default is top row
     *	@param	nBottomRow Index of last row to scroll. Default is bottom row
     *	@note	Scrolling is continuous, wrapping to other side of screen
     */
    void ConfigureScrolling(uint8_t nSpeed = OLED_SCROLLRATE_5, bool bRight = false, uint8_t nTopRow = 0, uint8_t nBottomRow = 7);

    /**	@brief	Start continuous scroll
     */
    void StartScrolling();

    /**	@brief	Stop continuous scroll
     */
    void StopScrolling();

    //LiquidCrystal library emulation functions

    /**	@brief	Initialises display
     *	@param	nColumns Quantity of columns in display (default is 21)
     *	@param	nColumns Quantity of rows in display (default is 8)
     *	@param	nCharSize Not used - for compatibility with LiquidCrystal API
     *	@param	bChargePump False to disable OLED charge pump. Default enabled
     *	@note	Charge pump is used to create voltage required to run OLED if supply is insufficient. Probably needs to be enabled for 5V or lower supplies
     */
    void begin(uint8_t nColumns = 21, uint8_t nRows = 8, uint8_t nCharSize = 0,
    bool bChargePump = true);

    /**	@brief	Turns display on
     */
    void display();

    /**	@brief	Turns display off
     *	@note	This mode reduces power consumption
     */
    void noDisplay();

    /**	@brief	Clears the display
     */
    void clear();

    /**	@brief	Sets cursor to home position (0,0)
     */
    void home();

    /**	@brief	Hide cursor
     */
    void noCursor();

    /**	@brief	Show cursor
     */
    void cursor();

    /**	@brief	Set the position of the print cursor, i.e. where next character will be printed
     *	@param	x Index of column (0 - MaxColumn)
     *	@param	y Index of row (0 - MaxRow)
     */
    void setCursor(uint8_t x, uint8_t y);

    /**	@brief	Stops cursor blinking
     *	@note	Does nothing - blink is not implemented (see documentation)
     */
    void noBlink();

    /**	@brief	Start cursor blinking - not implemented
     *	@note	Blink is not implemented (see documentation)
     */
    void blink();

    /**	@brief	Refreshes display with any time dependent data
     * 	@note	Call regularly if blink() is used, otherwise no need to use this function
     */
    void Refresh();

    /**	@brief	Scroll whole display one character to left
     */
    void scrollDisplayLeft();

    /**	@brief	Scroll whole display one character to right
     */
    void scrollDisplayRight();

    /**	@brief	Set direction of text to left-to-right
     *	@note	Does not update display. Each character written will be to the right of previously written character
     */
    void leftToRight();

    /**	@brief	Set direction of text to right-to-left
     *	@note	Does not update display. Each character written will be to the left of previously written character
     */
    void rightToLeft();

    /**	@brief	Enable autoscroll mode
     *	@note	Whole display scrolls before each character is written.
     *	@note	Scroll direction depends on print direction (left-to-right / right-to-left)
     */
    void autoscroll();

    /**	@brief	Disables autoscroll mode
     *	@see	autoscroll
     */
    void noAutoscroll();

    /**	@brief	Create a custom character
     *	@param	nChar The character index (0 - OLED_CUSTOM_CHARS)
     *	@param	pBitmap Array of 5 bytes representing rows of character bitmap
     */
    void createChar(uint8_t nChar, uint8_t[]); //!@todo Why can't I add a name for the second parameter?

    /**	@brief	Set display inverse (black<->white)
     * 	@param	bInverse True to inverse, false for normal display
     */
    void inverse(bool bInverse = true);

    /**	@brief	Writes a character to the display at current location
     * 	@param	nChar Character to write
     * 	@return	<i>size_t</i> Quantity of characters written (always 1)
     */
    virtual size_t write(uint8_t Char);
    using Print::write;

  private:
    //Send a single bte command message
    //	nCommand is the OLED command to send (see constants.h OLED_CMD_...)
    void SendCommand(uint8_t nCommand);
    //Send a command with data
    //	nCommand is the OLED command to send (see constants.h OLED_CMD_...)
    //	nData is the data byte to send
    void SendCommand(uint8_t nCommand, uint8_t nData);
    //Send data to the GDDRAM
    //	nData is the data byte to send (writes 8 pixels in vertical column at current draw position and moves to next column)
    void SendData(uint8_t nData);
    //Draws the character at the current cursor position
    //	nChar = Character to draw (ASCII / HD44780 character set - see charsets.h)
    //	nCursor = 0x80 to draw underscore cursor (actually this is logically OR'd with each column so could also use 0x40 to strike through)
    void Draw(uint8_t nChar, uint8_t nCursor = 0x00);
    //Redraws the character at the current cursor position including underscore cursor if enabled
    //	bBlank = true to blank the character (default false)
    void Redraw(bool bBlank = false);
    // Writes a character to the display
    //	nChar The character to write
    //	returns quantity of characters written
    //	@note	This function performs the actual screen update and is required to allow write() to work with autoscroll
    size_t Write(uint8_t Char);

    unsigned long m_lBlinkTime; // Time to toggle character cursor flashing - 0 to disable
    uint8_t m_nResetPin; 	// Index of pin connected to OLED reset - 0xFF if not used
    uint8_t m_nColumns;		// Quantity of columns in display
    uint8_t m_nRows;		// Quantity of rows in display
    uint8_t m_nCursor;		// 0x80 if cursor enabled else 0x00
    uint8_t m_nX;			// Current cursor column
    uint8_t m_nY;			// Current cursor row
    uint8_t m_nRotation;			// Current rotation (OLED_ROTATE_0 | OLED_ROTATE_90 | OLED_ROTATE_180 | OLED_ROTATE_270)
    bool m_bLeftToRight;			// True left-to-right mode. False for right-to-left mode
    bool m_bAutoscroll;		// True to enable autoscroll mode
    bool m_bBlinkOn;		// True if flashing cursor is asserted (all black)
    uint8_t m_pCustom[OLED_CUSTOM_CHARS][5]; // Custom character glyphs
    uint8_t * m_pBuffer; 	// Pointer to buffer holding current display
};
