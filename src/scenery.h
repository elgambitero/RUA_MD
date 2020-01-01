#ifndef SCENERY_H
#define SCENERY_H

#include <genesis.h>

#include "scenery_gfx.h"

typedef struct Section{
    s16 pos[2];
    const Image * image;
    const struct Section * next;
} Section ;

const Section section_1 = {{0, 0}, &tile194, 0};

const Section section_2 = {{0, 0}, &tile192, 0};

const Section section_3_1 = {{0, -50}, &tile194, 0};
const Section section_3 = {{0, 0}, &tile192, &section_3_1};

#endif 
