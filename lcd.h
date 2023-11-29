/* 
 * File:   colLCD.h
 * Author: 21towe
 *
 * Created on October 19, 2023, 6:20 PM
 */

#ifndef COLLCD_H
#define	COLLCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "mcc_generated_files/mcc.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x8DOTS 0x00

    
#define D0 lcd_D0_LAT
#define D1 lcd_D1_LAT
#define D2 lcd_D2_LAT
#define D3 lcd_D3_LAT
#define D4 lcd_D4_LAT
#define D5 lcd_D5_LAT
#define D6 lcd_D6_LAT
#define D7 lcd_D7_LAT
#define RS lcd_RS_LAT
#define EN lcd_RW_LAT

void lcd_init();
void lcd_clear();
void lcd_writechar(char x);
void lcd_displayON();
void lcd_customChar(char loc, char map[8]);
void lcd_NoAutoScroll();
void lcd_autoScroll();
void lcd_cursorPos(char col, char row);


#ifdef	__cplusplus
}
#endif

#endif	/* COLLCD_H */

