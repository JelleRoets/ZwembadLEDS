/* 
 * File:   Initialisations.c
 * Author: Jelle
 *
 * Created on 28 juli 2013, 21:57
 *
 * Content: configuration routines
 */
#include "p30F6012A.h"
#include "Initialisations.h"

// MCU Config
#ifdef Mips30             // MCU: HS/2 w/PLL 16x => 30 MIPS
    _FOSC(CSW_FSCM_OFF & HS2_PLL16);
#elif defined(Mips20)       // MCU: HS/3 w/PLL 16x => 20 MIPS
    _FOSC(CSW_FSCM_OFF & HS3_PLL16);
#else                       // MCU: HS/3 w/PLL 8x => 10 MIPS
    _FOSC(CSW_FSCM_OFF & HS3_PLL8);
#endif
_FWDT(WDT_OFF);                         // Turn off the Watch-Dog Timer.
_FBORPOR(MCLR_EN & PWRT_OFF & BORV_42); // Enable MCLR reset pin, turn off the power-up timers, Brownout reset at 4.2V
_FGS(CODE_PROT_OFF);                    // Disable Code Protection

void init() {
    // PORT directions
    ADPCFG = 0xFFFF; 		//Make all inputs digital

    // General IO
    LEDred_tris = OUTPUT;
    LEDorange_tris = OUTPUT;
    LEDgreen_tris = OUTPUT;
    BUTTONup_tris = INPUT;
    BUTTONdown_tris = INPUT;
    BUTTONenter_tris = INPUT;
    PowerLow_tris = INPUT;
    PowerEn_tris = OUTPUT;
    Sense12V_tris = INPUT;

    init_LEDdriver();
    initLCD();
    initAudio();
}