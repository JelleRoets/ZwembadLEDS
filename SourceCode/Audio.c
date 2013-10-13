/*
 * File:   Audio.h
 * Author: Jelle
 *
 * Created on 1 augustus 2013, 0:40
 *
 * Content: audio system
 */

#include "Audio.h"

void initAudio(void){

    // IO Tris:
    AudioOff_tris = OUTPUT;
    AudioChan1_tris = INPUT;
    AudioChan2_tris = INPUT;
    Audio_CS_tris = OUTPUT;
    SPI_SDI_tris = INPUT;
    SPI_SDO_tris = OUTPUT;
    SPI_SCK_tris = OUTPUT;

    AudioOff = 1;        // power off audio system
    Audio_CS = 1;       // CS idles high

}
