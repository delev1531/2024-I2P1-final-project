#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/bloodbar.h"
#include "../element/catfunc.h"
#include "../element/ball.h"

typedef enum EleType
{
    //Ball_L,
    //Floor_L, 
    //Teleport_L,
    //Tree_L,
    //Character_L,
    Projectile1_L,
    Projectile2_L,
    Bloodbar1_L,
    Bloodbar2_L,
    P1_L,
    P2_L
    
} EleType;

typedef enum CatState
{
    STOP = 0,
    MOVE,
    ATK,
    JUMP,
    DEAD,
    HURT
} CatState;

typedef struct _cat{
    int CatID;
    int x, y,initial_y; // the position of image
    int width, height; // the width and height of image
    int state,forestate; // the state of Cat
    int wx,wy; //the position of its weapon

    float vely; // velocity of image 
    int speed; // moving speed

    bool jump,jumping; // no:false, jump:true
    bool dir; // left: false, right: true
    bool dead;
    double motiontime;
    ALLEGRO_BITMAP  *gif_image[6][2];
    ALLEGRO_SAMPLE_INSTANCE *gif_sound[2]; //SAMPLE 
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    Shape *hitbox; // the hitbox of object

    bool new_proj;
}Cat;

Cat* p1address,*p2address;

typedef struct _GameScene
{
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    bool gameover;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif




