/*	lcd2oled.cpp Implementation of riban OLED library with LiquidCrystal library compatible API for Arduino using I2C interface
*	Copyright (c) riban.co.uk 2015
*/

#include "Wire.h"
#include "lcd2oled.h"
#include "charsets.h"

lcd2oled::lcd2oled(uint8_t ResetPin)
{
	m_pBuffer = NULL;
	pinMode(ResetPin, OUTPUT);
	digitalWrite(ResetPin, LOW);
	delayMicroseconds(10); //Require 3us reset pulse but let's be generous. Use delayMicroseconds - wiring not yet initialised so delay() won't work!
	digitalWrite(ResetPin, HIGH);
//	begin(21, 8); //This causes failure because Reset() is called before wiring is initialised
}

void lcd2oled::Reset(bool bPump)
{
	//!@todo Do we need to reset if we are doing so in hardware?
	m_nCursor = 0x00; //No cursor
	m_bLeftToRight = true;
	m_bAutoscroll = false;
	Wire.begin(); //!@todo move Wire.begin() to init (or begin)
	//turn display off whilst we configure it
	noDisplay();
	//Configure pages (rows) 0 - 7)
	SendCommand(OLED_CMD_PAGE_ADDRESS, 0x00);
	SendCommand(0x07);
	SendCommand(OLED_CMD_COLUMN_RANGE, 0x00);
	SendCommand(0x7F);
	//Select horizontal mode (wrap at end of row)
	SendCommand(OLED_CMD_MEMORY_ADDRESS_MODE, OLED_MODE_HORIZONTAL); //Reset sets to Page mode but we want horizontal
	//Set offset to zero
	SendCommand(OLED_CMD_OFFSET, 0);
	//OLED physical configuration
	SendCommand(OLED_CMD_MUX_RATIO, 0x3F);
	SendCommand(OLED_CMD_PIN_CONFIG, OLED_PIN_ALT);
	Rotate(false); //Assume LCD is installed right way up - user must rotate in code if installed upside down
	SendCommand(OLED_CMD_CLOCK_DIVIDE, 0xF0); //Fastest clock (default is 0x80) to improve scroll speed and accuracy
	SendCommand(OLED_CMD_PRECHARGE_PERIOD, 0xF1);
	//Turn on charge pump
	if(bPump)
		SendCommand(OLED_CMD_CHARGE_PUMP, 0x14);
	//Set medium brightness
	SendCommand(OLED_CMD_CONTRAST, 0x7F);
	//Do not invert display
	SendCommand(OLED_CMD_NORMAL);
	//Set Vcom deslect to 77% of Vcc
	SendCommand(OLED_CMD_VCOM_LEVEL, OLED_VCOM_77);
	//Disable scrolling
	SendCommand(OLED_CMD_SCROLL_STOP);
	//Clear display
	clear();
	//Turn display on (not on by default after reset)
	display();
}

void lcd2oled::clear()
{
	noDisplay(); //Turn display off to hide slow scan clear
	for(unsigned int i=0; i < 1024; ++i) //!@todo replace 1024 with appropriate constant or calculated value
		SendData(0);
	memset(m_pBuffer, 32, m_nColumns * m_nRows); //fill buffer with spaces ' '
	display();
	home();
}

void lcd2oled::ShowTest()
{
	home();
	for(unsigned int i=0; i < 512; ++i)
	{
		SendData(0xAA);
		delay(10);
		SendData(0x55);
		delay(10);
	}
}

void lcd2oled::AllOn(bool bEnable)
{
	SendCommand(bEnable?OLED_CMD_ENTIREON_ENABLE:OLED_CMD_ENTIREON_DISABLE);
}

void lcd2oled::SetBrightness(uint8_t nBrightness)
{
	SendCommand(OLED_CMD_CONTRAST, nBrightness);
}

void lcd2oled::begin(uint8_t nColumns, uint8_t nRows, uint8_t nCharSize)
{
	if(!m_pBuffer)
		m_pBuffer = new uint8_t[nColumns * nRows];
	m_nColumns = nColumns;
	m_nRows = nRows;
	Reset(true);
}

void lcd2oled::display()
{
	SendCommand(OLED_CMD_DISPLAY_ON);
}

void lcd2oled::noDisplay()
{
	SendCommand(OLED_CMD_DISPLAY_OFF);
}

void lcd2oled::Rotate(bool b180)
{
	SendCommand(b180?OLED_CMD_SCAN_BOTTOM2TOP:OLED_CMD_SCAN_TOP2BOTTOM);
	SendCommand(b180?OLED_CMD_SCAN_RIGHT2LEFT:OLED_CMD_SCAN_LEFT2RIGHT);
}

void lcd2oled::ConfigureScrolling(uint8_t nSpeed, bool bRight, uint8_t nTopRow, uint8_t nBottomRow)
{
	SendCommand(OLED_CMD_SCROLL_STOP);
	SendCommand(bRight?OLED_CMD_SCROLL_RIGHT:OLED_CMD_SCROLL_LEFT, 0x00); //dummy data
	SendCommand(nTopRow, nSpeed); //start page, interval
	SendCommand(nBottomRow, 0x00); //end page, dummy
	SendCommand(0xFF); //dummy
}

void lcd2oled::StartScrolling()
{
	SendCommand(OLED_CMD_SCROLL_START);
}

void lcd2oled::StopScrolling()
{
	SendCommand(OLED_CMD_SCROLL_STOP);
}

void lcd2oled::SendCommand(uint8_t nCommand)
{
	Wire.beginTransmission(OLED_I2C_ADDRESS);
	Wire.write(OLED_CMD_MODE);
	Wire.write(nCommand);
	Wire.endTransmission();
}

void lcd2oled::SendCommand(uint8_t nCommand, uint8_t nData)
{
	Wire.beginTransmission(OLED_I2C_ADDRESS);
	Wire.write(OLED_CMD_MODE);
	Wire.write(nCommand);
	Wire.write(OLED_CMD_MODE);
	Wire.write(nData);
	Wire.endTransmission();
}

void lcd2oled::SendData(uint8_t nData)
{
	Wire.beginTransmission(OLED_I2C_ADDRESS);
	Wire.write(OLED_DATA_MODE);
	Wire.write(nData);
	Wire.endTransmission();
}

void lcd2oled::setCursor(uint8_t x, uint8_t y)
{
	if(x >= m_nColumns || y >= m_nRows)
		return;
	bool bCursor = (0x80 == m_nCursor);
	if(bCursor)
		noCursor(); //Remove cursor from current position
	m_nX = x;
	m_nY = y;
	SendCommand(OLED_CMD_COLUMN_LOW | ((6 * m_nX + OLED_LEFT_BORDER) & 0x0F)); //!@todo May be able to remove OLED_LEFT_BORDER by configuring display with borders
	SendCommand(OLED_CMD_COLUMN_HIGH | (((6 * m_nX + OLED_LEFT_BORDER) & 0xF0) >> 4));
	SendCommand(OLED_CMD_PAGE_START | m_nY);
	if(bCursor)
		cursor(); //Show cursor at new position
}

void noBlink()
{
	//!@todo Implement noBlink
}

void blink()
{
	//!@todo Implement blink
}

void lcd2oled::home()
{
	setCursor(0, 0);
}

void lcd2oled::noCursor()
{
	m_nCursor = 0x00;
	Redraw();
}

void lcd2oled::cursor()
{
	m_nCursor = 0x80; //Set MSB which is used to draw underscore by logical OR with character
	Redraw();
}

void lcd2oled::createChar(uint8_t nIndex, uint8_t* pBitmap)
{
	if(nIndex >= OLED_CUSTOM_CHARS)
		return;
	for(uint8_t i = 0; i < 5; ++i)
	{
		m_pCustom[nIndex][i] = 0;
		for(uint8_t j = 0; j < 7; ++j)
		{
			//!@todo Can this horrible bit of code to rotate custom glyph from horizontal to vertical encoding be optimised?
			m_pCustom[nIndex][i] |= (((*(pBitmap + j) & (1 << (4-i))) >> (4-i)) << j);
		}
	}
}

void lcd2oled::scrollDisplayLeft()
{
	//Clear first column of text
	for(uint8_t nRow = 0; nRow < m_nRows; ++nRow)
	{
		setCursor(0, nRow);
		write(32);
	}
	ConfigureScrolling(OLED_SCROLLRATE_2);
	for(uint8_t i = 0; i < 6; ++i)
	{
		//Burst scrolling for each column of pixels
		StartScrolling();
		delay(10);
		StopScrolling();
	}
}

void lcd2oled::scrollDisplayRight()
{
	//Clear last column of text
	for(uint8_t nRow = 0; nRow < m_nRows; ++nRow)
	{
		setCursor(m_nColumns - 1, nRow);
		write(32);
	}
	ConfigureScrolling(OLED_SCROLLRATE_2, true);
	for(uint8_t i = 0; i < 6; ++i)
	{
		//Burst scrolling for each column of pixels
		StartScrolling();
		delay(10);
		StopScrolling();
	}
}

void lcd2oled::leftToRight()
{
	m_bLeftToRight = true;
}

void lcd2oled::rightToLeft()
{
	m_bLeftToRight = false;
}

void lcd2oled::autoscroll()
{
	m_bAutoscroll = true;
}

void lcd2oled::noAutoscroll()
{
	m_bAutoscroll = false;
}

size_t lcd2oled::write(uint8_t Char)
{
	if(m_nX >= m_nColumns)
		return 0; //Don't attempt to draw beyond end of display
	uint8_t nChar = Char;
	if((nChar < 32 && nChar >= OLED_CUSTOM_CHARS) || (nChar > 127))
		nChar = 32; //Draw space if invalid character
	Draw(nChar);
	m_pBuffer[m_nY * m_nColumns + m_nX] = nChar; //Update buffer (used to redraw with / without cursor undesrscore)
	if(m_bLeftToRight)
		++m_nX;
	else
	{
		if(--m_nX < m_nColumns)
		{
			SendCommand(OLED_CMD_COLUMN_LOW | ((6 * m_nX) & 0x0F));
			SendCommand(OLED_CMD_COLUMN_HIGH | (((6 * m_nX) & 0xF0) >> 4));
			SendCommand(OLED_CMD_PAGE_START | m_nY);
		}
	}
	if(m_bAutoscroll)
		if(m_bLeftToRight)
			scrollDisplayLeft(); //!@todo URGENT: This causes howl-round
		else
			scrollDisplayRight();
	if(0x80 == m_nCursor)
		Redraw(); //Redraws next character with cursor underscore
	return(1);
}

void lcd2oled::Draw(uint8_t nChar, uint8_t nCursor)
{
	for(uint8_t nColumn = 0; nColumn < 5; ++nColumn)
	{
		if(nChar < 32)
			SendData(m_pCustom[nChar][nColumn] | nCursor);
		else
			SendData(FONT_5x7[nChar - 32][nColumn] | nCursor); //!@todo get from program memory
	}
	SendData(0); //Add inter-character space
}

void lcd2oled::Redraw()
{
	if(m_nX >= m_nColumns)
		return;
	Draw(m_pBuffer[m_nY * m_nColumns + m_nX], m_nCursor);
	//Reposition cursor
	SendCommand(OLED_CMD_COLUMN_LOW | ((6 * m_nX + OLED_LEFT_BORDER) & 0x0F));
	SendCommand(OLED_CMD_COLUMN_HIGH | (((6 * m_nX + OLED_LEFT_BORDER) & 0xF0) >> 4));
	SendCommand(OLED_CMD_PAGE_START | m_nY);
}
