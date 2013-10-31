/* 
 * File:   LEDdriver.h
 * Author: Jelle
 *
 * Created on 29 juli 2013, 0:25
 * 
 * Content: 
 */
#ifndef LEDDRIVER_H
#define	LEDDRIVER_H

#include "Initialisations.h"

// LED timer interrupts
#define LEDupdateOn T3CONbits.TON
#define CI_LEDupdate() IFS0bits.T3IF = 0

#define LEDtimerOn T2CONbits.TON
#define LEDnextToggle PR2
#define LEDtimerReg TMR2
#define CI_LEDtimer() IFS0bits.T2IF = 0

// LED timer constants
#define EOP 0xFFFF          // end of period

#ifdef Mips30
    #define LSBticks 74     // Number of timerticks per LSB of colorvalue
#elif defined(Mips20)
    #define LSBticks 49     // Number of timerticks per LSB of colorvalue
#else
    #define LSBticks 196    // Number of timerticks per LSB of colorvalue
#endif

// Function prototypes
void init_LEDdriver(void);
void updateLEDpins(void);
void setLEDColors(unsigned char colors[]);
int compare (const void* p1, const void* p2);
void setLedPin(int LEDnumber, int state);

#endif	/* LEDDRIVER_H */

