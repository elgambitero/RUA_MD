#ifndef SCENERY_H
#define SCENERY_H

#include <genesis.h>

#include "scenery_gfx.h"

typedef struct{
    s16 x, y;
    const Image * image;
    struct Section * next;
}Section;

const Section section_1 = {0, 0, &tile194, 0};
const Section section_2 = {0, 0, &tile192, 0};

#endif 
