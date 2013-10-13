/*
 * File:   LCD.c
 * Author: Jelle
 *
 * Created on 31 juli 2013
 *
 * Content: LCD driver
 */

#include "LCD.h"

// Keeps track of current line number and character position.
struct lcd_info_type lcd_info;

void initLCD(void) {
    LCD_BACKLIGHT_TRIS = OUTPUT;

    __delay_ms(5);
    
    // IO Tris
    LCD_D0_TRIS = OUTPUT;
    LCD_D1_TRIS = OUTPUT;
    LCD_D2_TRIS = OUTPUT;
    LCD_D3_TRIS = OUTPUT;
    LCD_D4_TRIS = OUTPUT;
    LCD_D5_TRIS = OUTPUT;
    LCD_D6_TRIS = OUTPUT;
    LCD_D7_TRIS = OUTPUT;
    LCD_RW_TRIS = OUTPUT;
    LCD_RS_TRIS = OUTPUT;
    LCD_EN_TRIS = OUTPUT;
 
    // init
    LCD_RS = 0;     //RS=0: Command, RS=1: Data
    LCD_RW = 0;     //R/W=0: Write, R/W=1: Read
    LCD_EN = 0;     //clock enable

    __delay_ms(15);

    commandLCD(0b00110000); // 8 bit interface, 8 chars per line, 5x10 pixels per char
    commandLCD(0b00110000);
    commandLCD(0b00110000);
    commandLCD(0b00111000);
    commandLCD(0b00000110); // no display shift
    commandLCD(0b00011000); 
    commandLCD(0b00001100); // display on, cursor off, no blink
    lcd_info.line = lcd_info.pos = 0;
}

void clearLCD(void) {
    commandLCD(0b00000001);
    __delay_ms(2);
    setCursorLCD(0,0);
}

void sendByte(byte b){
    byte D0_temp,D1_temp,D2_temp;

    union {
        unsigned char D;
        struct {
            unsigned D0:1;
            unsigned D1:1;
            unsigned D2:1;
            unsigned D3:1;
            unsigned D4:1;
            unsigned D5:1;
            unsigned D6:1;
            unsigned D7:1;
          };
    }data;

    // Save current data on datapins for LED's
    D0_temp = LCD_D0;
    D1_temp = LCD_D1;
    D2_temp = LCD_D2;

    // set byte on datapins
    data.D=b;
    LCD_EN = 1;         // Bring enable pin high
    LCD_D0 = data.D0;
    LCD_D1 = data.D1;
    LCD_D2 = data.D2;
    LCD_D3 = data.D3;
    LCD_D4 = data.D4;
    LCD_D5 = data.D5;
    LCD_D6 = data.D6;
    LCD_D7 = data.D7;
    LCD_EN = 0;       // data is clocked at the falling edge of enable pin

    // restore data on datapins
    LCD_D0 = D0_temp;
    LCD_D1 = D1_temp;
    LCD_D2 = D2_temp;

}
void commandLCD(const byte c) {
    // Write command to LCD
    LCD_RW = 0;
    LCD_RS = 0;

    sendByte(c);        // Write command data to data port

    __delay_us(45);     // wait until display has processed the data
}


// set cursor at position p of line l
void setCursorLCD(byte l, byte p) {
    byte c;

    // check if input is valid
    if (l>LCD_LASTLINE) l = LCD_LASTLINE;
    if (p>LCD_LASTPOS)  p = LCD_LASTPOS;

    lcd_info.line = l;
    lcd_info.pos = p;

    if (l == 1)
            c = 0b11000000;
    else
            c = 0b10000000;

    // position offset
    p &= 0b00001111;
    c |= p;

    commandLCD(c);

    __delay_us(45);         // wait until display has processed the command
}


void appendCharToLCD(const char c) {
    if (lcd_info.pos>LCD_LASTPOS){
        if (lcd_info.line)
            clearLCD();
        else
            setCursorLCD(1, 0);
    }
    // Write data to LCD
    LCD_RW = 0;
    LCD_RS = 1;

    sendByte(c);       // Write command data to data port
    __delay_us(45);         // wait until display has processed the data

    lcd_info.pos++;       // increment lcd cursor position
}


void printCharToLCD(const char c, byte l, byte p) {
    // set cursor to selected position
    setCursorLCD(l,p);

    // append to this position
    appendCharToLCD(c);
}

void appendStringToLCD_(const char* message) {
    while (*message) {
            appendCharToLCD(*message++);
    }
}

void printStringToLCD(char* message, byte l, byte p) {
    // set cursor to selected position
    setCursorLCD(l,p);
    // append to this position
    appendStringToLCD(message);
}

void appendStringToLCDcharptr(const char* message) {
    while(*message) {
    appendCharToLCD(*message++);
    }
}

void appendIntToLCD(int i) {
    char buffer[6];
    itoa(buffer,i,10);
    buffer[5] = 0;
    appendStringToLCDcharptr(buffer);
}

void printIntToLCD(int i, byte l, byte p) {
    // set cursor to selected position
    setCursorLCD(l,p);

    // append to this position
    appendIntToLCD(i);
}
