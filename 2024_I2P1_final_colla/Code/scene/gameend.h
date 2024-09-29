#ifndef GAMEEND_H_INCLUDED
#define GAMEEND_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"


typedef struct _GameEnd
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    int select;
    ALLEGRO_BITMAP *gameend_image[2];

} GameEnd;
Scene *New_GameEnd(int label);
void gameend_update(Scene *self);
void gameend_draw(Scene *self);
void gameend_destroy(Scene *self);


#endif