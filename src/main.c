#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

#include "Graphics.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Input.h"


int time;


extern int he_texture[];
Texture he_texture_text;
Sprite he_sprite;

Controller* controller;


int main() {
        
    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_texture);
    he_sprite.text = &he_texture_text;
    he_sprite.x=64;
    he_sprite.y=64;


    while(1) {
        controller = (Controller*)padbuff[0];

        if(controller->status==0){
            if((controller->type==0x4)||(controller->type==0x5)||(controller->type==0x7)){
                if(!(controller->button&PAD_UP)){
                    he_sprite.y--;
                }
                else if(!(controller->button&PAD_DOWN)){
                    he_sprite.y++;
                }
                if(!(controller->button&PAD_LEFT)){
                    he_sprite.x--;
                }
                else if(!(controller->button&PAD_RIGHT)){
                    he_sprite.x++;
                }
            }
        }

        ClearOTagR(ord.ot[db], OTLEN);

        time++;

        DrawSprite(&he_sprite,&ord,db);

    


        FntPrint("Time: %d",time);

        FntFlush(-1);
                
        display();
        
    }
    
    return 0;
}
