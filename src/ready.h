#ifndef READY_H
#define READY_H

#include "states.h"

enum ReadyStates{
    ENTRY,
    READY,
    EXIT,
};

enum ReadyStates readyState;

void readyLoop();

#endif