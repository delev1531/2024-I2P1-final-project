#ifndef CATFUNC_H_INCLUDED
#define CatFUNC_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>
/*
[Cat object]
*/
// typedef struct _cat{
//     int CatID;
//     int x, y; // the position of image
//     int width, height; // the width and height of image
//     int state; // the state of Cat
//     int wx,wy; //the position of its weapon

//     float vely; // velocity of image 
//     int speed; // moving speed

//     bool jump; // no:false, jump:true
//     bool dir; // left: false, right: true
//     bool dead;

//     ALGIF_ANIMATION *gif_image[6];
//     ALGIF_ANIMATION *weapon_image[1];
//     ALLEGRO_SAMPLE_INSTANCE *gif_sound[6]; //SAMPLE 
//     int anime; // counting the time of animation
//     int anime_time; // indicate how long the animation
//     Shape *hitbox; // the hitbox of object

//     bool new_proj;
// }Cat;

Elements *New_Cat(int playerid, int catid);
void Cat1_update(Elements *self);
void Cat2_update(Elements *self);
void Cat_interact(Elements *self, Elements *tar);
void Cat_draw(Elements *self);
void Cat_destory(Elements *self);
void _Cat_update_position(Elements *self, int dx, int dy,int return0);

#endif