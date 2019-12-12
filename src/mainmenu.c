#include <genesis.h>

#include "mainmenu.h"

void mainMenu(){
    VDP_setPaletteColor(15, 0xFFF);
    VDP_drawText("Main Menu", 16, 13);
}