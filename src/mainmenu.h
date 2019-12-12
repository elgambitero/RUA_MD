#ifndef MAINMENU_H
#define MAINMENU_H

#include "states.h"

enum MenuStates{
    MENUENTRY,
    MENU,
    MENUEXIT,
};

enum MenuStates menuState;

void mainMenu();

static inline void menuControls(u16 joy, u16 changed, u16 state){
    if(state){
        menuState = MENUEXIT;
    }
}

#endif