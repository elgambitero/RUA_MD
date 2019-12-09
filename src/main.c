#include <genesis.h>

#include "music.h"
#include "states.h"

#define PAL

#ifdef NTSC
    #define FRAMES 60
#elif
    #define FRAMES 50
#endif

int main()
{
    mainStates = INTRO;
    introStates = MADE_WITH_SGDK;

    SND_startPlay_XGM(intro_mus);

    while(1)
	{
        switch(mainStates){
            case INTRO:
                introPlay();
            break;
            case MAIN_MENU:

            break;
            case READY:

            break;
            case TRY_AGAIN:

            break;
            case GAMEPLAY:

            break;
            case GAME_OVER:

            break;
        }

		VDP_waitVSync();
	}
	return 0;
}