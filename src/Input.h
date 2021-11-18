#ifndef INPUT_H
#define INPUT_H

#define PAD_SELECT      1
#define PAD_L3          2
#define PAD_R3          4
#define PAD_START       8
#define PAD_UP          16
#define PAD_RIGHT       32
#define PAD_DOWN        64
#define PAD_LEFT        128
#define PAD_L2          256
#define PAD_R2          512
#define PAD_L1          1024
#define PAD_R1          2048
#define PAD_TRIANGLE    4096
#define PAD_CIRCLE      8192
#define PAD_CROSS       16384
#define PAD_SQUARE      32768

u_char padbuff[2][34];

typedef struct _controller{
    unsigned char status;
    unsigned char len:4;
    unsigned char type:4;
    unsigned short button;
    unsigned char rightstick_x,rightstick_y;
    unsigned char leftstick_x,leftstick_y;
} Controller;

Controller controller1;

void initControllers(){
    InitPAD( padbuff[0], 34, padbuff[1], 34 );

    padbuff[0][0] = padbuff[0][1] = 0xff;
    padbuff[1][0] = padbuff[1][1] = 0xff;

    StartPAD();


}

#endif