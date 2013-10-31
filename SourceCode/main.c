#include "p30F6012A.h"
#include "Initialisations.h"

// main

int main(int argc, char** argv) {

    init();         // configure the microcontroller
    LEDgreen=1;
    LEDupdateOn = 1;    // put 30 Hz Ledupdater on

    backlightOn();
    clearLCD();
    appendStringToLCD("Welcome to superasem LED world!");

    // Green Board LED blinking
    while(1){
        LEDgreen = !LEDgreen;
        __delay_ms(500);
    };
    return (EXIT_SUCCESS);
}

