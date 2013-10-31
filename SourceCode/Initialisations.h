/* 
 * File:   Initialisations.h
 * Author: Jelle
 *
 * Created on 28 juli 2013, 21:45
 *
 * Content: configuration, pinmapping, defines
 */

#ifndef INITIALISATIONS_H
#define	INITIALISATIONS_H

// Included libs
#include "p30F6012A.h"
#include <stdio.h>
#include <stdlib.h>

// *** Constants ***
#define Mips20          //Processor speed: Mips10 (75 mA), Mips20(138 mA) or Mips30 (200 mA)

// *** Pin mapping ***
// Board Leds
#define LEDred          LATBbits.LATB2
#define LEDorange       LATBbits.LATB4
#define LEDgreen        LATBbits.LATB3
// Buttons
#define BUTTONup        PORTBbits.RB7
#define BUTTONdown      PORTBbits.RB6
#define BUTTONenter     PORTDbits.RD8
// LED drivers
#define S1R1            LATFbits.LATF1
#define S1G1            LATGbits.LATG12
#define S1B1            LATGbits.LATG1
#define S1R2            LATGbits.LATG14
#define S1G2            LATCbits.LATC1
#define S1B2            LATFbits.LATF0
#define S1R3            LATGbits.LATG15
#define S1G3            LATGbits.LATG13
#define S1B3            LATGbits.LATG0
#define S2R1            LATDbits.LATD0
#define S2G1            LATDbits.LATD4
#define S2B1            LATDbits.LATD1
#define S2R2            LATDbits.LATD3
#define S2G2            LATDbits.LATD6
#define S2B2            LATDbits.LATD11
#define S2R3            LATDbits.LATD7
#define S2G3            LATDbits.LATD5
#define S2B3            LATDbits.LATD2
//Misc
#define PowerLow        PORTDbits.RD9
#define PowerEn         LATDbits.LATD10
#define Sense12V        PORTBbits.RB13
// LCD
#define LCD_D0          PORTBbits.RB2
#define LCD_D1          PORTBbits.RB3
#define LCD_D2          PORTBbits.RB4
#define LCD_D3          PORTBbits.RB5
#define LCD_D4          PORTGbits.RG9
#define LCD_D5          PORTGbits.RG8
#define LCD_D6          PORTGbits.RG7
#define LCD_D7          PORTGbits.RG6
#define LCD_BACKLIGHT   PORTCbits.RC2
#define LCD_RW          PORTBbits.RB0
#define LCD_RS          PORTBbits.RB8
#define LCD_EN          PORTBbits.RB1
// Audio
#define AudioOff        PORTGbits.RG2
#define AudioChan1      PORTBbits.RB14
#define AudioChan2      PORTBbits.RB15
#define Audio_CS        PORTGbits.RG3
#define SPI_SDI         PORTFbits.RF2
#define SPI_SDO         PORTFbits.RF3
#define SPI_SCK         PORTFbits.RF6

// *** General Constants ***
#define TRUE    1
#define FALSE   0
#define INPUT   1
#define OUTPUT  0
#define byte unsigned char
// *** Interrupts ***

// *** TRIS ***
#define LEDred_tris           TRISBbits.TRISB2
#define LEDorange_tris        TRISBbits.TRISB4
#define LEDgreen_tris         TRISBbits.TRISB3
#define BUTTONup_tris         TRISBbits.TRISB7
#define BUTTONdown_tris       TRISBbits.TRISB6
#define BUTTONenter_tris      TRISDbits.TRISD8
#define S1R1_tris             TRISFbits.TRISF1
#define S1G1_tris             TRISGbits.TRISG12
#define S1B1_tris             TRISGbits.TRISG1
#define S1R2_tris             TRISGbits.TRISG14
#define S1G2_tris             TRISCbits.TRISC1
#define S1B2_tris             TRISFbits.TRISF0
#define S1R3_tris             TRISGbits.TRISG15
#define S1G3_tris             TRISGbits.TRISG13
#define S1B3_tris             TRISGbits.TRISG0
#define S2R1_tris             TRISDbits.TRISD0
#define S2G1_tris             TRISDbits.TRISD4
#define S2B1_tris             TRISDbits.TRISD1
#define S2R2_tris             TRISDbits.TRISD3
#define S2G2_tris             TRISDbits.TRISD6
#define S2B2_tris             TRISDbits.TRISD11
#define S2R3_tris             TRISDbits.TRISD7
#define S2G3_tris             TRISDbits.TRISD5
#define S2B3_tris             TRISDbits.TRISD2
#define PowerLow_tris         TRISDbits.TRISD9
#define PowerEn_tris          TRISDbits.TRISD10
#define Sense12V_tris         TRISBbits.TRISB13
#define LCD_D0_TRIS           TRISBbits.TRISB2
#define LCD_D1_TRIS           TRISBbits.TRISB3
#define LCD_D2_TRIS           TRISBbits.TRISB4
#define LCD_D3_TRIS           TRISBbits.TRISB5
#define LCD_D4_TRIS           TRISGbits.TRISG9
#define LCD_D5_TRIS           TRISGbits.TRISG8
#define LCD_D6_TRIS           TRISGbits.TRISG7
#define LCD_D7_TRIS           TRISGbits.TRISG6
#define LCD_BACKLIGHT_TRIS    TRISCbits.TRISC2
#define LCD_RW_TRIS           TRISBbits.TRISB0
#define LCD_RS_TRIS           TRISBbits.TRISB8
#define LCD_EN_TRIS           TRISBbits.TRISB1
#define AudioOff_tris          TRISGbits.TRISG2
#define AudioChan1_tris       TRISBbits.TRISB14
#define AudioChan2_tris       TRISBbits.TRISB15
#define Audio_CS_tris         TRISGbits.TRISG3
#define SPI_SDI_tris          TRISFbits.TRISF2
#define SPI_SDO_tris          TRISFbits.TRISF3
#define SPI_SCK_tris          TRISFbits.TRISF6

// clockspeed:
#ifdef Mips30             // MCU: HS/2 w/PLL 16x => 30 MIPS
    #define Fosc 120        // oscillator = 120 MHz
    #define FCY 30000000UL  // clock period = 30 MHz
#elif defined(Mips20)       // MCU: HS/3 w/PLL 16x => 20 MIPS
    #define Fosc 80         // oscillator = 80 MHz
    #define FCY 20000000UL  // clock period = 20 MHz
#else                       // MCU: HS/3 w/PLL 8x => 10 MIPS
    #define Fosc 40         // oscillator = 40 MHz
    #define FCY 10000000UL  // clock period = 10 MHz
#endif

// includes
#include <libpic30.h>
#include "LEDdriver.h"
#include "LCD.h"
#include "Audio.h"

// Function prototypes
void init(void);    // configure the microcontroller

#endif	/* INITIALISATIONS_H */

