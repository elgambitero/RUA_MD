#include <genesis.h>

#include "ready.h"

u16 readyFrames;

void readyLoop(u16 * palette){
    switch(readyState){
        case READYENTRY:
            VDP_setPaletteColor(15, 0x000);
            VDP_drawText("Ready?", 16, 13);
            palette[15] = 0xFFF;
            VDP_fadeIn(15, 15, palette, READYFADE, TRUE);
            readyState = READY_FADE_IN;
        break;
        case READY_FADE_IN:
            if(VDP_isDoingFade()) {
                return;
            }
            else {
                readyState = READYLOOP;
                readyFrames = READYFRAMES;
            }
        break;
        case READYLOOP:
            if(readyFrames--) return;
            else {
                VDP_fadeOut(15,15,READYFADE,TRUE);
                readyState = READY_FADE_OUT;
            }
        break;
        case READY_FADE_OUT:
            if(VDP_isDoingFade()) {
                return;
            }
            else {
                readyState = READYEXIT;
            }
        break;
        case READYEXIT:
            mainState = MAIN_MENU;
        break;
    }
}