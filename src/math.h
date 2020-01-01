#ifndef MATH_H
#define MATH_H

#include <genesis.h>

#define X 0
#define Y 1

typedef struct Rect{
    u32 pos[2];
    u16 size[2];
} Rect;

Rect intersect(Rect a, Rect b);

u16 saturate(u16 num, u16 min, u16 max);

#endif