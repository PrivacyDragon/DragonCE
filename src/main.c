#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include "gfx/gfx.h"
#define APPVAR "DRGNLVL"
uint24_t score;
uint24_t level;
gfx_sprite_t *draga; //this is to make it easier to move the dragon, no matter what one it is.
uint8_t time[4] = {
		0,
		0,
		0,
		0
	    };
void setup(){
    srandom(rtc_Time());
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetTransparentColor(148);
    void GetLastTime();
}
void about(){
    void about2();
    score++;
    gfx_SetDrawScreen();
    do{ 
        gfx_FillScreen(132);
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
    	gfx_PrintStringXY("DEV_ALPHA v0.0.8",200,230);
    	gfx_PrintStringXY(">",5,230);
	delay(150);
    	do{ //Detect keypresses. Right goes to about2, clear exits the loop, so you can exit the about screen
    	    kb_Scan();
    	    if (kb_Data[7] == kb_Right){
    	        about2();
            }
	    if (kb_Data[6] == kb_Clear || kb_Data[7] == kb_Left){ //If kb_Left was pressed, it means the person did go to about2 and back. that means the loop for keypresses has to be quit, so the about text can be drawn again.
		break;
	    }
	} while (kb_Data[7] != kb_Right);
      } while (!kb_IsDown(kb_KeyClear));
      do{//wait untill clear is released
        kb_Scan();
      } while (kb_IsDown(kb_KeyClear));
    gfx_BlitBuffer(); //get the screen back from the buffer, move the about screen in the buffer (though it isn't needed anymore)
}
void about2(){
    gfx_FillScreen(132);
    gfx_PrintStringXY("DRAGONCE, a virtual dragon on your calculator!",1,1);
    gfx_PrintStringXY("Patty van Delft's website:",1,26);
    gfx_PrintStringXY("https://pattyvandelft.com/",5,41);
    gfx_PrintStringXY("Celtica Publishing website:",1,61);
    gfx_PrintStringXY("https://www.celtica-publishing.nl/",5,76);
    gfx_PrintStringXY("This program was made by: Privacy_Dragon",1,210);
    gfx_PrintStringXY("DEV_ALPHA v0.0.8",200,230);
    gfx_PrintStringXY("<",5,230);
    do{
      kb_Scan();
    } while (kb_Data[7] != kb_Left && kb_Data[6] != kb_Clear);
}
void say(char string){
}
void fly(){
	int x, y, i;
	x = 10;y = 10;i = 0;
	score+=2;
	gfx_BlitScreen();
	gfx_FillScreen(132);
	gfx_SetColor(132);
	gfx_ScaledSprite_NoClip(grass, 1, 210, 2, 2);
	do{
		if (level<10){
			gfx_PrintStringXY("YOU CAN'T FLY ON A DRAGON TILL IT'S GROWN UP!!!", 1,20);
			delay(500);
			score-=2;
			break;
		}
		gfx_FillRectangle(1,1,20,20);
		gfx_SetTextXY(1,1);
		gfx_PrintUInt(x, 2);
		gfx_SetTextXY(1,10);
		gfx_PrintUInt(y, 2);
		gfx_ScaledSprite_NoClip(dragon_fly, x, y, 2, 2);
		kb_Scan();
		if (kb_Data[7] == kb_Left && x!=1){
			if (x>2){
				x--;
			}
			else{
				i++;
				gfx_FillRectangle(1,210,30,480);
				gfx_ScaledSprite_NoClip(grass, 480+i, 210, 2, 2);
			}
		}
		else if (kb_Data[7] == kb_Right){
			if (x!=280){
				x++;
			}
			else{
				/*gfx_ShiftLeft(1);*/
				i--;
				gfx_FillRectangle(1,210,30,480);
				gfx_ScaledSprite_NoClip(grass, 480+i, 210, 2, 2);
			}
		}
		else if (kb_Data[7] == kb_Down && y!=188){
			y++;
		}
		else if (kb_Data[7] == kb_Up && y!=1){
			y--;
		}
		if (kb_IsDown(kb_KeyAlpha)){ //If alpha is PRESSED the fire should come
			gfx_ScaledSprite_NoClip(fire, x+40, y+30, 2, 2); //The location of the fire is based on the location of the dragon.
			gfx_ScaledSprite_NoClip(fire, x+58, y+30, 2, 2);
		}
		else{ //if the alpha key is not pressed, a simple rectangle is drawn.
			gfx_FillRectangle(x+40, y+30, 50, 70);
		}
	} while (!kb_IsDown(kb_KeyClear));
	do{//wait untill clear is released
        kb_Scan();
    } while (kb_IsDown(kb_KeyClear));
	gfx_BlitBuffer(); //get the normal screen back
    gfx_SetDrawScreen();
}
void feed(){
    void GetLastTime(), SetLastTime();
    int x, y;
    uint8_t second_now, minute_now, hour_now, day_now, month_now;
    uint16_t year_now;
    //Get the time the dragon was last fed out of an appvar. Then get the current time.
    GetLastTime();
    gfx_SetTextXY(1,20);
    gfx_PrintUInt(time[0], sizeof(time[0]));
    gfx_PrintString(":");
    gfx_PrintUInt(time[1], sizeof(time[1]));
    gfx_PrintString(".");
    gfx_PrintUInt(time[2], sizeof(time[2]));
    delay(500);
    boot_GetTime(&second_now, &minute_now, &hour_now);
    boot_GetDate(&day_now, &month_now, &year_now);
    int hours_gone = hour_now - time[0];
    int days_gone = day_now - time[3];
    time[0] = hour_now;
    time[1] = minute_now;
    time[2] = second_now;
    time[3] = day_now;
    SetLastTime();
    score++;
    gfx_BlitScreen();
    gfx_SetTextXY(21,50);
    gfx_PrintUInt(hours_gone, sizeof(hours_gone));
    gfx_PrintString(":");
    gfx_PrintUInt(days_gone, sizeof(days_gone));
    gfx_PrintString(".");
    gfx_PrintUInt(time[2], sizeof(time[2]));
    delay(500);
    if ((level<10 && ((days_gone == 0 && hours_gone > 4)||(days_gone>1))) || (level>=10 && days_gone >= 1)){



   	 //the following two for loops move the goat to the dragon.
   	 for (x = 10; x < 50; x++){
   	     gfx_Sprite(goat, x,50);
   	     delay(100);
   	 }
   	 for (y = 50; y < 70; y++){
   	     gfx_Sprite(goat, 50, y);
   	     delay(100);
   	 }
   	 gfx_TransparentSprite(goat, 50, 70);
   	 gfx_SwapDraw();
   	 delay(300);
   	 gfx_BlitBuffer();
   	 gfx_SetDrawScreen();
   }
   else {
     say("I don't want to get as fat as you!");
   }
}
	
void care(){
    /* ADD IN THE OIL STUFF.
     * LOOK UP IF THAT WAS BEFORE OR AFTER THE SAND.
     * FIND OUT IF THERE WAS ANYTHING ELSE NEEDED
     */
    uint24_t x, i, j;
    uint8_t y;
    score++;
    gfx_FillScreen(132); //fill the screen with the background color.
    gfx_SetColor(227); //set the color to a yellow to display pixels, being 'sand'
    gfx_Sprite(draga, 100, 40); //draw the dragon again
	gfx_SetTextScale(2, 2);
	gfx_PrintStringXY("Using sand...", 100, 0);
    for (j = 0; j < 240; j++){ //draw yellow pixels on the screen, going down.
        for (i = 0; i < 90; i++){
            x = randInt(0, 320);
            y = randInt(0, 10)+j;
            gfx_SetPixel(x, y);
        }
        for (i = 0; i < 46; i++){
            x = randInt(10, 310);
            y = randInt(10, 20)+j;
            gfx_SetPixel(x, y);
        }
        for (i = 0; i < 46; i++){
            x = randInt(10, 310);
            y = randInt(20, 40)+j;
            gfx_SetPixel(x, y);
        }
    }
    delay(300); //wait for a moment.
	gfx_SetColor(132);
	gfx_FillRectangle(0,0,320,15);
	gfx_SetColor(28);
	gfx_PrintStringXY("Using Water...", 100, 0);
	for (j = 20; j < 240; j++){ //draw blue pixels on the screen, going down.
        for (i = 0; i < 90; i++){
            x = randInt(0, 320);
            y = randInt(0, 10)+j;
            gfx_SetPixel(x, y);
        }
        for (i = 0; i < 46; i++){
            x = randInt(10, 310);
            y = randInt(10, 20)+j;
            gfx_SetPixel(x, y);
        }
        for (i = 0; i < 46; i++){
            x = randInt(10, 310);
            y = randInt(20, 40)+j;
            gfx_SetPixel(x, y);
        }
    }
    delay(300);
	gfx_FillScreen(132);
	gfx_Sprite(draga, 100, 40);
	gfx_PrintStringXY("Using Oil...", 100, 0);
	gfx_RotatedSprite_NoClip(oil, 240, 10, 45);
	delay(1500);
    //do something that wipes the pixels to the left.
   /* for (i = 0; i < 320; i++){
        gfx_ShiftLeft(1);
        gfx_FillRectangle(319,0,320,240);
        gfx_Sprite(draga, 100, 40);
        delay(50);
    }*/
    gfx_FillScreen(132);
	gfx_Sprite(draga, 100, 40);
	gfx_PrintStringXY("Done!", 100, 10);
	gfx_SetColor(255);
	for (i=0; i<50; i++){
		x=randInt(120,220);
		y=randInt(40,180);
		gfx_SetPixel(x, y);
		delay(50);
	}
	gfx_SetTextScale(1, 1);
	delay(500);
    gfx_BlitBuffer(); //get the normal screen back
    gfx_SetDrawScreen();
	
}
void train(){
    int i, y;
    score++;
    char* action[6] = {"FLYING +2",
                       "DAMAGE -1",
                       "HIDING +9",
                       "FIRE +4",
                       "ROARING +8",
                       "FLUFFY -10"};
    gfx_BlitScreen();
    gfx_FillScreen(132);
    /*for (y = 40; y != 10; y--){
        gfx_TransparentSprite(dragon, 40, y);
        delay(80);
    }
    for (x = 40; x < 80; x++){
        gfx_TransparentSprite(dragon, x, 10);
        delay(80);
    }*/
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("TRAINING...", 150,220);
    for (i = 0; i < 5; i++){
        for (y = 10; y < 40; y++){
            gfx_Sprite_NoClip(draga, 100, y);
            delay(40);
        }
        for (y = 40; y != 10; y--){
            gfx_Sprite_NoClip(draga, 100, y);
            delay(40);
        }
        gfx_FillScreen(132);
        gfx_PrintStringXY(action[randInt(0,5)], 0, 200);
        gfx_PrintStringXY("TRAINING...", 150,220);
    }
    gfx_SetTextScale(1, 1);
    delay(500);
    gfx_SwapDraw();
    gfx_BlitBuffer();
    gfx_SetDrawScreen();
}
void lines() {
    int a;
    gfx_SetColor(255);
    gfx_HorizLine(0, 210, 320);
    for (a = 0; a < 320; a+=64){
        gfx_VertLine(a, 210, 240);
    }
    gfx_FillRectangle(128,210,64,30);
    gfx_SetTextXY(5,5);
    gfx_PrintString("LEVEL: ");
    gfx_PrintUInt(level,2);
    gfx_PrintStringXY("FEED",13,223);
    gfx_PrintStringXY("CARE",77, 223);
    gfx_PrintStringXY("ABOUT",141,223);
    gfx_PrintStringXY("TRAIN",205,223);
	gfx_PrintStringXY("FLY",276,223);
    gfx_BlitBuffer();
}
void drawgan() {
    draga = dragan; //store the sprite in draga, so it's easier to use later.
    gfx_TransparentSprite(draga, 100, 40);
    gfx_BlitBuffer();
}
void draak() {
    draga = dragon; //store the sprite in draga, so it's easier to use later.
    gfx_TransparentSprite(draga, 100, 40);
    gfx_BlitBuffer();
}
void draw_Dragon(){
    gfx_FillScreen(132); //Fill the screen with a green background color.
    if (level >= 10){ //If the level is higher than 10, display the big dragon
        drawgan();
    }
    else { //if the level is lower than 10, display the small dragon
        draak();
    }
}
void program_run(){
    gfx_SetDrawScreen();
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
        if (kb_Data[1] == kb_Graph){
	    fly();
	}
        if (kb_Data[3] == kb_0){
            //for testing purposes only
            printf("%d",score);
            delay(500);
            gfx_BlitBuffer();
        }
        if (level != score/20){
            //Make sure that the level is updated when you level up.
            //You'll also see big "LEVEL UP!" when you level up.
            //Also make sure that the good dragon is when you have gained a level.
            gfx_FillScreen(132);
            gfx_SetTextScale(3, 3);
            gfx_PrintStringXY("LEVEL UP!", 25, 120);
            gfx_SetTextScale(1, 1);
	    delay(1000);
	    gfx_FillScreen(132);
            level = score/20;
	    gfx_SetDrawBuffer();
            draw_Dragon();
	    lines();
	    gfx_SetDrawScreen();
        }
    } while (kb_Data[6] != kb_Clear);
}
void SetLastTime(){
    ti_var_t var = ti_Open("FEEDTIME", "w");
    ti_Write(&time, sizeof(time), 1, var);
    ti_CloseAll();
}
void GetLastTime(){
    ti_var_t var, slot;
    ti_CloseAll();
    if (!ti_Open("FEEDTIME", "r")){
	slot = ti_Open("FEEDTIME", "w");
	ti_Write(&time, sizeof(time), 1, slot);
	ti_CloseAll();
    }
    var = ti_Open("FEEDTIME", "r");
    ti_Read(&time, sizeof(time), 1, slot);
    ti_CloseAll();
}
void OPENVAR(){
    ti_var_t var;
    ti_var_t slot;
    ti_CloseAll();
    if (!ti_Open(APPVAR, "r")){
        slot = ti_Open(APPVAR, "w");
        score = 20;
        ti_Write(&score, sizeof(score), 1, slot);
        ti_CloseAll();
    }
    var = ti_Open(APPVAR, "r");
    ti_Read(&score, sizeof(score), 1, var); //DON'T say score = ti_Read(blabla) that will mess everything up...
    ti_CloseAll();
    if (score < 20){ //if for some reason the score is below 20, which shouldn't happen, reset it to 20
        printf("%d\n",score);
        delay(500);
        score = 20;
        var = ti_Open(APPVAR, "w");
        ti_Write(&score, sizeof(score), 1, var);
        }
    ti_CloseAll();
}
void UPDATEVAR(){
    ti_var_t var = ti_Open(APPVAR, "w");
    ti_Write(&score, sizeof(score), 1, var);
    ti_CloseAll();
}
int main(void)
{
    setup(); //setup the stuff for graphics.
    OPENVAR(); //get the score from the appvar.
    level = score/20;
    ti_CloseAll();
    draw_Dragon(); //determine which dragon to draw and draw it.
    lines(); //draw the rest of the screen
    program_run(); //run the program
    UPDATEVAR(); //update the score appvar with the new score.
    gfx_End();
}
