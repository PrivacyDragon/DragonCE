#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <compression.h>
#include <fileioc.h>
#include "gfx/gfx.h"
#define APPVAR "DRGNLVL"

uint24_t score;
uint24_t level;

void setup(){
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetTransparentColor(148);
    gfx_FillScreen(224);
}

void about(){
    void about2();
    score++;
    gfx_SetDrawScreen();
    gfx_FillScreen(224);
    gfx_PrintStringXY("DRAGONCE, a virtual dragon on your calculator!",1,1);
    gfx_PrintStringXY("I really want to thank:",1,26);
    gfx_PrintStringXY("-Patty van Delft,",1,46);
    gfx_PrintStringXY("The dragon is based on Dragan Duma,",10,61);
    gfx_PrintStringXY("Which is a incredible serie Patty wrote",10,76);
    gfx_PrintStringXY("-Celtica Publishing,",1,96);
    gfx_PrintStringXY("Who published Dragan Duma",10,111);
    gfx_PrintStringXY("-TimmyTurner51 and others from Cemetech,",1,131);
    gfx_PrintStringXY("Who helped me with creating this",10,146);
    gfx_PrintStringXY("-Again: Patty van Delft,",1,166);
    gfx_PrintStringXY("For drawing the dragons",10,181);
    gfx_PrintStringXY("This program was made by: Privacy_Dragon",1,210);
    gfx_PrintStringXY("DEV_ALPHA v0.0.2",200,230);
    gfx_PrintStringXY(">",5,230);
    do{ //wait untill clear is pressed
        kb_Scan();
        if (kb_Data[7] == kb_Right){
            about2();
        }
    } while (!kb_IsDown(kb_KeyClear));
    do{//wait untill clear is released
        kb_Scan();
    } while (kb_IsDown(kb_KeyClear));
    gfx_BlitBuffer(); //get the screen back from the buffer, move the about screen in the buffer (though it isn't needed anymore)
}

void about2(){
    gfx_FillScreen(224);
    gfx_PrintStringXY("DRAGONCE, a virtual dragon on your calculator!",1,1);
    gfx_PrintStringXY("Patty van Delft's website:",1,26);
    gfx_PrintStringXY("https://pattyvandelft.com/",5,41);
    gfx_PrintStringXY("Celtica Publishing website:",1,61);
    gfx_PrintStringXY("https://www.celtica-publishing.nl/",5,76);
    gfx_PrintStringXY("This program was made by: Privacy_Dragon",1,210);
    gfx_PrintStringXY("DEV_ALPHA v0.0.2",200,230);
    gfx_PrintStringXY("<",5,230);
    do{
        kb_Scan();
        if (kb_Data[7] == kb_Left){
            about();
        }
    } while (kb_Data[6] != kb_Clear);
}
void feed(){
    int x, y;
    score++;
    gfx_BlitScreen();
    gfx_SetDrawScreen();
    for (x = 10; x < 60; x++){
        gfx_Sprite(goat, x,50);
        delay(100);
    }
    for (y = 50; y < 75; y++){
        gfx_Sprite(goat, 60, y);
        delay(100);
    }
    gfx_TransparentSprite(goat, 60, 75);
    gfx_SwapDraw();
    delay(300);
    gfx_BlitBuffer();
}

void care(){
}
void train(){
       int x, y;
    score++;
    gfx_BlitScreen();
    gfx_SetDrawScreen();
    gfx_FillScreen(224);
    for (y = 40; y < 10; y--){
        gfx_Sprite_NoClip(dragon, 40, y);
        delay(80);
    }
    for (x = 40; x < 70; x++){
        gfx_Sprite_NoClip(dragon, x, 5);
        delay(80);
    }
    delay(500);
    gfx_SwapDraw();
    gfx_BlitBuffer();
}

void lines() {
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

void drawgan() {
    gfx_TransparentSprite(dragan, 40, 40);
    gfx_BlitBuffer();
}

void draak() {
    gfx_TransparentSprite(dragon, 40, 40);
    gfx_BlitBuffer();
}

void program_run(){
    do {
        kb_Scan();
        if (kb_Data[1] == kb_Yequ){
            feed();
        }
        if (kb_Data[1] == kb_Window){
            care();
        }
        if (kb_Data[1] == kb_Zoom){
            gfx_BlitScreen(); //move the screen to the buffer.
            about();
        }
        if (kb_Data[1] == kb_Trace){
            train();
        }
    } while (kb_Data[6] != kb_Clear);
}

void OPENVAR(){
    ti_var_t var;
    ti_var_t slot;
    ti_CloseAll();
    if (!ti_Open(APPVAR, "r")){
        slot = ti_Open(APPVAR, "w");
        score = 100;
        ti_Write(&score, sizeof(score), 1, slot);
        ti_CloseAll();
    }
    var = ti_Open(APPVAR, "r");
    ti_Read(&score, sizeof(score), 1, var); //DON'T say score = ti_Read(blabla) that will mess everything up...
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
    ti_CloseAll();
}

void UPDATEVAR(){
    ti_var_t var = ti_Open(APPVAR, "w");
    ti_Write(&score, sizeof(score), 1, var);
    ti_CloseAll();
}

int main(void)
{
    setup();
    OPENVAR(); //get the score from the appvar
    level = score/100;
    ti_CloseAll();
    if (level > 20){ //If the level is higher than 10, display the big dragon
        drawgan();
    }
    else { //if the level is lower than 10, display the small dragon
        draak();
    }
    lines(); //draw the rest of the screen
    program_run();
    UPDATEVAR(); //update the score appvar with the new score
    gfx_End();
}
