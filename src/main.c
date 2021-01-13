#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <compression.h>
#include <fileioc.h>
#include <debug.h>
#include "gfx/DRAAK.h"
#include "gfx/DRAGAN.h"
#define APPVAR "DRGNLVL"
uint24_t about(uint24_t score){
    score++;
    gfx_BlitScreen(); //move the screen to the buffer.
    gfx_SetDrawScreen();
    gfx_FillScreen(255);
    gfx_PrintStringXY("DRAGONCE, a virtual dragon on your calculator!",1,1);
    gfx_PrintStringXY("I really want to thank:",1,26);
    gfx_PrintStringXY("-Patty van Delft,",1,46);
    gfx_PrintStringXY("The dragon is based on Dragan Duma,",10,61);
    gfx_PrintStringXY("Which is a incredible serie Patty wrote",10,76);
    gfx_PrintStringXY("-Celtica Publishing,",1,96);
    gfx_PrintStringXY("Who published Dragan Duma",10,111);
    gfx_PrintStringXY("-The Cemetech community,",1,131);
    gfx_PrintStringXY("Who helped me with creating this",10,146);
    gfx_PrintStringXY("-Again: Patty van Delft,",1,166);
    gfx_PrintStringXY("For creating the artwork",10,181);
    gfx_PrintStringXY("This program was made by: Privacy_Dragon",1,210);
    gfx_PrintStringXY("DEV_ALPHA v0.0.1",200,230);
    do{ //wait untill clear is pressed
        kb_Scan();
    } while (!kb_IsDown(kb_KeyClear));
    do{//wait untill clear is released
        kb_Scan();
    } while (kb_IsDown(kb_KeyClear));
    gfx_BlitBuffer(); //get the screen back from the buffer, move the about screen in the buffer (though it isn't needed anymore)
    return score;
}
void feed(){
}
void care(){
}
void train(){
}
void lines(uint24_t level) {
    int a;
    gfx_SetColor(255);
    gfx_HorizLine_NoClip(0, 210, 320);
    for (a = 0; a < 320; a+=64){
        gfx_VertLine_NoClip(a, 210, 240);
    }
    gfx_FillRectangle(128,210,64,30);
    gfx_SetTextXY(5,5);
    gfx_PrintString("LEVEL: ");
    gfx_PrintUInt(level,2);
    gfx_PrintStringXY("FEED",13,223);
    gfx_PrintStringXY("CARE",77, 223);
    gfx_PrintStringXY("ABOUT",141,223);
    gfx_PrintStringXY("TRAIN",205,223);
    gfx_BlitBuffer();
}
void dragan() {
    unsigned int i;
    unsigned int x, y;
    gfx_sprite_t *tile;
    tile = gfx_MallocSprite(image1_tile_width, image1_tile_height);
    gfx_Begin();
    x = 0;
    y = 0;
    gfx_SetDrawBuffer();
    for (i = 0; i < image1_tiles_num; ++i)
    {
        zx7_Decompress(tile, image1_tiles_compressed[i]);
        gfx_Sprite_NoClip(tile, x, y);

        x += image1_tile_width;
        if (x >= LCD_WIDTH)
        {
            y += image1_tile_height;
            x = 0;
        }
    }
    gfx_SetPalette(globale_palette, sizeof_global_palette, 0);
    gfx_BlitBuffer();
}    
void draak() {
    unsigned int i;
    unsigned int x, y;
    gfx_sprite_t *tile;
    tile = gfx_MallocSprite(image_tile_width, image_tile_height);
    gfx_Begin();
    x = 0;
    y = 0;
    gfx_SetDrawBuffer();
    for (i = 0; i < image_tiles_num; ++i)
    {
        zx7_Decompress(tile, image_tiles_compressed[i]);
        gfx_Sprite_NoClip(tile, x, y);

        x += image_tile_width;
        if (x >= LCD_WIDTH)
        {
            y += image_tile_height;
            x = 0;
        }
    }
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_BlitBuffer();
}
uint24_t program_run(uint24_t score){
    do {
        kb_Scan();
        if (kb_Data[1] == kb_Yequ){
            feed();
        }
        if (kb_Data[1] == kb_Window){
            care();
        }
        if (kb_Data[1] == kb_Zoom){
            score = about(score);
        }
        if (kb_Data[1] == kb_Trace){
            train();
        }
    } while (kb_Data[6] != kb_Clear);
    return score;
}
uint24_t OPENVAR(){
    uint24_t score;
    uint24_t level;
    ti_var_t var;
    ti_var_t slot;
    score = 100;
    ti_CloseAll();
    if (!ti_Open(APPVAR, "r")){
        ti_CloseAll();
         slot = ti_Open(APPVAR, "w");
        ti_Write(&score, sizeof(score), 1, slot);
        ti_CloseAll();
    }
     var = ti_Open(APPVAR, "r");
    score = ti_Read(&score, sizeof(score), 1, var);
    dbg_sprintf(dbgout, score);
    ti_CloseAll();
    if (score < 100){ //if for some reason the score is below 100, which shouldn't happen, reset it to 100
        printf("%d\n",score);
        delay(500);
        score = 100;
        var = ti_Open(APPVAR, "w");
        ti_Write(&score, sizeof(score), 1, var);
        }
    printf("%d",score);
    delay(500);
    level = score/100;
    ti_CloseAll();
    return score;
}
int main(void)
{
    /*Open an appvar where the score is stored.
     * If it isn't available, create it and set it to 100.
     */
    uint24_t score = OPENVAR();
    uint24_t level = score/100;
    ti_CloseAll();
    if (level > 20){ //If the level is higher than 10, display the big dragon
        DRAGAN_init();
        dragan();
    }
    else { //if the level is lower than 10, display the small dragon
        DRAAK_init();
        draak();
    }
    lines(level); //draw the 'menu' bar
    score = program_run(score);
    //update the score variable with the new score
    ti_var_t var = ti_Open(APPVAR, "w");
    ti_Write(&score, sizeof(score), 1, var);
    ti_CloseAll();
    printf("%d",score);
    delay(500);
    gfx_End();
}
