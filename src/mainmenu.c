#include <genesis.h>

#include "mainmenu.h"

#include "sound.h"

void mainMenu(){
    switch(menuState){
        case MENUENTRY:
            VDP_setPaletteColor(15, 0xFFF);
            VDP_drawText("Main Menu", 16, 13);
            XGM_setPCM(BELL_ID, bell, sizeof(bell));
            XGM_startPlayPCM(BELL_ID, 0, SOUND_PCM_CH2);
            menuState = MENU;
        break;
        case MENU:

        break;
        case MENUEXIT:
            VDP_clearPlan(PLAN_A, TRUE);
            menuState = MENUENTRY;
            mainState = READY;
        break;
    }
}