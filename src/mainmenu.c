#include <genesis.h>

#include "mainmenu.h"

void mainMenu(){
    switch(menuState){
        case ENTRY:
            VDP_setPaletteColor(15, 0xFFF);
            VDP_drawText("Main Menu", 16, 13);
            menuState = MENU;
        break;
        case MENU:

        break;
        case EXIT:

        break;
    }
}