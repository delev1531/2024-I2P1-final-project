#include "catfunc.h"
#include "../scene/sceneManager.h"
#include "../scene/gamescene.h" // for element label
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro_primitives.h>
/*
   [Cat function]
    PLAYER  MOVE  JUMP  ATK  SPEEDUP
     1      A,D    W    X      S
     2      H,K    U    M      J

*/
Elements *New_Cat(int playerid, int catid)
{
    //printf(" palyer : %d cat:%d\n", playerid, catid);
    Cat *pDerivedObj = (Cat *)malloc(sizeof(Cat));
    Elements *pObj = New_Elements(playerid);

    if(playerid==P1_L) p1address=pDerivedObj;
    else p2address=pDerivedObj;

    // setting derived object member
    pDerivedObj->CatID = catid; 
    pDerivedObj->speed = catspeed[catid]; 
    pDerivedObj->dead = false;
    pDerivedObj->jumping = false;
    //printf("before image loading:\n");
    char state_string[6][10] = {"stop", "move", "attack", "jump", "dead", "hurt"};
    for (int i = 0; i < 6; i++)
    {
        //printf("%d ",i);
        char buffer[150];
        memset(buffer,'\0',sizeof(buffer));
        // load cat images
        //printf("%d%d ",i,i);
        sprintf(buffer, "assets/image/pcat_%d%s0.png", catid, state_string[i]);
        pDerivedObj->gif_image[i][0] = al_load_bitmap(buffer); 
        memset(buffer,'\0',sizeof(buffer));
        sprintf(buffer, "assets/image/pcat_%d%s1.png", catid, state_string[i]);
        pDerivedObj->gif_image[i][1] = al_load_bitmap(buffer); 

        // load effective sound
        if (i ==2 || i==3) { // sound effct only in sttack and jump state
            memset(buffer,'\0',sizeof(buffer));
            sprintf(buffer, "assets/sound/pcat_%d%s.wav", catid, state_string[i]);
            ALLEGRO_SAMPLE *sample = al_load_sample(buffer); 
            int audiotemp;
            if(i==2) audiotemp =0;
            else audiotemp = 1;
            pDerivedObj->gif_sound[audiotemp] = al_create_sample_instance(sample); 
            
            al_set_sample_instance_playmode(pDerivedObj->gif_sound[audiotemp], ALLEGRO_PLAYMODE_ONCE); 
            al_attach_sample_instance_to_mixer(pDerivedObj->gif_sound[audiotemp], al_get_default_mixer()); 
            //printf("sound %s loading finished\n",buffer);
        }
    } 

    // initial the geometric information of cat
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->gif_image[0][0]);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->gif_image[0][0]);

    if (playerid == P1_L) pDerivedObj->x =10; 
    else {pDerivedObj->x = 900;}
    pDerivedObj->y =320; 

    //pDerivedObj->y = HEIGHT/2;//HEIGHT - player->height - 10;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x+200,
                                        pDerivedObj->y+70,
                                        pDerivedObj->x + pDerivedObj->width-200,
                                        pDerivedObj->y + pDerivedObj->height);
    
    if (playerid == P1_L) pDerivedObj->dir = true; 
    else pDerivedObj->dir = false;

    pDerivedObj->jump = false;

    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->forestate = STOP; 
    pDerivedObj->anime = 0; 
    pDerivedObj->anime_time = 1;
    pDerivedObj->motiontime = 0;
    pDerivedObj->new_proj = false; 
    pObj->pDerivedObj = pDerivedObj; //？
    // setting derived object function
    pObj->Draw = Cat_draw; 

    if (playerid == P1_L){ //see gamescene.h: P1_L=8
        pObj->Update = Cat1_update; 
        pObj->inter_obj[pObj->inter_len++] =P2_L; //setting the interact object
        pObj->inter_obj[pObj->inter_len++] =Projectile2_L;
    } 
    else{
        pObj->Update = Cat2_update;
        pObj->inter_obj[pObj->inter_len++] =P1_L;
        pObj->inter_obj[pObj->inter_len++] =Projectile1_L;
    }
    pObj->Interact = Cat_interact; 
    pObj->Destroy = Cat_destory;
    return pObj;
}

void Cat1_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Cat *pcat = ((Cat *)(self->pDerivedObj));
    if(winnerPl==2) pcat->state = DEAD;

    else if (key_state[ALLEGRO_KEY_X]) {
        pcat->state = ATK;
        pcat->forestate=ATK;
    }
 
    else if (key_state[ALLEGRO_KEY_A])
    {
        pcat->dir = false;
        pcat->forestate=MOVE;
        _Cat_update_position(self, -5, 0,0);
        pcat->state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_D])
    {
        pcat->dir = true;
        pcat->forestate=MOVE;
        _Cat_update_position(self, 5, 0,0);
        pcat->state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_W])//&& pcat->jump
    {
        if(!pcat->jump){
           // printf("Jump\n");
            pcat->state = JUMP;
            pcat->jumping =true;
            pcat->jump = true;
        }
    }
    else {
        if(!pcat->jumping){
            pcat->state = STOP;
            pcat->vely=0;
        }
        pcat->new_proj = false;
    }
    
    if (pcat->state == ATK)
    {
        pcat->forestate =ATK;
        if (pcat->new_proj == false)
        {
            Elements *pro;
            if (pcat->dir) pro = New_Projectile(Projectile1_L, pcat->x +pcat->width, pcat->y + pcat->height/2,3); //投射物的初始 x 座標 5是指水平向右速度
            else pro = New_Projectile(Projectile1_L, pcat->x, pcat->y + pcat->height/2, -3); // 向左速度
            //printf("I FLOOW THE WEAPON1\n");
            _Register_elements(scene, pro);
            pcat->new_proj = true;
        }
    }
    else if (pcat->jump || pcat->jumping)
    {
        printf("\n%d %d ||",pcat->jump,pcat->jumping);
        if(pcat->jump){
            pcat->vely = -5;
            pcat->jump=false;
        }
         // negative is jump upwaed
        _Cat_update_position(self, 0, pcat->vely,0);
        //printf("(state = %d, vely=%f, y= %d) ",pcat->state,pcat->vely,pcat->y);
        if(pcat->vely<=5){
            pcat->state = JUMP;
            pcat->vely+= 0.25;
            //printf("(state = %d, vely=%f, y= %d) ",pcat->state,pcat->vely,pcat->y);
            _Cat_update_position(self, 0, pcat->vely,0);
        }
        if(pcat->vely>=5){
            //printf("(state = %d, vely=%f, y= %d)",pcat->state,pcat->vely,pcat->y);
            _Cat_update_position(self, 0, 0,1);
            pcat->vely = 0;
            pcat->motiontime=0;
            pcat->jumping=false;
            pcat->forestate = JUMP;
            pcat->state = STOP;
        }

    }
}

void Cat2_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Cat *pcat = ((Cat *)(self->pDerivedObj));

    if(winnerPl==1) pcat->state = DEAD;

    if (key_state[ALLEGRO_KEY_N]) {
        pcat->state = ATK;
        pcat->forestate=ATK;
    }
    else if (key_state[ALLEGRO_KEY_H])
    {
        pcat->dir = false;
        _Cat_update_position(self, -5, 0,0);
        pcat->state = MOVE;
        pcat->forestate=MOVE;
    }
    else if (key_state[ALLEGRO_KEY_K])
    {
        pcat->dir = true;
        _Cat_update_position(self, 5, 0,0);
        pcat->state = MOVE;
        pcat->forestate=MOVE;
    }
    else if (key_state[ALLEGRO_KEY_U])//&& pcat->jump
    {
        if(!pcat->jump){
            pcat->state = JUMP;
            pcat->jumping = true;
            pcat->jump = true;
        }
    }
    else{
        if(!pcat->jumping){
            pcat->state = STOP;
            pcat->vely=0;
        }
        pcat->new_proj = false;
    }
    if (pcat->state == ATK)
    {
        if (pcat->new_proj == false)
        {
            Elements *pro;
            if (pcat->dir) pro = New_Projectile(Projectile2_L, pcat->x+pcat->width, pcat->y + pcat->height/2,3); //投射物的初始 x 座標 5是指水平向右速度
            else pro = New_Projectile(Projectile2_L, pcat->x,pcat->y + pcat->height/2,-3); // 向左速度
            //printf("I FLOOW THE WEAPON22\n");
            _Register_elements(scene, pro);
            pcat->new_proj = true;
        }
    }
    else if (pcat->jump || pcat->jumping)
    {
        //printf("\n%d %d ||",pcat->jump,pcat->jumping);
        if(pcat->jump){
            pcat->vely = -5;
            pcat->jump=false;
        }
         // negative is jump upwaed
        _Cat_update_position(self, 0, pcat->vely,0);
        //printf("(state = %d, vely=%f, y= %d) ",pcat->state,pcat->vely,pcat->y);
        if(pcat->vely<=5){
            pcat->state = JUMP;
            pcat->vely+= 0.25;
            //printf("(state = %d, vely=%f, y= %d) ",pcat->state,pcat->vely,pcat->y);
            _Cat_update_position(self, 0, pcat->vely,0);
        }
        if(pcat->vely>=5){
            //printf("(state = %d, vely=%f, y= %d)",pcat->state,pcat->vely,pcat->y);
            _Cat_update_position(self, 0, 0,1);
            pcat->vely = 0;
            pcat->jumping=false;
            pcat->motiontime=0;
            pcat->forestate = JUMP;
            pcat->state = STOP;
        }

    }
}

void Cat_draw(Elements *self)
{
    // with the state, draw corresponding image
    Cat *pcat = ((Cat *)(self->pDerivedObj));
    //al_draw_rectangle(pcat->x+200, pcat->y+70, pcat->x + pcat->width-200, pcat->y+pcat->height,al_map_rgb(255, 0,0), 0);
    if(pcat->state==STOP){
        if(pcat->forestate==HURT){
            if(al_get_time() < pcat->motiontime+0.2) al_draw_bitmap(pcat->gif_image[HURT][0], pcat->x, pcat->y, ((self->label==P2_L) ? ALLEGRO_FLIP_HORIZONTAL : 0));
            else if(al_get_time() < pcat->motiontime +0.4)al_draw_bitmap(pcat->gif_image[pcat->forestate][1], pcat->x, pcat->y, ((self->label==P2_L) ? ALLEGRO_FLIP_HORIZONTAL : 0));
            else {
                pcat->motiontime=0;
                pcat->forestate =STOP;
            }
        }
        else if(pcat->motiontime!=0) {
            if(al_get_time() < pcat->motiontime+0.4)  {
                al_draw_bitmap(pcat->gif_image[pcat->forestate][1], pcat->x, pcat->y, ((!pcat->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
            }
            else {
                pcat->motiontime=0;
                al_draw_bitmap(pcat->gif_image[pcat->forestate][1], pcat->x, pcat->y, 0);
            }
        }
        else al_draw_bitmap(pcat->gif_image[STOP][1], pcat->x, pcat->y, 0);
    }

    else {
        if(pcat->state!=JUMP){
            al_draw_bitmap(pcat->gif_image[pcat->state][0], pcat->x, pcat->y, ((!pcat->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
            pcat->motiontime = al_get_time();
        }
        else{
            if(al_get_time()<pcat->motiontime+0.3)  al_draw_bitmap(pcat->gif_image[JUMP][0], pcat->x, pcat->y, ((!pcat->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
            else  al_draw_bitmap(pcat->gif_image[JUMP][1], pcat->x, pcat->y, 0);
        }
    }
    //soung effects settings
    if (pcat->state == ATK) al_play_sample_instance(pcat->gif_sound[0]);
    else if (pcat->state == JUMP) al_play_sample_instance(pcat->gif_sound[1]);
}


void Cat_destory(Elements *self)
{
    Cat *Obj = ((Cat *)(self->pDerivedObj)); 
    for(int i=0;i<=1;i++) al_destroy_sample_instance(Obj->gif_sound[i]);
    for (int i = 0; i < 6; i++) {
        al_destroy_bitmap(Obj->gif_image[i][0]);
        al_destroy_bitmap(Obj->gif_image[i][1]);
    }
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Cat_update_position(Elements *self, int dx, int dy,int return0)
{
    Cat *pcat = ((Cat *)(self->pDerivedObj));
    if(return0) dy=320-pcat->y;
    pcat->x += dx;
    pcat->y += dy;
    Shape *hitbox = pcat->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Cat_interact(Elements *self, Elements *tar)
{
    Cat *Obj = ((Cat*)(self->pDerivedObj));

    int target;
    if(self->label == P1_L){
        if(tar->label == Projectile2_L) target = 1;
        if(tar->label == P2_L) target = 2;
    }
    else{
        if(tar->label == Projectile1_L) target = 1;
        if(tar->label == P1_L) target = 2;
    }

    if (target == 1)
    {
        Projectile *Obj2 = ((Projectile *)(tar->pDerivedObj));
        if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox)) {
            Obj->state = HURT;
            Obj->forestate =HURT;
            Obj->motiontime = al_get_time();
            //printf("%d is hurt",self->label-4);
        }
    } 
    else if (target==2)
    {
        Cat *Obj2 = ((Cat *)(tar->pDerivedObj));
        if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox) && Obj2->state == ATK) {
            Obj->state = HURT;
            Obj->forestate =HURT;
            Obj->motiontime = al_get_time();
        }
    }
}
