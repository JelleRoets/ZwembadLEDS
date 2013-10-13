#include "p30F6012A.h"
#include "Initialisations.h"

// main
int main(int argc, char** argv) {
    int i;

    init();         // configure the microcontroller
    LEDgreen=1;

    backlightOn();
    clearLCD();
    appendStringToLCD("Hello World 2");
    S1R1 = 1;
    while(1){
        LEDgreen=!LEDgreen;
        LEDorange=!LEDorange;
        setColor(i++,TRUE);
        if (i==9) i=0;
        __delay_ms(250);
    };
    return (EXIT_SUCCESS);
}

