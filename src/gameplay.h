#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "states.h"

#define X 0
#define Y 1

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 30

#define REFRESH_STEP 4
#define REFRESH_STEP_PX (8 * REFRESH_STEP)

#define REFRESH_RATE 20

#define BLOCKS 3

s32 scroll[2]; //px
s16 speed[2]; //px per frame

enum GameStates{
    GAMEINIT,
    GAME,
    GAMEENDING,
    GAMEEXIT
};

enum GameStates gameState;

void gameplayLoop();
void pollSection();
void refreshScene();

static inline void gameControls(u16 joy, u16 changed, u16 state){
    if(joy == JOY_1){
        if(state & BUTTON_LEFT){
            speed[X]++;
        }
        if(state & BUTTON_UP){
            speed[Y]++;
        }
        if(state & BUTTON_RIGHT){
            speed[X]--;
        }
        if(state & BUTTON_DOWN){
            speed[Y]--;
        }
        if(state & BUTTON_START){
            gameState = GAMEEXIT;
        }
    }
}

#endif