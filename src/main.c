#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

#include "Graphics.h"
#include "Primitives.h"
#include "Texture.h"
#include "Input.h"


int time;


extern int he_transparent_texture[];
Texture he_texture_text;

extern int road_left_texture[];
Texture road_left;
extern int road_right_texture[];
Texture road_right;


Controller* controller;


int main() {
    Rectangle sideRectangle;
    Sprite he_sprite;

    Sprite road_left_sprite;
    Sprite road_right_sprite;
    Sprite top_road_left;
    Sprite top_road_right;

    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_transparent_texture);
    GetTexture(&road_left,road_left_texture);
    GetTexture(&road_right,road_right_texture);


    he_sprite.text = &he_texture_text;
    he_sprite.x=128+(320-128)/2;
    he_sprite.y=200;
    he_sprite.angle=2048;
    he_sprite.scale=1;



    road_left_sprite.text=&road_left;
    road_left_sprite.x=128;
    road_left_sprite.y=0;

    road_right_sprite.text=&road_right;
    road_right_sprite.x=128+(192/2);
    road_right_sprite.y=0;

    top_road_left.text=&road_left;
    top_road_left.x=128;
    top_road_left.y=-240;

    top_road_right.text=&road_right;
    top_road_right.x=128+(192/2);
    top_road_right.y=-240;



    sideRectangle = CreateRectangle(0,0,128,240,200,200,200);
    


    while(1) {
        controller = (Controller*)padbuff[0];

        if(controller->status==0){
            if((controller->type==0x4)||(controller->type==0x5)||(controller->type==0x7)){
                if(!(controller->button&PAD_LEFT)){
                    if(he_sprite.x>(128+32)){
                        he_sprite.x-=3;
                    }
                }
                else if(!(controller->button&PAD_RIGHT)){
                    if(he_sprite.x<(320-32)){
                        he_sprite.x+=3;
                    }
                }
            }
        }


        //Road scrolling
        road_left_sprite.y+=3;
        road_right_sprite.y+=3;
        top_road_left.y+=3;
        top_road_right.y+=3;

        if(road_left_sprite.y>=240){
            road_left_sprite.y=0;
            road_right_sprite.y=0;
            top_road_left.y=-240;
            top_road_right.y=-240;
        }


        ClearOTagR(ord.ot[db], OTLEN);

        he_sprite.angle+=20;

        time++;

        DrawSprite(&he_sprite,&ord,db);
        
        DrawRectangle(&sideRectangle,&ord,db);

        DrawAlignedSprite(&road_left_sprite,&ord,db);        
        DrawAlignedSprite(&road_right_sprite,&ord,db);
        DrawAlignedSprite(&top_road_left,&ord,db);        
        DrawAlignedSprite(&top_road_right,&ord,db);



        FntPrint("\n    HE RUN\n\n\n\nScore: %d",time);

        FntFlush(-1);
                
        display();
        
    }
    
    return 0;
}
