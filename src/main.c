#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

#include "Graphics.h"
#include "Primitives.h"
#include "Texture.h"
#include "Input.h"
#include "Resources.h"


Rectangle sideRectangle;
Sprite he_sprite;

Sprite road_left_sprite;
Sprite road_right_sprite;
Sprite top_road_left;
Sprite top_road_right;

Sprite car;


void initResources(){
    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_transparent_texture);
    GetTexture(&road_left,road_left_texture);
    GetTexture(&road_right,road_right_texture);
    GetTexture(&car1_texture_text,car1_texture);

    sideRectangle = CreateRectangle(0,0,128,240,200,200,200);

    he_sprite.text = &he_texture_text;
    road_left_sprite.text=&road_left;
    road_right_sprite.text=&road_right;
    top_road_left.text=&road_left;
    top_road_right.text=&road_right;


    road_left_sprite.x=128;
    road_left_sprite.y=0;

    road_right_sprite.x=128+(192/2);
    road_right_sprite.y=0;

    top_road_left.x=128;
    top_road_left.y=-240;

    top_road_right.x=128+(192/2);
    top_road_right.y=-240;

    he_sprite.text->w-=13;
    he_sprite.text->h-=13;


}

int lives;
int score;

void resetGame(){
    he_sprite.x=128+(320-128)/2;
    he_sprite.y=200;
    he_sprite.angle=2048;
    he_sprite.scale=1;

    car.text=&car1_texture_text;
    Random(192-64);
    car.x = 128+RAN;
    car.y = -128;

    lives=9;
    score=0;
}


int checkCollision(Sprite* sprite1,Sprite* sprite2){
    if(sprite1->x < sprite2->x + sprite2->text->w &&
    sprite1->x + sprite1->text->w > sprite2->x &&
    sprite1->y < sprite2->y +sprite2->text->h &&
    sprite1->y + sprite1->text->h > sprite2->y){
        return 1;
    }
    return 0;
}



void gameLoop(){
    int hasCollided;

    hasCollided = 0;

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
                if(!(controller->button&PAD_START)){
                    resetGame();
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

        car.y+=5;
        if(car.y>=240){
            car.y=-128;
            Random(192-64);
            car.x = 128+RAN;
        }

        if(checkCollision(&he_sprite,&car)){
            if(!hasCollided){
                hasCollided = 1;
                lives--;
                if(lives<=0){return;}
            }
        }else{
            hasCollided=0;
        }

        ClearOTagR(ord.ot[db], OTLEN);

        he_sprite.angle+=20;

        time++;
        score++;

        DrawAlignedSprite(&car,&ord,db);

        DrawSprite(&he_sprite,&ord,db);
        
        DrawRectangle(&sideRectangle,&ord,db);

        DrawAlignedSprite(&road_left_sprite,&ord,db);        
        DrawAlignedSprite(&road_right_sprite,&ord,db);
        DrawAlignedSprite(&top_road_left,&ord,db);        
        DrawAlignedSprite(&top_road_right,&ord,db);



        FntPrint("\n    HE RUN\n\n\n\nScore: %d\n\nLives: %d",score,lives);

        FntFlush(-1);
                
        display();
    }   
}


int main() {

    initResources();

    while(1){
        resetGame();
        gameLoop();
    }

    
    return 0;
}
