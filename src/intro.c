#include <genesis.h>

#include "intro.h"

#include "intro_gfx.h"


void introPlay(u16* palette, u16 ind){
    switch(introState)
    {
        case MADE_WITH_SGDK:
            //entry
            if(introCount == (introFrames[introState])){
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
                introState = MUSIC_WITH_DEFLE;
                introCount = introFrames[introState];
            }         
        break;
        case MUSIC_WITH_DEFLE:
            if(introCount == (introFrames[introState])){
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
                introState = BASED_ON_RUA;
                introCount = introFrames[introState];
            } 
        break;
        case BASED_ON_RUA:
            if(introCount == (introFrames[introState])){
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
                introState = FRAME;
                introCount = introFrames[introState];
            }   
        break;
        case FRAME:
            if(introCount == (introFrames[FRAME])){
                VDP_setPaletteColor(15, 0x000);
                VDP_drawText("Hey!", 20, 5);
                VDP_drawText("Want to really play this", 8, 7);
                VDP_drawText("game that was illegally", 9, 9);
                VDP_drawText("stolen from Adult Swim?", 9, 11);
                VDP_setPaletteColor(15, 0xFFF);

            }
            if(introCount) {
                introCount--;
                return;
            }
            else{
                VDP_clearPlan(PLAN_A, TRUE);
                VDP_interruptFade();
                mainState = MAIN_MENU;
                introState = MADE_WITH_SGDK;
            }   
        break;
    }
}