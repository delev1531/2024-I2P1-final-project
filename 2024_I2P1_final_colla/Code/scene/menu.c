#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
# include"../global1.h"
/*
   [Menu function]
    choice 1 2 3 4
    p1 a d w s 
    p2 h k u j
    scene 1 2 3 4

*/

Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    //加載字體和音效資源，並設置相關成員。
    //設置標題的位置為螢幕的中心。
    pDerivedObj->font = al_load_ttf_font("assets/font/ugly.ttf", 35, 0);
    char buffer[100]={'\0'};
    sprintf(buffer,"assets/image/menu%d.jpg",label);
    pDerivedObj->background = al_load_bitmap(buffer);
    if(label==2){
        memset(buffer,'\0',sizeof(buffer));
        sprintf(buffer,"assets/image/pcat_%dstop0.png",p1);
        pDerivedObj->p1menu =al_load_bitmap(buffer);
    }

    // Load sound
    sprintf(buffer,"assets/sound/menu%d_bgm.wav",label);
    pDerivedObj->song = al_load_sample(buffer);
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = 1*HEIGHT / 4;
    pDerivedObj->select =0;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    if(label==0) pObj->Update = menu_update;
    else if(label==1) pObj->Update = menu1_update;
    else if(label==2) pObj->Update = menu2_update;
    else if(label==3) pObj->Update = menu3_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}

void menu_update(Scene *self) { //指向當前場景的指標，表示函數正在更新哪個場景
    if (key_state[ALLEGRO_KEY_ENTER]){
        self->scene_end = true;
        window++;
    }
    return;
}

void menu1_update(Scene *self){
    if(key_state[ALLEGRO_KEY_A]){
        p1=0;
        self->scene_end = true;
        window++;
    }
     else if(key_state[ALLEGRO_KEY_D]) {
        p1=1;
        self->scene_end = true;
        window++;
    }
    else if(key_state[ALLEGRO_KEY_W]) {
        p1=2;
        self->scene_end = true;
        window++;
        }
    else if(key_state[ALLEGRO_KEY_S])  {
        p1=3;
        self->scene_end = true;
        window++;
    }
}
void menu2_update(Scene *self){
    if(key_state[ALLEGRO_KEY_H]){
        p2=0;
        self->scene_end = true;
        window++;
    }
     else if(key_state[ALLEGRO_KEY_K]) {
        p2=1;
        self->scene_end = true;
        window++;
    }
    else if(key_state[ALLEGRO_KEY_U]) {
        p2=2;
        self->scene_end = true;
        window++;
    }
    else if(key_state[ALLEGRO_KEY_J])  {
        p2=3;
        self->scene_end = true;
        window++;
    }
}
void menu3_update(Scene *self){
    if(key_state[ALLEGRO_KEY_1]){
        setted_scene=0;
        self->scene_end = true;
        window++;
    }
     else if(key_state[ALLEGRO_KEY_2]) {
        setted_scene=1;
        self->scene_end = true;
        window++;
    }
    else if(key_state[ALLEGRO_KEY_3]) {
        setted_scene=2;
        self->scene_end = true;
        window++;
        }
    else if(key_state[ALLEGRO_KEY_4])  {
        setted_scene=3;
        self->scene_end = true;
        window++;
    }
}


void menu_draw(Scene *self){
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    if(self->label==0){
        al_draw_bitmap(Obj->background, 0, 0, 0);
        al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y-125, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");      
        al_draw_rectangle(Obj->title_x - 180, Obj->title_y -150, Obj->title_x + 180, Obj->title_y -70, al_map_rgb(255, 255, 255), 3);
    }
    else if(self->label==1){
        al_draw_bitmap(Obj->background, 0, 0, 0);
        //al_draw_text(Obj->font, al_map_rgb(255, 255, 255),2*WIDTH/5, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "please select a character for player 1");        
    }
    else if(self->label==2){
        al_draw_bitmap(Obj->background, 0, 0, 0);
        al_draw_bitmap(Obj->p1menu, 0, 350, 0);
        //al_draw_text(Obj->font, al_map_rgb(255, 255, 255),2*WIDTH/5, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "please select a character for player 2");
        al_draw_text(Obj->font, al_map_rgb(225,225,225),2*WIDTH/12, 2*HEIGHT/6, ALLEGRO_ALIGN_CENTRE,catChoice[p1]);
    }
    if(self->label==3){
        al_draw_bitmap(Obj->background, 0, 0, 0);
        //al_draw_text(Obj->font, al_map_rgb(255, 255, 255),2*WIDTH/5, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "please select the game scene");
        //al_draw_text(Obj->font, al_map_rgb(255, 255, 255),2*WIDTH/5, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE,catChoice[p1]);
        //al_draw_text(Obj->font, al_map_rgb(255, 255, 255),4*WIDTH/5, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE,catChoice[p2]);
    }
    al_play_sample_instance(Obj->sample_instance);
}

void menu_destroy(Scene *self){
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
