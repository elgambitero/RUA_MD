#ifndef INTRO_H
#define INTRO_H

#include "states.h"

#ifdef NTSC
    #define FADEFRAMES 20
#else
    #define FADEFRAMES 17
#endif

enum IntroStates{
    MADE_WITH_SGDK = 0,
    MUSIC_WITH_DEFLE,
    BASED_ON_RUA,
    FRAME
    };

enum IntroStates introState;

u16 introCount;

#ifdef NTSC
    static u16 introFrames[] = {180, 180, 180, 1};
#else
    static u16 introFrames[] = {150, 150, 150, 1};
#endif

void introPlay(u16* palette, u16 ind);

static inline void introControls(u16 joy, u16 changed, u16 state){
    if(state){
        introCount = 1;
    }
}

#endif