#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
# include "gameend.h"


Scene *New_GameEnd(int label)
{
    //printf("gameend scene included || ");
    //printf("winner player %d  ",winnerPl);
    GameEnd *pDerivedObj = (GameEnd*)malloc(sizeof(GameEnd));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    //加載字體和音效資源，並設置相關成員。
    //設置標題的位置為螢幕的中心。
    pDerivedObj->font = al_load_ttf_font("assets/font/ugly.ttf", 18, 0);
    char buffer[150],buffer1[150];
    if(winnerPl==1) {
        sprintf(buffer, "assets/image/pcat_%d%s0.png", p1,"attack");
        sprintf(buffer1, "assets/image/pcat_%d%s0.png", p2,"dead");
        pDerivedObj->background = al_load_bitmap("assets/image/2.jpg");
    }
    else{
        sprintf(buffer, "assets/image/pcat_%d%s0.png", p2,"attack");
        sprintf(buffer1, "assets/image/pcat_%d%s0.png", p1,"dead");
        pDerivedObj->background = al_load_bitmap("assets/image/1.jpg");
    }
    
    pDerivedObj->gameend_image[0] = al_load_bitmap(buffer); 
    pDerivedObj->gameend_image[1] = al_load_bitmap(buffer1); 

    
    
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/gameend_bgm.wav");
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
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = gameend_update;
    pObj->Draw = gameend_draw;
    pObj->Destroy = gameend_destroy;
    return pObj;
}

void gameend_update(Scene *self) { //指向當前場景的指標，表示函數正在更新哪個場景
    if (key_state[ALLEGRO_KEY_ENTER]){
        self->scene_end = true;
        window =0;
    }
    else if (key_state[ALLEGRO_KEY_ESCAPE]){ 
        self->scene_end = false;
        window = -1;
    }
    return;
}

void gameend_draw(Scene *self){
    //printf("1232432423\n");
    GameEnd *Obj = ((GameEnd *)(self->pDerivedObj));
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), WIDTH/2, 4*HEIGHT/5, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to restart"); 
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), WIDTH/2, 4*HEIGHT/5-30, ALLEGRO_ALIGN_CENTRE, "Press 'ESC' to ended the game");  // change
    
    char buffer1[50],buffer2[50];
    sprintf(buffer1,"player %d (%s) wins! :)",winnerPl,catChoice[winnerCat]);
    sprintf(buffer2,"player %d (%s) loses! hahaha XD",loserPl,catChoice[loserCat]);
    al_draw_text(Obj->font, al_map_rgb(255, 0,0), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, buffer1);
    al_draw_text(Obj->font, al_map_rgb(255, 0, 255), Obj->title_x, Obj->title_y-50, ALLEGRO_ALIGN_CENTRE, buffer2);    
    al_draw_bitmap(Obj->background,0,0,0);

    if(winnerPl==1){
        //printf("23e\n");
        al_draw_bitmap(Obj->gameend_image[0], 10, 350, 0);
        al_draw_bitmap(Obj->gameend_image[1], 900, 200, ALLEGRO_FLIP_HORIZONTAL);
    }
    if(winnerPl==2){
        //printf("23434e\n");
        al_draw_bitmap(Obj->gameend_image[1], 10, 200, 0);
        al_draw_bitmap(Obj->gameend_image[0], 900, 350, ALLEGRO_FLIP_HORIZONTAL);
    }
    al_play_sample_instance(Obj->sample_instance);
}

void gameend_destroy(Scene *self){
    winnerPl=-1;
    loserPl=-1;
    winnerCat=-1;
    loserCat=-1;
    GameEnd *Obj = ((GameEnd *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->background);
    for(int i=0;i<=1;i++) al_destroy_bitmap(Obj->gameend_image[i]);
    free(Obj);
    free(self);
}