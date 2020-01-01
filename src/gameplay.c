#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "math.h"
#include "scenery.h"

//VDP_drawImageEx(PLAN_A, section.image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), _x, _y, TRUE, TRUE);

u16 drawn[2] = {0, 0}; //px
const u8 margin[2] = { 80, 4 }; //px
Rect hRefresh;


u16 secPos[2]; //px

const Section * currentSection;

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
    if( drawn[X] - scroll[X] > REFRESH_STEP_PX ){
        hRefresh.pos[X] = scroll[X] + screenWidth + margin[X];
        hRefresh.pos[Y] = scroll[Y] - margin[Y];
        u8 i = 0;
        while ( secPtr ){
            
            Rect block;
            block.pos[X] = secPos[X] + secPtr->pos[X];
            block.pos[Y] = secPos[Y] + secPtr->pos[Y];
            block.size[X] = 8 * secPtr->image->map->w;
            block.size[Y] = 8 * secPtr->image->map->h;

            Rect inter = intersect(hRefresh, block);
            
            if(inter.size[X] < 0 || inter.size[Y] < 0) continue;

            Rect mapCrop;
            mapCrop.pos[X] = ( inter.pos[X] - block.pos[X] ) / 8;
            mapCrop.pos[Y] = ( inter.pos[Y] - block.pos[Y] ) / 8;
            mapCrop.size[X] = inter.size[X] / 8;
            mapCrop.size[Y] = inter.size[Y] / 8;
            
            VDP_setMapEx(PLAN_A, secPtr->image->map, 
                TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[i]), 
                inter.pos[X] % planWidth, inter.pos[Y] % planHeight, 
                mapCrop.pos[X], mapCrop.pos[Y],
                mapCrop.size[X], mapCrop.size[Y] );
            
            drawn[X] = scroll[X];
            drawn[Y] = scroll[Y];
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

            hRefresh.pos[X] = 0;
            hRefresh.pos[Y] = 0;
            hRefresh.size[X] = REFRESH_STEP_PX;
            hRefresh.size[Y] = planHeight;

            XGM_startPlay(always_mus);

            gameState = GAME;
            updateCount = REFRESH_RATE;

            VDP_drawImageEx(PLAN_B, &background, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, blockIndex[0]), 0, 0, TRUE, TRUE);
            VDP_setBackgroundColor(47);
            VDP_setPaletteColor(47, 0xF77);

            blockIndex[0] += background.tileset->numTile;

            pollSection();

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