#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "scenery.h"

void gameplayLoop(u16 ind){
    switch(gameState){
        case GAMEINIT:
            scroll[X] = 0;
            scroll[Y] = 0;
            XGM_startPlay(always_mus);
            VDP_drawImageEx(PLAN_A, section_1.image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, TRUE);
            gameState = GAME;
        break;
        case GAME:
            scroll[X] += speed[X];
            scroll[Y] += speed[Y];
            VDP_setHorizontalScroll(PLAN_A, scroll[X]);
            VDP_setVerticalScroll(PLAN_A,scroll[Y]);
        break;
        case GAMEENDING:

        break;
        case GAMEEXIT:
            VDP_clearPlan(PLAN_A, TRUE);
            VDP_clearPlan(PLAN_B, TRUE);

            VDP_setHorizontalScroll(PLAN_A, 0);
            VDP_setHorizontalScroll(PLAN_B, 0);
            VDP_setVerticalScroll(PLAN_A, 0);
            VDP_setVerticalScroll(PLAN_B, 0);

            gameState = GAMEINIT;
            mainState = MAIN_MENU;
            XGM_startPlay(intro_mus);
        break;
    }
}