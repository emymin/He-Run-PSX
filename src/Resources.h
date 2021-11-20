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

extern int road_left_texture[];
Texture road_left;
extern int road_right_texture[];
Texture road_right;

extern int car1_texture[];
Texture car1_texture_text;


Controller* controller;

int RAN;
int Random(int max)
{
	RAN = (rand()%max);
	return 0;
}