#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "states.h"

#define X 0
#define Y 1

s16 scroll[2];

enum GameStates{
    GAMEINIT,
    GAME,
    GAMEENDING,
    GAMEEXIT
};

enum GameStates gameState;

void gameplayLoop(u16 ind);

static inline void gameControls(u16 joy, u16 changed, u16 state){
    if(joy == JOY_1){
        if(state == BUTTON_LEFT){
            scroll[X]--;
        }
        if(state == BUTTON_UP){
            scroll[Y]++;
        }
        if(state == BUTTON_RIGHT){
            scroll[X]++;
        }
        if(state == BUTTON_DOWN){
            scroll[Y]--;
        }
        if(state == BUTTON_START){
            gameState = GAMEEXIT;
        }
    }
}

#endif