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
    MADE_WITH_SGDK = 0,
    MUSIC_WITH_DEFLE,
    BASED_ON_RUA,
    FRAME
    };

enum IntroStates introStates;



#endif