#ifndef BLOODBAR_H_INCLUDED
#define BLOODBAR_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../algif5/src/algif.h"
#include "../shapes/Shape.h"
#include "element.h"


typedef struct _blood{ 
    int forwhich,loss;
    float lx,ly;// left-up point of bloodbar
    float rx,ry; // right-down point of bloodbar
    float maxValue;  // Maximum value of the blood bar
    float value;  // Current value of the blood bar
    float hurttime,temptime;
    ALLEGRO_COLOR c; // the color
    ALLEGRO_FONT *font;
} BloodBar;

Elements *New_BloodBar(int label,int cattype);
void BloodBar_update(Elements *self);
void BloodBar_draw(Elements *self);
void BloodBar_destory(Elements *self);

#endif