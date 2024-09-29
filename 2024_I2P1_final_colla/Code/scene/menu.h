#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/

typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    int select;
    ALLEGRO_BITMAP *background,*p1menu;
} Menu;

Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu1_update(Scene *self);
void menu2_update(Scene *self);
void menu3_update(Scene *self);
void menu_draw(Scene *self);
//void menu_select(Scene *self);
void menu_destroy(Scene *self);

#endif 
