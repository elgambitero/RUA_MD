#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "math.h"
#include "scenery.h"

//VDP_drawImageEx(PLAN_A, section.image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), _x, _y, TRUE, TRUE);

u16 drawn[2] = {0, 0}; //px
const u8 margin[2] = { 80, 4 }; //px

u16 secPos[2]; //px

const Section * currentSection;
u16 ind;

s16 blockPos[2];
s16 cropPos[2];
u16 cropPos_map[2];
u16 cropSize[2];

u8 updateCount;

void pollSection(){
    if(currentSection == &section_1) currentSection = &section_2;
    else currentSection = &section_1;
    secPos[X] = ( screenWidth + scroll[X] ) % ( 8 * planWidth );
    secPos[Y] = ( ( screenHeight / 2 ) + scroll[Y] ) % ( 8 * planHeight );
}

void refreshScene(){
    const Section * secPtr = currentSection;
    if( ( scroll[X] + screenWidth + margin[X] ) % ( 8 * planWidth ) > drawn[X]){
        while ( secPtr ){

            blockPos[X] = secPos[X] + secPtr->x;
            blockPos[Y] = secPos[Y] + secPtr->y;
            if( blockPos[X] + planWidth > ( drawn[2] / 8 ) + planWidth || 
                blockPos[X] + secPtr->image->map->w + planWidth < ( drawn[2] / 8 ) + planWidth ){
                    continue;
                }
            cropPos[X] = drawn[X] / 8;
            cropPos[Y] = ( drawn[Y] + margin[Y] ) / 8;
            cropPos_map[X] = cropPos[X] - blockPos[X];
            cropPos_map[Y] = cropPos[Y] - blockPos[Y];
            cropSize[X] = saturate(secPtr->image->map->w - cropPos_map[X], 0, REFRESH_STEP);
            cropSize[Y] = saturate(secPtr->image->map->h - cropPos_map[Y], 0, planHeight);
            
            VDP_setMapEx(PLAN_A, secPtr->image->map, 
                TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 
                cropPos[X], cropPos[Y], 
                cropPos_map[X], cropPos_map[Y],
                cropSize[X], cropSize[Y]);
            
            drawn[X] = ( drawn[X] + ( 8 * REFRESH_STEP ) ) % ( 8 * planHeight );
            ind += REFRESH_STEP + planHeight;
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
            speed[X] = 0;
            speed[Y] = 0;
            XGM_startPlay(always_mus);
            pollSection();
            gameState = GAME;
            updateCount = REFRESH_RATE;
            VDP_drawImageEx(PLAN_B, &tile125, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, TRUE);
            VDP_setBackgroundColor(47);
            VDP_setPaletteColor(47, 0xF77);

            SYS_enableInts();
        break;
        case GAME:
            scroll[X] += speed[X];
            scroll[Y] += speed[Y];
            VDP_setHorizontalScroll(PLAN_A, scroll[X]);
            VDP_setHorizontalScroll(PLAN_B, scroll[X] / 2);
            VDP_setVerticalScroll(PLAN_A,scroll[Y]);
            if( !updateCount ) { refreshScene(); updateCount--; }
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
            VDP_setBackgroundColor(0);

            gameState = GAMEINIT;
            mainState = MAIN_MENU;
            XGM_startPlay(intro_mus);
        break;
    }
}