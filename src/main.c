#include <genesis.h>

#include "states.h"
#include "intro.h"
#include "mainmenu.h"
#include "ready.h"
#include "gameplay.h"

#include "music.h"

#define PAL

#ifdef NTSC
    #define FRAMES 60
#else
    #define FRAMES 50
#endif

u16 palette[64];
u16 ind;

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1){
        switch(mainState){
            case INTRO:
                introControls(joy, changed, state);
            break;
            case MAIN_MENU:
                menuControls(joy, changed, state);
            break;
            case READY:
                return;
            break;
            case TRY_AGAIN:
                //continueControls();
            break;
            case GAMEPLAY:
                gameControls(joy, changed, state);
            break;
            case GAME_OVER:
                //overControls();
            break;
        }
    }
}

void game_init(){

    SYS_disableInts();

    JOY_init();
    JOY_setEventHandler( &myJoyHandler );
    VDP_setScreenWidth320();
    mainState = INTRO;
    menuState = MENUENTRY;
    readyState = READYENTRY;
    gameState = GAMEINIT;
    introState = MADE_WITH_SGDK;
    introCount = (introFrames[MADE_WITH_SGDK]);
    // set all palette to black
    VDP_setPaletteColors(0, (u16*) palette_black, 64);

    SYS_enableInts();
}

int main()
{
    game_init();

    XGM_startPlay(intro_mus);

    while(1)
	{
        switch(mainState){
            case INTRO:
                introPlay(palette, ind);
            break;
            case MAIN_MENU:
                mainMenu();
            break;
            case READY:
                readyLoop(palette);
            break;
            case TRY_AGAIN:

            break;
            case GAMEPLAY:
                gameplayLoop(ind);
            break;
            case GAME_OVER:

            break;
        }

		VDP_waitVSync();
	}
	return 0;
}
