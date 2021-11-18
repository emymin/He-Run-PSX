#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <sys/types.h>
#include <libgpu.h>
#include "Graphics.h"

TILE *tile;


typedef struct _rectangle{
    int x,y;
    int width,height;
    int r,g,b;
} Rectangle;

Rectangle CreateRectangle(int x,int y,int width,int height,int r,int g,int b){
    Rectangle rect;
    rect.x=x;
    rect.y=y;
    rect.width=width;
    rect.height=height;
    rect.r=r;
    rect.g=g;
    rect.b=b;
    return rect;
}

void DrawRectangle(Rectangle* rect,OrderingTable* ord,int db){
        TILE* tile = (TILE*)(ord->nextpri);

        setTile(tile);
        setXY0(tile, rect->x, rect->y);
        setWH(tile, rect->width,rect->height);
        setRGB0(tile, rect->r, rect->g, rect->b);
        addPrim(ord->ot[db], tile);
        
        (ord->nextpri) += sizeof(TILE);
}

#endif