#ifndef TEXTURE_H
#define TEXTURE_H

#include <sys/types.h>
#include <libgpu.h>


typedef struct _texture{
    u_short tpage;
    u_short clut;
    u_char  u,v;
    u_char  w,h;
    CVECTOR col;
} Texture;

typedef struct _sprite{
    int x,y;
    Texture* text;
} Sprite;

void LoadTexture(u_long *tim, TIM_IMAGE *tparam) {

    OpenTIM(tim);
    ReadTIM(tparam);

    LoadImage(tparam->prect, (u_long*)tparam->paddr);
    DrawSync(0);

    if( tparam->mode & 0x8 ) {

        LoadImage(tparam->crect, (u_long*)tparam->caddr);
        DrawSync(0);

    }

}

GetTexture(Texture* text,int tim_image[]){
    TIM_IMAGE tim;
    LoadTexture((u_long*)tim_image,&tim);
    
    text->tpage = getTPage(tim.mode&0x3, 0, 
        tim.prect->x, tim.prect->y);
        
    if( tim.mode & 0x8 ) {
        text->clut = getClut(tim.crect->x, tim.crect->y);
    }
    
    text->w = tim.prect->w<<(2-tim.mode&0x3);
    text->h = tim.prect->h;
    
    text->u = (tim.prect->x&0x3f)<<(2-tim.mode&0x3);
    text->v = tim.prect->y&0xff;
    
    text->col.r = 128;
    text->col.g = 128;
    text->col.b = 128;
}

void DrawSprite(Sprite* sprite,OrderingTable* ord,int db){
    SPRT* sprt;
    DR_TPAGE *tpage;

    sprt = (SPRT*)(ord->nextpri);
    setSprt(sprt);

    setXY0(sprt,sprite->x,sprite->y);
    setWH(sprt,sprite->text->w,sprite->text->h);
    setUV0(sprt,sprite->text->u,sprite->text->v);

    setRGB0(sprt,sprite->text->col.r,sprite->text->col.g,sprite->text->col.b);

    sprt->clut = sprite->text->clut;

    addPrim(ord->ot[db],sprt);
    ord->nextpri += sizeof(SPRT);

    tpage = (DR_TPAGE*)(ord->nextpri);
    setDrawTPage(tpage,0,1,sprite->text->tpage);
    addPrim(ord->ot,tpage);

    ord->nextpri += sizeof(DR_TPAGE);


}

#endif