#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "states.h"

#define X 0
#define Y 1

s16 scroll[2];
s16 speed[2];

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
            speed[X]--;
        }
        if(state == BUTTON_UP){
            speed[Y]++;
        }
        if(state == BUTTON_RIGHT){
            speed[X]++;
        }
        if(state == BUTTON_DOWN){
            speed[Y]--;
        }
        if(state == BUTTON_START){
            gameState = GAMEEXIT;
        }
    }
}

#endif