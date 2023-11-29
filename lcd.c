
#include "lcd.h"

static uint8_t displayFunction = 0x00;
static uint8_t displayMode = 0x00;
static uint8_t displayControl = 0x00;

void pins(char x)
{
    D4 = (bool)(x&0x1);
    D5 = (bool)(x&0x2);
    D6 = (bool)(x&0x4);
    D7 = (bool)(x&0x8);

}

void cmdL(char x, bool rs)
{
    pins(x);
    RS = rs;
    EN = 0;
    __delay_us(1);
    EN = 1;
    __delay_us(1);
    EN = 0;
    __delay_us(100);
}
void cmd(char x)
{
    cmdL(x,0);
} 
void cmdDubbel(char x)
{
    cmd(x>>4);
    cmd(x);

}
void cmdDubbelL(char x, bool rs)
{
    cmdL(x>>4, rs);
    cmdL(x, rs);

}

void lcd_init()
{
    displayFunction = 
        LCD_4BITMODE    | 
        LCD_2LINE       | 
        LCD_5x8DOTS     |
        LCD_1LINE
    ;
    //Wait for powerupp
    pins(0x00);
    __delay_ms(20);
    //Set lcd to 4 bit mode (d4-d7), try multiple times (idk, arduino lcd library)
    for(int i = 0; i < 3; i++)
    {
        cmd(0x03);
        __delay_ms(15);
    }    
    //4 bit interface
    cmd(0x02);
    
    // Set the functions
    cmdDubbel(displayFunction | LCD_FUNCTIONSET);
    //cmd(displayFunction);
    
    //Ingen aning varför cmd(0x00) behöver vara på båda sidor men de gör de
    // De är inte där i arduinos bibliotek
    displayControl = 
        LCD_DISPLAYON   | 
        LCD_CURSORON    |
        LCD_BLINKON
    ;
    lcd_displayON();
    lcd_clear();

    
    displayMode = 
        LCD_ENTRYLEFT | 
        LCD_ENTRYSHIFTDECREMENT
    ;
    cmdDubbel(LCD_ENTRYMODESET | displayMode);
    
}

//Load a custom characters, you can load a maximum of 8 loaction (0-7)
void lcd_customChar(char loc, char map[])
{
    loc &= 0x7;
    cmdDubbel(LCD_SETCGRAMADDR | (loc << 3));
    //cmd(LCD_SETCGRAMADDR | (loc << 3));
    //cmd(0x00);
    for(int i = 0; i < 8; i++)
        lcd_writechar(map[i]);
}

void lcd_writechar(char x)
{
    cmdDubbelL(x,1);
}

void lcd_NoAutoScroll()
{
    displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    cmdDubbel(LCD_ENTRYMODESET | displayMode);
}
void lcd_autoScroll()
{
    displayMode |= LCD_ENTRYSHIFTINCREMENT;
    cmdDubbel(LCD_ENTRYMODESET | displayMode);
}

void lcd_displayOFF()
{
    displayControl &= ~LCD_DISPLAYON;
    cmdDubbel(LCD_DISPLAYCONTROL | displayControl);
}
void lcd_displayON()
{
    displayControl |= LCD_DISPLAYON;
    cmdDubbel(LCD_DISPLAYCONTROL | displayControl);
}

void lcd_clear()
{
    cmdDubbel(LCD_CLEARDISPLAY);
    __delay_ms(2);
}

void lcd_cursorPos(char col, char row)
{
    cmdDubbel(LCD_SETDDRAMADDR | (col+row));
}
