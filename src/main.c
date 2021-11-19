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
Sprite he_sprite;

Controller* controller;


int main() {
        
    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_transparent_texture);
    he_sprite.text = &he_texture_text;
    he_sprite.x=64;
    he_sprite.y=64;
    he_sprite.angle=2048;
    he_sprite.scale=1;


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

        he_sprite.angle=time*20;

        time++;

        DrawSprite(&he_sprite,&ord,db);


    


        FntPrint("Time: %d\nHe position:\n    X: %d\n    Y: %d\nAngle: %d",time,he_sprite.x,he_sprite.y,he_sprite.angle);

        FntFlush(-1);
                
        display();
        
    }
    
    return 0;
}
