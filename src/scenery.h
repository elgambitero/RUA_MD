#ifndef SCENERY_H
#define SCENERY_H

#include <genesis.h>

#include "scenery_gfx.h"

typedef struct{
    s16 x, y;
    const Image * image;
    struct Section * next;
}Section;

const Section section_1 = {0, 50, &tile194, 0};

#endif 
