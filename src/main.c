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


int main() {
        
    initGraphics();
    initControllers();
    
    GetTexture(&he_texture_text,he_texture);
    he_sprite.text = &he_texture_text;


    while(1) {
        ClearOTagR(ord.ot[db], OTLEN);

        time++;

        he_sprite.y = (120-32) + sin((float)time*0.1f)*(120-32);
        he_sprite.x = (160-32) + cos((float)time*0.1f)*(160-32);
        DrawSprite(&he_sprite,&ord,db);

        he_sprite.y = (120-32) + cos((float)time*0.1f)*(120-32);
        he_sprite.x = (160-32) + sin((float)time*0.1f)*(120-32);
        DrawSprite(&he_sprite,&ord,db);
    


        FntPrint("Time: %d",time);

        FntFlush(-1);
                
        display();
        
    }
    
    return 0;
}
