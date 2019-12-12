#ifndef READY_H
#define READY_H

#include "states.h"

#ifdef NTSC
    #define READYFRAMES 120
    #define READYFADE 30
#else
    #define READYFRAMES 100
    #define READYFADE 25
#endif

enum ReadyStates{
    READYENTRY,
    READY_FADE_IN,
    READYLOOP,
    READY_FADE_OUT,
    READYEXIT,
};

enum ReadyStates readyState;

void readyLoop();

#endif