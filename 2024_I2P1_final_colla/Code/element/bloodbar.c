#include "bloodbar.h"
#include <allegro5/allegro_primitives.h>
#include"../shapes/Rectangle.h"
#include "catfunc.h"
#include "../scene/gamescene.h"


//create BloodBar
Elements *New_BloodBar(int label,int cattype)
{
    BloodBar *pDerivedObj = (BloodBar *)malloc(sizeof(BloodBar));
    Elements *pObj = New_Elements(label);
    pDerivedObj->font = al_load_ttf_font("assets/font/ugly.ttf", 35, 0);
    pDerivedObj->forwhich=label;
    // initial BloodBar
    if(label==Bloodbar1_L){ 
        pDerivedObj->loss = cathit[p2];
        pDerivedObj->lx = WIDTH/36;
        pDerivedObj->rx = WIDTH/3.93; 
    }
    if(label==Bloodbar2_L){
        pDerivedObj->loss = cathit[p1];
        pDerivedObj->lx = WIDTH/1.345;
        pDerivedObj->rx = WIDTH/1.037;
    }
    pDerivedObj->c = al_map_rgb(255,106,106);
    pDerivedObj->ly = 40.5;
    pDerivedObj->ry = 77;
    pDerivedObj->hurttime=0;
    pDerivedObj->temptime=0;
    pDerivedObj->maxValue = catHP[cattype];
    pDerivedObj->value = catHP[cattype];
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = BloodBar_update;
    pObj->Draw = BloodBar_draw;
    pObj->Destroy = BloodBar_destory;
    return pObj;
}

void BloodBar_update(Elements *self){
    BloodBar *Obj = ((BloodBar*)(self->pDerivedObj));
    Cat* selfCat_c;

    if(Obj->temptime) {
        if(al_get_time() < Obj->temptime+0.2)Obj->c =al_map_rgb(0,171,169);
        else Obj->c =al_map_rgb(255,106,106);
    }

    if(Obj->forwhich==Bloodbar1_L) selfCat_c = ((Cat*) p1address);    
    else selfCat_c = ((Cat*) p2address); 
    
    if(winnerPl<0){
            if(selfCat_c->state == HURT){
            if(setted_scene == selfCat_c->CatID) {
                Obj->hurttime = al_get_time();
                //printf(" get time %f ",Obj->hurttime);
            }
            Obj->value -= Obj->loss;
            selfCat_c->state =STOP;
            //printf("%d(%d %f)", Obj->forwhich-2, selfCat_c->state, Obj->value);
        }
        //if(Obj->hurttime) printf("now time %f ",al_get_time());
        if(al_get_time() >= 0.5 + Obj->hurttime && Obj->hurttime!=0){
            //printf("recover! ");
            Obj->value*=1.02;
            Obj->hurttime =0;
            Obj->temptime =al_get_time();
        } 
        if(Obj->value <= 0){
            if(self->label==Bloodbar2_L) {
                winnerPl=1;
                winnerCat =p1;
                loserPl=2;
                loserCat=p2;
            }
            else {
                winnerPl=2;
                winnerCat = p2;
                loserPl=1;
                loserCat=p1;
            }
        }
    }

}

void BloodBar_draw(Elements *self){
    BloodBar *Obj = ((BloodBar *)(self->pDerivedObj));
    float remain = (Obj->value/Obj->maxValue)*(Obj->rx - Obj->lx); //new percent of blood
    char buffer[20];
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"%3.1f",Obj->value);
    if(self->label==Bloodbar1_L){
        al_draw_filled_rectangle(Obj->lx, Obj->ly, Obj->lx + remain, Obj->ry, Obj->c);
        al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->lx +314 +50, Obj->ly+5 , ALLEGRO_ALIGN_CENTRE, buffer);
    }
    if(self->label==Bloodbar2_L){
        al_draw_filled_rectangle(Obj->rx-remain, Obj->ly, Obj->rx, Obj->ry,Obj->c);
        al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->rx-314-50, Obj->ly+5, ALLEGRO_ALIGN_CENTRE, buffer);
    }
    al_draw_rectangle(Obj->lx, Obj->ly, Obj->lx +314, Obj->ly+35, al_map_rgb(255, 255, 255), 4);
}

void BloodBar_destory(Elements *self){
    BloodBar *Obj = ((BloodBar *)(self->pDerivedObj));
    free(Obj);
    free(self);
}
