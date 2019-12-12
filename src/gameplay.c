#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "scenery.h"

void gameplayLoop(u16 ind){
    switch(gameState){
        case GAMEINIT:
            scroll[X] = 0;
            scroll[Y] = 1;
            XGM_startPlay(always_mus);
            VDP_drawImageEx(PLAN_A, &tile194, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, TRUE);
            gameState = GAME;
        break;
        case GAME:
            VDP_setHorizontalScroll(PLAN_A, scroll[X]);
        break;
        case GAMEENDING:

        break;
        case GAMEEXIT:
            VDP_clearPlan(PLAN_A, TRUE);
            VDP_clearPlan(PLAN_B, TRUE);
            gameState = GAMEINIT;
            mainState = MAIN_MENU;
            XGM_startPlay(intro_mus);
        break;
    }
}