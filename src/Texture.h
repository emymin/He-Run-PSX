#ifndef TEXTURE_H
#define TEXTURE_H

#include <sys/types.h>
#include <libgpu.h>


typedef struct _texture{
    TIM_IMAGE tim;
    u_short tpage;
    u_short clut;
    u_char  u,v;
    u_char  w,h;
    CVECTOR col;
} Texture;

typedef struct _sprite{
    int x,y;
    int angle;
    int scale;
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

void CreateSprite(Sprite* sprite,int x,int y,int angle,int scale,Texture* text){
    sprite->x=x;
    sprite->y=y;
    sprite->angle=angle;
    sprite->scale=scale;
    sprite->text=text;

}

GetTexture(Texture* text,int tim_image[]){
    TIM_IMAGE tim;
    LoadTexture((u_long*)tim_image,&tim);
    
    text->tpage = getTPage(tim.mode&0x3, 0, 
        tim.prect->x, tim.prect->y);
    
    text->tim=tim;

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

void DrawAlignedSprite(Sprite* sprite,OrderingTable* ord,int db){
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

void DrawSprite(Sprite* sprite,OrderingTable* ord,int db){
    POLY_FT4 *quad;
    SVECTOR	s[4];
    SVECTOR	v[4];

    int i,cx,cy;

    cx = sprite->text->w>>1;
    cy = sprite->text->h>>1;

    s[0].vx = -(((sprite->text->w*sprite->scale)>>12)-cx);
    s[0].vy = -(((sprite->text->h*sprite->scale)>>12)-cy);

    s[1].vx = (((sprite->text->w*sprite->scale)+2048)>>12)-cx;
    s[1].vy = s[0].vy;

    s[2].vx = -(((sprite->text->w*sprite->scale)>>12)-cx);
    s[2].vy = (((sprite->text->h*sprite->scale)+2048)>>12)-cy;

    s[3].vx = (((sprite->text->w*sprite->scale)+2048)>>12)-cx;
    s[3].vy = s[2].vy;

    cx = ccos( sprite->angle );
    cy = csin( sprite->angle );

    for( i=0; i<4; i++ )
    {
        v[i].vx = (((s[i].vx*cx)
            -(s[i].vy*cy))>>12)+sprite->x;
        v[i].vy = (((s[i].vy*cx)
            +(s[i].vx*cy))>>12)+sprite->y;
    }

    quad = (POLY_FT4*)(ord->nextpri);
    setPolyFT4( quad );

    setTPage( quad, sprite->text->tim.mode&0x3, 0, sprite->text->tim.prect->x, sprite->text->tim.prect->y );
    setClut( quad, sprite->text->tim.crect->x, sprite->text->tim.crect->y );

    setRGB0( quad, 128, 128, 128 );
    setXY4( quad,
        v[0].vx, v[0].vy,
        v[1].vx, v[1].vy,
        v[2].vx, v[2].vy,
        v[3].vx, v[3].vy );
    setUVWH( quad, sprite->text->u, sprite->text->v, sprite->text->w, sprite->text->h );

    addPrim( ord->ot[db], quad );
    ord->nextpri += sizeof(POLY_FT4);

}



#endif