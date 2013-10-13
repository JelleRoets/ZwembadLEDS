/*
 * File:   LEDdriver.c
 * Author: Jelle
 *
 * Created on 29 juli 2013, 0:25
 *
 * Content:
 */
#include "LEDdriver.h"

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
}

void setColor(int idx,int slinger){
    S1R1 = 0 ;
    S1G1 = 0 ;
    S1B1 = 0 ;
    S1R2 = 0 ;
    S1G2 = 0 ;
    S1B2 = 0 ;
    S1R3 = 0 ;
    S1G3 = 0 ;
    S1B3 = 0 ;
    S2R1 = 0 ;
    S2G1 = 0 ;
    S2B1 = 0 ;
    S2R2 = 0 ;
    S2G2 = 0 ;
    S2B2 = 0 ;
    S2R3 = 0 ;
    S2G3 = 0 ;
    S2B3 = 0 ;

    if(slinger){
        switch (idx){
            case 0: S1R1 =1;break;
            case 1: S1R2 =1;break;
            case 2: S1R3 =1;break;
            case 3: S1G1 =1;break;
            case 4: S1G2 =1;break;
            case 5: S1G3 =1;break;
            case 6: S1B1 =1;break;
            case 7: S1B2 =1;break;
            case 8: S1B3 =1;break;
        }
    }
    else {
        switch (idx){
            case 0: S2R1 =1;break;
            case 1: S2G1 =1;break;
            case 2: S2B1 =1;break;
            case 3: S2R2 =1;break;
            case 4: S2G2 =1;break;
            case 5: S2B2 =1;break;
            case 6: S2R3 =1;break;
            case 7: S2G3 =1;break;
            case 8: S2B3 =1;break;
        }
    }

}
