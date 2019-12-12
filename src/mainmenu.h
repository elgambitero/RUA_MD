#ifndef MAINMENU_H
#define MAINMENU_H

#include "states.h"

void mainMenu();

static inline void menuControls(u16 joy, u16 changed, u16 state){
    if(state){
        mainStates = MAIN_MENU;
    }
}

#endif