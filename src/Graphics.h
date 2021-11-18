#ifndef ORDERINGTABLE_H
#define ORDERINGTABLE_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#define OTLEN 8
typedef struct _ordering_table{
    u_long ot[2][OTLEN];
    char pribuff[2][32768];
    char *nextpri;
} OrderingTable;

void IncreaseOrderingTablePointer(OrderingTable* ord){
    *(ord->nextpri) += sizeof(TILE);
}

DISPENV disp[2];
DRAWENV draw[2];
int db = 0;

OrderingTable ord;

void display() {
    
    DrawSync(0);
    
    VSync(0);

    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);

    SetDispMask(1);

    DrawOTag(ord.ot[db]+OTLEN-1);
    
    db = !db;
    ord.nextpri = ord.pribuff[db];
    
}

void initGraphics(){
    ResetGraph(0);

    SetDefDispEnv(&disp[0], 0, 0, 320, 240);
    SetDefDrawEnv(&draw[0], 0, 240, 320, 240);

    SetDefDispEnv(&disp[1], 0, 240, 320, 240);
    SetDefDrawEnv(&draw[1], 0, 0, 320, 240);

    FntLoad(960, 0);
    FntOpen(0, 8, 320, 224, 0, 100);

    draw[0].isbg = 1;
    setRGB0(&draw[0], 255, 200, 202);
    draw[1].isbg = 1;
    setRGB0(&draw[1], 255, 200, 202);

    ord.nextpri = ord.pribuff[0];


    PutDrawEnv(&draw[!db]);


}


#endif