/* 
 * File:   LCD.h
 * Author: Jelle
 *
 * Created on 31 juli 2013, 1:
 *
 * Content: LCD driver
 */

#ifndef LCD_H
#define	LCD_H

#include "Initialisations.h"

// Properties
#define LCD_WIDTH       16
#define LCD_HEIGHT      2
#define LCD_LASTLINE    (LCD_HEIGHT - 1)
#define LCD_LASTPOS     (LCD_WIDTH - 1)

// Macro's
#define backlightOn()    (LCD_BACKLIGHT = 1)
#define backlightOff()   (LCD_BACKLIGHT = 0)

#define appendStringToLCD(message)   appendStringToLCD_((const char*)(message))

//#define byte unsigned char

// Functions
void initLCD(void);
void clearLCD(void);
void sendByte(byte b);

void commandLCD(const byte c);
void setCursorLCD(byte l, byte p);

void appendCharToLCD(const char c);
void printCharToLCD(const char c, byte l, byte p);

void appendStringToLCD_(const char* s);
void printStringToLCD(char* s, byte l, byte p);

void appendIntToLCD(int i);
void printIntToLCD(int i, byte l, byte p);

// Structures
struct lcd_info_type {
  unsigned char line;
  unsigned char pos;
};

// Keeps track of current line number and character position.
extern struct lcd_info_type lcd_info;

#endif	/* LCD_H */

