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

s16 blockPos[2];
s16 cropPos[2];
u16 cropPos_map[2];
u16 cropSize[2];

u16 blockIndex[BLOCKS + 1] = {TILE_USERINDEX, TILE_USERINDEX, TILE_USERINDEX, TILE_USERINDEX};

u8 updateCount;

void pollSection(){
    if(currentSection == &section_1) currentSection = &section_2;
    else currentSection = &section_1;
    secPos[X] = ( screenWidth + scroll[X] );
    secPos[Y] = ( ( screenHeight / 2 ) + scroll[Y] );
    const Section * secPtr = currentSection;
    u8 i = 1;
    while( secPtr ){
        blockIndex[i] = blockIndex[i-1];
        VDP_loadTileSet(secPtr->image->tileset, blockIndex[i], CPU);
        VDP_setPaletteColors(16, secPtr->image->palette->data, secPtr->image->palette->length);

        /*
        VDP_setMapEx(PLAN_A, secPtr->image->map, 
            TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[i]), 
            10, 10, 
            0, 0,
            10, 10);
        */

        blockIndex[i] += secPtr->image->tileset->numTile;

        

        i++;
        secPtr = secPtr->next;
    }
}

void refreshScene(){
    const Section * secPtr = currentSection;
    if( ( scroll[X] + screenWidth + margin[X] ) > drawn[X] ){
        u8 i = 0;
        while ( secPtr ){

            blockPos[X] = secPos[X] + secPtr->x;
            blockPos[Y] = secPos[Y] + secPtr->y;
            /*
            if( blockPos[X] + planWidth > ( drawn[2] / 8 ) + planWidth || 
                blockPos[X] + secPtr->image->map->w + planWidth < ( drawn[2] / 8 ) + planWidth ){
                    secPtr = secPtr->next;
                    continue;
                }
                */
            cropPos[X] = drawn[X] / 8;
            cropPos[Y] = ( drawn[Y] + margin[Y] ) / 8;
            cropPos_map[X] = cropPos[X] - blockPos[X];
            cropPos_map[Y] = cropPos[Y] - blockPos[Y];
            cropSize[X] = saturate(secPtr->image->map->w - cropPos_map[X], 0, REFRESH_STEP);
            cropSize[Y] = saturate(secPtr->image->map->h - cropPos_map[Y], 0, planHeight);
            
            VDP_setMapEx(PLAN_A, secPtr->image->map, 
                TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[i]), 
                cropPos[X] % planWidth, cropPos[Y] % planHeight, 
                0, 0,
                10, 10);
                /*
                cropPos_map[X], cropPos_map[Y],
                cropSize[X], cropSize[Y]);
                */
            
            drawn[X] += ( 8 * REFRESH_STEP );
            i++;
            secPtr = secPtr->next;
        }
    }
}

void gameplayLoop(){
    switch(gameState){
        case GAMEINIT:
            SYS_disableInts();

            scroll[X] = 0;
            scroll[Y] = 0;
            speed[X] = 0;
            speed[Y] = 0;
            drawn[X] = planWidth * 4;
            XGM_startPlay(always_mus);
            gameState = GAME;
            updateCount = REFRESH_RATE;
            VDP_drawImageEx(PLAN_B, &background, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, blockIndex[0]), 0, 0, TRUE, TRUE);
            blockIndex[0] += background.tileset->numTile;

            pollSection();
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
            VDP_setBackgroundColor(0);

            gameState = GAMEINIT;
            mainState = MAIN_MENU;
            XGM_startPlay(intro_mus);
        break;
    }
}