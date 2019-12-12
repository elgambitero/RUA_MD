#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "states.h"

void gameplayLoop();

inline void gameControls(u16 joy, u16 changed, u16 state){
    if(state){
        mainStates = MAIN_MENU;
    }
}

#endif