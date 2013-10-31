/*
 * File:   LEDdriver.c
 * Author: Jelle
 *
 * Created on 29 juli 2013, 0:25
 *
 * Content:
 */
#include "LEDdriver.h"
#include "LedPrograms.h"
#include <stdlib.h>

union {
    unsigned int counter;
    struct{
        char action;
        unsigned char time;
    };
}TimeValues[20];
unsigned char LEDtoggle[19][2];
unsigned char state=0;

void init_LEDdriver(void){

    // IO
    S1R1_tris = OUTPUT;
    S1G1_tris = OUTPUT;
    S1B1_tris = OUTPUT;
    S1R2_tris = OUTPUT;
    S1G2_tris = OUTPUT;
    S1B2_tris = OUTPUT;
    S1R3_tris = OUTPUT;
    S1G3_tris = OUTPUT;
    S1B3_tris = OUTPUT;
    S2R1_tris = OUTPUT;
    S2G1_tris = OUTPUT;
    S2B1_tris = OUTPUT;
    S2R2_tris = OUTPUT;
    S2G2_tris = OUTPUT;
    S2B2_tris = OUTPUT;
    S2R3_tris = OUTPUT;
    S2G3_tris = OUTPUT;
    S2B3_tris = OUTPUT;

    // Setup Timer 3 for Ledupdate
    T3CONbits.TCS = 0;      // clock source = internal clock
    #ifdef Mips30
        T3CONbits.TCKPS = 2;// prescaler: 1/64
        PR3 = 15555;        // Led update 30 Hz
    #elif defined(Mips20)
        T3CONbits.TCKPS = 2;// prescaler: 1/64
        PR3 = 10455;        // Led update 30 Hz
    #else
        T3CONbits.TCKPS = 1;// prescaler: 1/8
        PR3 = 41565;        // Led update 30 Hz
    #endif
    IPC1bits.T3IP = 2;      // Timer priority level 2 (low)
    IFS0bits.T3IF = 0;      // clear interrupt flag
    IEC0bits.T3IE = 1;      // enable timer 3 interruptss

    // Setup Timer 2 for LEDPWM
    T2CONbits.TCS = 0;      // clock source = internal clock
    T2CONbits.T32 = 0;      // 16 bit timer
    #ifdef Mips30             
        T2CONbits.TCKPS = 1;// prescaler: 1/8
    #elif defined(Mips20)
        T2CONbits.TCKPS = 1;// prescaler: 1/8
    #else
        T2CONbits.TCKPS = 0;// prescaler: 1
    #endif
    IPC1bits.T2IP = 5;      // Timer priority level 5
    IFS0bits.T2IF = 0;      // clear interrupt flag
    IEC0bits.T2IE = 1;      // enable timer 2 interruptss
    
    TimeValues[19].counter = EOP;  // always last
}
void __attribute__((__interrupt__, __shadow__, auto_psv)) _T3Interrupt(void){
    LedUpdate();        // update Ledstatus
    CI_LEDupdate();     // Reset interrupt flag
}

void setLEDColors(unsigned char colors[]){
    char action = 1;
    unsigned char previdx = 0;
    unsigned char defidx = 0;
    int time=0;
    int i;
    
    //char buffer[33];
    //unsigned int cycli;
    //T3CONbits.TCKPS = 0;
    //PR3 = 0xFFFF;
    //TMR3=0;
    //LEDupdateOn = 1;

    LEDtimerOn = 0; // stop LED timer
    // calculate interrupt times
    TimeValues[0].action = 1;
    TimeValues[0].time = 0;

    for (i=1;i<19;i++){
        if (colors[i-1]==0) setLedPin(i,0);   // set initial state
        if (colors[i-1]==255) setLedPin(i,1);
        time = (time+colors[i-1]) % 255;
        action++;
        TimeValues[i].action = action;
        TimeValues[i].time = time;
    }

    // sort interrupt times
    qsort(TimeValues, 19, sizeof(unsigned int), compare);

    // calculate actions
    if (TimeValues[18].time){    // if at least one LED is on
        for (i=1;i<20;i++){
            if (TimeValues[i].time!=TimeValues[previdx].time || TimeValues[i].action - TimeValues[i-1].action != 1){
                LEDtoggle[defidx][0] = TimeValues[previdx].action - 1;  // LEDoff
                LEDtoggle[defidx][1] = TimeValues[i-1].action;          // LEDon
                TimeValues[defidx].counter = (TimeValues[i].time-TimeValues[previdx].time) * LSBticks;
                defidx++;
                previdx = i;
            }
        }
        TimeValues[defidx].counter = EOP;

        // toggle TimeValues for interrupt LED timer
        state=0;
        LEDtimerOn = 1;
    }

    //test code
    //cycli=TMR3;
    //LEDupdateOn = 0;
    //clearLCD();
    //sprintf(buffer,"cycli: %u",cycli);
    //sprintf(buffer,"%4X %4X %4X  %4X %4X %4X",TimeValues[0].counter,TimeValues[1].counter,TimeValues[2].counter,
    //                                          TimeValues[3].counter,TimeValues[4].counter,TimeValues[5].counter);
    //sprintf(buffer,"%2d %2d %2d %2d %2d  %2d %2d %2d %2d %2d",LEDtoggle[0][0],LEDtoggle[1][0],LEDtoggle[2][0],LEDtoggle[3][0],LEDtoggle[4][0],
    //            LEDtoggle[0][1],LEDtoggle[1][1],LEDtoggle[2][1],LEDtoggle[3][1],LEDtoggle[4][1]);
    //appendStringToLCD(buffer);
}

int compare (const void * a, const void * b){// compare function
    if ( *(unsigned int*)a <  *(unsigned int*)b ) return -1;
    if ( *(unsigned int*)a >  *(unsigned int*)b ) return 1;
    return 0;
}

void __attribute__((__interrupt__, __shadow__, auto_psv)) _T2Interrupt(void){
    unsigned int nextInterval;
    
    do {
        setLedPin(LEDtoggle[state][0],0);           // set led off
        setLedPin(LEDtoggle[state][1],1);           // set led on
        nextInterval = TimeValues[state].counter;   // search next timer interval
        state++;                                    // increment state
        if (TimeValues[state].counter==EOP) state=0;
    } while (!nextInterval);                        // repeat for all action on same time
    
    LEDnextToggle = nextInterval;                   // set timer

    CI_LEDtimer();                                  // Reset interrupt flag
                                
}

void setLedPin(int LEDnumber, int state){
   switch (LEDnumber){
        case 1: S1R1=state; break;
        case 2: S1R2=state; break;
        case 3: S1R3=state; break;
        case 4: S1G1=state; break;
        case 5: S1G2=state; break;
        case 6: S1G3=state; break;
        case 7: S1B1=state; break;
        case 8: S1B2=state; break;
        case 9: S1B3=state; break;
        case 10: S2R1=state; break;
        case 11: S2R2=state; break;
        case 12: S2R3=state; break;
        case 13: S2G1=state; break;
        case 14: S2G2=state; break;
        case 15: S2G3=state; break;
        case 16: S2B1=state; break;
        case 17: S2B2=state; break;
        case 18: S2B3=state; break;
    }
}