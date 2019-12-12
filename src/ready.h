#ifndef READY_H
#define READY_H

#include "states.h"

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