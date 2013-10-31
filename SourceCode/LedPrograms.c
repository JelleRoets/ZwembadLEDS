/*
 * File:   LedPrograms.c
 * Author: Jelle
 *
 * Created on 29 juli 2013, 0:25
 *
 * Content:
 */

#include "LedPrograms.h"


void LedUpdate(void){       // Update LED status: executed every 30 Hz

    static int j=0;
    static int k=0;
    unsigned char colors[18]={0};
    
    k+=2;
    if (k>100){
        k=0;
        j++;
        if (j>=9) j=0;
    }
                
    colors[j]=k;
    
    setLEDColors(colors);
}