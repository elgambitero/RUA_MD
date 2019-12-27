#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "scenery.h"

const Section * currentSection;
u16 ind;

//VDP_drawImageEx(PLAN_A, section.image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), _x, _y, TRUE, TRUE);

void pollSection(){
    if(currentSection == &section_1) currentSection = &section_2;
    else currentSection = &section_1;
}

void refreshScene(){
    const Section * secPtr = currentSection;
    if(scroll[X] + screenWidth + margin[X] > drawn[X]){
        while ( secPtr ){
            u16 VDP_setMapEx(VDPPlan plan, const Map *map, u16 basetile, u16 x, u16 y, u16 xm, u16 ym, u16 wm, u16 hm)
            secPtr = secPtr->next;
        }
    }
}

void gameplayLoop(){
    switch(gameState){
        case GAMEINIT:
            SYS_disableInts();

            ind = TILE_USERINDEX;
            scroll[X] = 0;
            scroll[Y] = 0;
            XGM_startPlay(always_mus);
            pollSection();
            gameState = GAME;

            SYS_enableInts();
        break;
        case GAME:
            scroll[X] += speed[X];
            scroll[Y] += speed[Y];
            VDP_setHorizontalScroll(PLAN_A, scroll[X]);
            VDP_setVerticalScroll(PLAN_A,scroll[Y]);
            refreshScene();
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