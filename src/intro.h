#ifndef INTRO_H
#define INTRO_H

#ifdef NTSC
    #define FADEFRAMES 20
#else
    #define FADEFRAMES 17
#endif

u16 introCount;

#ifdef NTSC
    static u16 introFrames[] = {120, 120, 120, 1};
#else
    static u16 introFrames[] = {100, 100, 100, 1};
#endif

void introPlay(u16* palette, u16 ind);

#endif