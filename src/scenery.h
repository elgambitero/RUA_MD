#ifndef SCENERY_H
#define SCENERY_H

#include <genesis.h>

#include "scenery_gfx.h"

typedef struct Section{
    s32 pos[2];
    const Image * image;
    const struct Section * next;
} Section ;

const Section section_1 = {{0, 0}, &tile194, 0};

const Section section_2 = {{0, 0}, &tile192, 0};

const Section section_3 = {{0, 0}, &tile195, 0};

const Section section_4 = {{0, 0}, &tile197, 0};

const Section section_5 = {{0, 0}, &tile198, 0};

const Section section_6 = {{0, 0}, &tile200, 0};

const Section *sections[] = {&section_1, 
                            &section_2, 
                            &section_3, 
                            &section_4, 
                            &section_5,
                            &section_6};

#endif 
