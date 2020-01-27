#include <genesis.h>

#include "gameplay.h"

#include "music.h"
#include "math.h"
#include "scenery.h"

s32 world_pos[2]; //px
s32 drawn[2]; //px
s32 sec_pos[2]; //px
u16 sec_plan_pos[2]; //tile
u16 cross[2]; //tile
u16 map_drawn[2]; //tile

const u8 margin[2] = { 80, 4 }; //px
Rect hRefresh;

u32 color = 0;

const Section * currentSection;

u16 blockIndex[BLOCKS + 1];

u8 updateCount;

u8 sectionCount;

void pollSection(){
    currentSection = sections[RNGpoll() % (sizeof(sections)/sizeof(Section *))];

    sec_pos[X] = ( screenWidth + world_pos[X] );
    sec_pos[Y] = ( ( screenHeight / 2 ) + world_pos[Y] );

    sec_plan_pos[X] = ( sec_pos[X] / 8 ) % planWidth;
    sec_plan_pos[Y] = ( sec_pos[Y] / 8 ) % planHeight;

    cross[X] = planWidth - sec_plan_pos[X];
    cross[Y] = planHeight - sec_plan_pos[Y];

    map_drawn[X] = 0;
    map_drawn[Y] = 0;

    blockIndex[1] = blockIndex[0];
    VDP_loadTileSet(currentSection->image->tileset, blockIndex[1], DMA);
    VDP_setPaletteColors(16, currentSection->image->palette->data, currentSection->image->palette->length);

    blockIndex[1] += currentSection->image->tileset->numTile;

    sectionCount = (sectionCount + 1) % (sizeof(sections)/sizeof(sections[0]));
}

//TODO: RETHINK THIS!
void refreshScene(){
    u16 current_cross[2];

    //horizontal case

    VDP_clearTileMapRect(PLAN_A, ( world_pos[X] / 8 ) & 0x7F, 0,
        REFRESH_STEP, planHeight);

    current_cross[Y] = map_drawn[Y];
    if( map_drawn[X] < currentSection->image->map->w){
        /*
        if( cross[Y] > map_drawn[Y] && cross[Y] - map_drawn[Y] < planHeight){
            current_cross[Y] = cross[Y];

            VDP_setMapEx(PLAN_A, currentSection->image->map,
                TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[0]),
                sec_plan_pos[X] + map_drawn[X], sec_plan_pos[Y] + map_drawn[Y],
                map_drawn[X], map_drawn[Y],
                REFRESH_STEP, cross[Y] - map_drawn[Y] );

        }
        */
        VDP_setMapEx(PLAN_A, currentSection->image->map,
                TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, blockIndex[0]),
                sec_plan_pos[X] + map_drawn[X], sec_plan_pos[Y] + current_cross[Y],
                map_drawn[X], current_cross[Y],
                REFRESH_STEP, planHeight - current_cross[Y] + map_drawn[Y] );
    }
    map_drawn[X] += REFRESH_STEP;
    /*
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
    */
    drawn[X] = world_pos[X];
    drawn[Y] = world_pos[Y];
}

void gameplayLoop(){
    switch(gameState){
        case GAMEINIT:
            SYS_disableInts();

            world_pos[X] = 0;
            world_pos[Y] = 0;
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
            world_pos[X] += speed[X];
            world_pos[Y] += speed[Y];
            VDP_setHorizontalScroll(PLAN_A, -world_pos[X]);
            VDP_setHorizontalScroll(PLAN_B, -world_pos[X] / 2 );
            VDP_setVerticalScroll(PLAN_A,world_pos[Y]);
            
            //TODO: Start fixing logic here.
            if( ( world_pos[X] - drawn[X] ) >= REFRESH_STEP_PX ){
                refreshScene();
            }

            if( ( world_pos[X] ) > sec_pos[X] + screenWidth + currentSection->image->map->w * 8 ){
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