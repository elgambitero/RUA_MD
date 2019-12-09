#ifndef STATES_H
#define STATES_H

enum MainStates{INTRO,
    MAIN_MENU,
    READY,
    TRY_AGAIN,
    GAMEPLAY,
    GAME_OVER
    };

enum MainStates mainStates;

enum IntroStates{
    MADE_WITH_SGDK,
    MUSIC_WITH_DEFLE,
    BASED_ON_RUA,
    FRAME
    };

enum introStates introStates;

#ifdef NTSC
    static u16 introFrames[] = {120, 120, 120, 1};
#elif
    static u16 introFrames[] = {100, 100, 100, 1};
#endif

#endif