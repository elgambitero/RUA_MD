#ifndef INTRO_H
#define INTRO_H

#ifdef NTSC
    #define FADEFRAMES 20
#else
    #define FADEFRAMES 17
#endif

u16 introCount;

#ifdef NTSC
    static u16 introFrames[] = {180, 180, 180, 1};
#else
    static u16 introFrames[] = {150, 150, 150, 1};
#endif

void introPlay(u16* palette, u16 ind);

#endif