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


extern int he_texture[];
Texture he_texture_text;
Sprite he_sprite;

Triangle triangle;

Controller* controller;

SVECTOR vertices[] = {
{   0, -20,  0  },
{  10,  20,  0  },
{ -10,  20,  0  }
};


int main() {
        
    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_texture);
    he_sprite.text = &he_texture_text;
    he_sprite.x=64;
    he_sprite.y=64;
    he_sprite.angle=2048;
    he_sprite.scale=1;

    triangle = CreateTriangle(vertices,255,255,255);
    triangle.posx=ONE*64;
    triangle.posy=ONE*64;

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

        triangle.angle=time*20;
        he_sprite.angle=time*20;

        time++;

        DrawTriangle(&triangle,&ord,db);
        DrawSprite(&he_sprite,&ord,db);


    


        FntPrint("Time: %d\nTriangle position:\n    X: %d\n    Y: %d\nAngle: %d",time,triangle.posx>>12,triangle.posy>>12,triangle.angle);

        FntFlush(-1);
                
        display();
        
    }
    
    return 0;
}
