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

typedef struct _triangle{
    SVECTOR vertices[3];
    CVECTOR col;
    int posx,posy;
    int angle;
} Triangle;

SVECTOR _default_triangle_offsets[] = {{64,64,0},{64,64,0},{64,64,0}};

Triangle CreateTriangle(SVECTOR vertices[3],int r,int g,int b){
    Triangle triangle;
    
    triangle.vertices[0] = vertices[0];
    triangle.vertices[1] = vertices[1];
    triangle.vertices[2] = vertices[2];

    triangle.col.r=r;
    triangle.col.g=g;
    triangle.col.b =b;

    triangle.posx=0;
    triangle.posy=0;
    triangle.angle=0;


    return triangle;
}

SVECTOR tri_v[3];
int _tri_i;

void DrawTriangle(Triangle* triangle,OrderingTable* ord,int db){
    POLY_F3* tri = (POLY_F3*)(ord->nextpri);
    setPolyF3( tri );
    setRGB0( tri, triangle->col.r, triangle->col.g, triangle->col.b );
    for( _tri_i=0; _tri_i<3; _tri_i++ )
    {
        tri_v[_tri_i].vx = (((triangle->vertices[_tri_i].vx*ccos( triangle->angle ))
            -(triangle->vertices[_tri_i].vy*csin( triangle->angle )))>>12) + (triangle->posx>>12);
        tri_v[_tri_i].vy = (((triangle->vertices[_tri_i].vy*ccos( triangle->angle ))
            +(triangle->vertices[_tri_i].vx*csin( triangle->angle )))>>12) + (triangle->posy>>12);
    }

    setXY3( tri,
        tri_v[0].vx, tri_v[0].vy,
        tri_v[1].vx, tri_v[1].vy,
        tri_v[2].vx, tri_v[2].vy );
        
    addPrim( ord->ot[db], tri );
    ord->nextpri += sizeof(POLY_F3);
}


#endif