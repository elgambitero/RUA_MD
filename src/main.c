#include <genesis.h>

#include "music.h"
#include "states.h"
#include "intro.h"

#define PAL

#ifdef NTSC
    #define FRAMES 60
#else
    #define FRAMES 50
#endif

u16 palette[64];
u16 ind;

void game_init(){
    mainStates = INTRO;
    introStates = MADE_WITH_SGDK;
    introCount = (introFrames[MADE_WITH_SGDK] - FADEFRAMES);
    // set all palette to black
    VDP_setPaletteColors(0, (u16*) palette_black, 64);
}

int main()
{
    game_init();

    SND_startPlay_XGM(intro_mus);

    while(1)
	{
        switch(mainStates){
            case INTRO:
                introPlay(palette, ind);
            break;
            case MAIN_MENU:
                VDP_setPaletteColor(15, 0xFFF);
                VDP_drawText("Main Menu", 16, 13);
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
