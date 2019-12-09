#include <genesis.h>
#include "intro.h"
#include "states.h"
#include "intro_gfx.h"



void introPlay(u16* palette, u16 ind){
    switch(introStates)
    {
        case MADE_WITH_SGDK:
            //entry
            if(introCount == (introFrames[MADE_WITH_SGDK] - FADEFRAMES)){
                ind = TILE_USERINDEX;
                VDP_drawImageEx(PLAN_B, &sgdk_logo, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 5, 7, FALSE, TRUE);
                
                // prepare palettes
                memcpy(palette, sgdk_logo.palette->data, 16 * 2);
                ind += sgdk_logo.tileset->numTile;

                //Fade in all the pallets
                VDP_fadeIn(0, (4 * 16) - 1, palette, FADEFRAMES, FALSE);
            }

            if(introCount)
            {
                introCount--;
                return;
            }
            //exit
            else
            {/*
                memcpy(palette, sgdk_logo.palette->data, 16 * 2);
                VDP_setPalette(PAL0, palette);
                VDP_fadeOutAll(FADEFRAMES, TRUE);*/
                VDP_clearPlan(PLAN_B, TRUE);
                introStates = MUSIC_WITH_DEFLE;
                introCount = introFrames[introStates];
            }         
        break;
        case MUSIC_WITH_DEFLE:
            if(introCount--) {
                return;
            }
            else{
                introStates = BASED_ON_RUA;
                introCount = introFrames[introStates];
            }   
        break;
        case BASED_ON_RUA:
            if(introCount--) {
                return;
            }
            else{
                introStates = FRAME;
                introCount = introFrames[introStates];
            }   
        break;
        case FRAME:
            if(introCount--) {
                return;
            }
            else{
                mainStates = MAIN_MENU;
            }   
        break;
    }
}