#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "math.h"
#include "scenery.h"

s32 cam_pos[2]; //px
s32 drawn[2]; //px

const u8 margin[2] = { 80, 4 }; //px
Rect hRefresh;

u32 color = 0;

u16 secPos[2]; //px

const Section * currentSection;

u16 blockIndex[BLOCKS + 1];

u8 updateCount;

u8 sectionCount;

void pollSection(){
    currentSection = sections[RNGpoll() % (sizeof(sections)/sizeof(Section *))];

    secPos[X] = ( screenWidth + cam_pos[X]);
    secPos[Y] = ( ( screenHeight / 2 ) + cam_pos[Y] );

    const Section * secPtr = currentSection;
    
    u8 i = 1;
    while( secPtr ){
        blockIndex[i] = blockIndex[i-1];
        VDP_loadTileSet(secPtr->image->tileset, blockIndex[i], DMA);
        VDP_setPaletteColors(16, secPtr->image->palette->data, secPtr->image->palette->length);

        blockIndex[i] += secPtr->image->tileset->numTile;

        i++;
        secPtr = secPtr->next;
    }
    sectionCount = (sectionCount + 1) % (sizeof(sections)/sizeof(sections[0]));
}

void refreshScene(){
    const Section * secPtr = currentSection;

    hRefresh.left = cam_pos[X] + margin[X]; // + screenWidth;
    hRefresh.top = cam_pos[Y] - margin[Y];
    hRefresh.right = hRefresh.left + REFRESH_STEP_PX;
    hRefresh.bottom = hRefresh.top + ( 8 * planHeight );

    

    VDP_clearTileMapRect(PLAN_A,  ( hRefresh.left / 8 ) % planWidth, ( hRefresh.top / 8 ) % planHeight, 
        ( hRefresh.right - hRefresh.left ) / 8, ( hRefresh.bottom - hRefresh.top ) / 8);

    u8 i = 0;
    while ( secPtr ){
        
        Rect block;
        block.left = secPos[X] + secPtr->pos[X];
        block.top = secPos[Y] + secPtr->pos[Y];
        block.right = block.left + ( 8 * secPtr->image->map->w );
        block.bottom = block.top + ( 8 * secPtr->image->map->h );

        Rect inter = intersect(hRefresh, block);

        if( inter.left == 0 ) {i++; secPtr = secPtr->next; continue;}

        Box mapCrop;
        mapCrop.x = ( inter.left - block.left ) / 8;
        mapCrop.y = ( inter.top - block.top ) / 8;
        mapCrop.w = ( inter.right - inter.left ) / 8;
        mapCrop.h = ( inter.bottom - inter.top ) / 8;

        VDP_setMapEx(PLAN_A, secPtr->image->map, 
            TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[i]), 
            (inter.left / 8) % planWidth, ( inter.top / 8 ) % planHeight, 
            mapCrop.x, mapCrop.y,
            mapCrop.w, mapCrop.h );

        i++;
        secPtr = secPtr->next;
    }
    drawn[X] = cam_pos[X];
    drawn[Y] = cam_pos[Y];
}

void gameplayLoop(){
    switch(gameState){
        case GAMEINIT:
            SYS_disableInts();

            cam_pos[X] = 0;
            cam_pos[Y] = 0;
            speed[X] = 0;
            speed[Y] = 0;
            drawn[X] = 0;
            drawn[Y] = 0;

            for(register u8 i = 0; i <= BLOCKS; i++) blockIndex[i] = TILE_USERINDEX;

            XGM_startPlay(always_mus);

            gameState = GAME;
            updateCount = REFRESH_RATE;
            sectionCount = 0;

            VDP_drawImageEx(PLAN_B, &background, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, blockIndex[0]), 0, 0, TRUE, TRUE);
            VDP_setBackgroundColor(47);
            VDP_setPaletteColor(47, 0xF77);

            blockIndex[0] += background.tileset->numTile;

            pollSection();

            SYS_enableInts();
        break;
        case GAME:
            cam_pos[X] += speed[X];
            cam_pos[Y] += speed[Y];
            VDP_setHorizontalScroll(PLAN_A, -cam_pos[X]);
            VDP_setHorizontalScroll(PLAN_B, -cam_pos[X] / 2 );
            VDP_setVerticalScroll(PLAN_A,cam_pos[Y]);

            if( ( cam_pos[X] - drawn[X] ) >= REFRESH_STEP_PX ){
                refreshScene();
            }

            if( ( cam_pos[X] ) > secPos[X] + screenWidth + currentSection->image->map->w * 8 ){
                pollSection();
            }

        break;
        case GAMEENDING:

        break;
        case GAMEEXIT:
            VDP_clearPlan(PLAN_A, TRUE);
            VDP_clearPlan(PLAN_B, TRUE);
            VDP_clearPlan(PLAN_WINDOW, TRUE);

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