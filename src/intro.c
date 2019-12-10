#include <genesis.h>
#include "intro.h"
#include "states.h"
#include "intro_gfx.h"


void introPlay(u16* palette, u16 ind){
    switch(introStates)
    {
        case MADE_WITH_SGDK:
            //entry
            if(introCount == (introFrames[MADE_WITH_SGDK])){
                VDP_setPaletteColor(15, 0x000);
                VDP_drawText("A game ported with", 7, 5);
                ind = TILE_USERINDEX;
                VDP_drawImageEx(PLAN_A, &sgdk_logo, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 5, 7, FALSE, TRUE);
                
                // prepare palette for fade.
                palette[15] = 0xFFF;
                memcpy(palette + (1 * 16), sgdk_logo.palette->data, 16);
                ind += sgdk_logo.tileset->numTile;

                //Fade in PAL1 plus the text color
                VDP_fadeIn(0, (2 * 16) - 1, palette, FADEFRAMES, TRUE);           
            }
            if(introCount)
            {
                introCount--;
                if(introCount == FADEFRAMES) VDP_fadeOutAll(FADEFRAMES, TRUE);
                return;
            }
            //exit
            else
            {
                VDP_clearPlan(PLAN_A, TRUE);
                introStates = MUSIC_WITH_DEFLE;
                introCount = introFrames[introStates];
            }         
        break;
        case MUSIC_WITH_DEFLE:
            if(introCount == (introFrames[MADE_WITH_SGDK])){
                VDP_setPaletteColor(15, 0x000);
                VDP_drawText("Original OST by Erasure", 8, 10);
                VDP_drawText("Music sequenced with DefleMask", 5, 13);
                 //Fade in PAL1 plus the text color
                VDP_fadeIn(0, 31, palette, FADEFRAMES, TRUE);

            }
            if(introCount) {
                introCount--;
                if(introCount == FADEFRAMES) VDP_fadeOutAll(FADEFRAMES, TRUE);
                return;
            }
            else{
                 // fade text
                VDP_fadeOut(15, 15, 30, FALSE);
                // clear text
                VDP_clearPlan(PLAN_A, TRUE);
                introStates = BASED_ON_RUA;
                introCount = introFrames[introStates];
            } 
        break;
        case BASED_ON_RUA:
            if(introCount == (introFrames[MADE_WITH_SGDK])){
                VDP_setPaletteColor(15, 0x000);
                VDP_drawText("Based on the flash game by Adult Swim", 1, 13);
                 //Fade in PAL1 plus the text color
                VDP_fadeIn(0, 31, palette, FADEFRAMES, TRUE);

            }
            if(introCount) {
                introCount--;
                if(introCount == FADEFRAMES) VDP_fadeOutAll(FADEFRAMES, TRUE);
                return;
            }
            else{
                VDP_clearPlan(PLAN_A, TRUE);
                introStates = FRAME;
                introCount = introFrames[introStates];
            }   
        break;
        case FRAME:
            if(introCount == (introFrames[MADE_WITH_SGDK])){
                VDP_setPaletteColor(15, 0x000);
                VDP_drawText("Main Menu", 16, 13);
                 //Fade in PAL1 plus the text color
                VDP_fadeIn(0, 31, palette, FADEFRAMES, TRUE);

            }
            if(introCount) {
                introCount--;
                if(introCount == FADEFRAMES) VDP_fadeOutAll(FADEFRAMES, TRUE);
                return;
            }
            else{
                VDP_clearPlan(PLAN_A, TRUE);
                mainStates = MAIN_MENU;
            }   
        break;
    }
    return;
}