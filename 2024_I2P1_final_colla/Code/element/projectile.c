#include "projectile.h"
#include "../shapes/Circle.h"
#include "../scene/gamescene.h" // for element label
#include <allegro5/allegro_primitives.h>
/*
   [Projectile function]
*/
Elements *New_Projectile(int label, int x, int y, int v)
{
    //printf("pp happy\n");
    projectile_exit++;
    Projectile *pDerivedObj = (Projectile *)malloc(sizeof(Projectile));
    Elements *pObj = New_Elements(label);
    //printf("%d\n",label);
    // setting derived object member
    char ppbuffer[100];

    if(label == Projectile1_L)sprintf(ppbuffer,"assets/image/projectile_%d.png",p1);
    else sprintf(ppbuffer,"assets/image/projectile_%d.png",p2);  

    pDerivedObj->img = al_load_bitmap(ppbuffer);
    pDerivedObj->width =al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height=al_get_bitmap_height(pDerivedObj->img);
    //printf("pp image done\n");
    pDerivedObj->x = x;
    pDerivedObj->y = y-pDerivedObj->height/2;
    pDerivedObj->v = v;
    pDerivedObj->vy = 0;
    if(label == Projectile1_L){
        if(p1==1 || p1==0)pDerivedObj->vy=-3;
    }
    else{
        if(p2==1 || p2==0)pDerivedObj->vy=-3;
    }

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width/2,
                                     pDerivedObj->y + pDerivedObj->height/2,
                                     min(pDerivedObj->width/2,pDerivedObj->height/2));
    if(pObj->label==Projectile2_L)pObj->inter_obj[pObj->inter_len++] = P1_L;
    else pObj->inter_obj[pObj->inter_len++] = P2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile_update;
    pObj->Interact = Projectile_interact;
    pObj->Draw = Projectile_draw;
    pObj->Destroy = Projectile_destory;
    //printf(" pp unhappy\n");
    return pObj;
}
void Projectile_update(Elements *self)
{
    //printf("update_p_ggg");
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    if(Obj->vy) Obj->vy+=0.025;
    else if(Obj->y<0) Obj->vy=0;
    _Projectile_update_position(self, Obj->v, Obj->vy);
    if(winnerPl > 0) {
        self->dele = true;
        projectile_exit--;
        //printf("(%d)",projectile_exit);
    }
}
void _Projectile_update_position(Elements *self, int dx, int dy)
{
    //printf("update_pos_ggg\n");
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
    if((Obj->x < 0)||(Obj->x > WIDTH)){
        //printf("projectile runs away!");
        projectile_exit--;
        self->dele = true;
    }
}
void Projectile_interact(Elements *self, Elements *tar)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    Cat* Obj2 = ((Cat*)tar->pDerivedObj);
    if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox)) {
        self->dele = true;
        projectile_exit--;
        //printf("(%d )",projectile_exit);
        //printf("projectile%d interact with cat%d",self->label-2,tar->label-4);
    }
    
}
void Projectile_draw(Elements *self)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    //al_draw_circle(Obj->x + Obj->width/2, Obj->y + Obj->height/2, min(Obj->width/2,Obj->height/2),al_map_rgb(255,0,0), 5);
    al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
}
void Projectile_destory(Elements *self){
    //printf("projectile destory,");
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
    //printf(" remain %d\n",projectile_exit);
}    

