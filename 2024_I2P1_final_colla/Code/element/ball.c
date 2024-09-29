// #include "ball.h"
// #include "../shapes/Circle.h"
// #include "../shapes/Shape.h"
// #include "../global.h"
// #include <allegro5/allegro_primitives.h>
// /*
//    [Ball function]
// */
// Elements *New_Ball(int label)
// {
//     Ball *pDerivedObj = (Ball *)malloc(sizeof(Ball));
//     Elements *pObj = New_Elements(label);
    
//     pDerivedObj->x = mouse.x;
//     pDerivedObj->y = mouse.y;
//     pDerivedObj->r = 10;
//     pDerivedObj->in = -1;
//     al_map_rgb(255,0,0);
//     pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);

//     //setting the interact object
//     pObj->inter_obj[pObj->inter_len++] =Character_L;
//     pObj->inter_obj[pObj->inter_len++] =Tree_L;
//     // setting derived object function
//     pObj->pDerivedObj = pDerivedObj;
//     pObj->Update = Ball_update;
//     pObj->Interact = Ball_interact;
//     pObj->Draw = Ball_draw;
//     pObj->Destroy = Ball_destory;
//     return pObj;
// }
// void Ball_update(Elements *self) {
//     Ball *Obj = ((Ball*)(self->pDerivedObj));
//     Shape *hitbox = Obj->hitbox;
//     hitbox ->update_center_x(hitbox,mouse.x -Obj->x);
//     hitbox ->update_center_y(hitbox,mouse.y -Obj->y);
//     Obj->x = mouse.x;
//     Obj->y = mouse.y;
// }
// void Ball_interact(Elements *self, Elements *tar) {
//     Ball *Obj = ((Ball*)(self->pDerivedObj));
//     if (tar->label == Character_L)
//     {
//         Character *Obj2 = ((Character *)(tar->pDerivedObj));
//         if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox)) {
//             Obj->c = al_map_rgb(0,255,0);
//             Obj->in =Character_L;
//         }
//         else if(Obj->in ==Character_L){
//             Obj->c = al_map_rgb(255,0,0);
//             Obj->in = -1;
//         }
//     }
//     else if (tar->label == Tree_L)
//     {
//         Tree *Obj2 = ((Tree *)(tar->pDerivedObj));
//         if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox)) {
//             Obj->c = al_map_rgb(0,0,255);
//             Obj->in =Tree_L;
//         }
//         else if(Obj->in ==Tree_L){
//             Obj->c = al_map_rgb(255,0,0);
//             Obj->in = -1;
//         }
//     }
// }
// void Ball_draw(Elements *self)
// {
//     Ball *Obj = ((Ball *)(self->pDerivedObj));
//     al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->c,5);
// }
// void Ball_destory(Elements *self)
// {
//     Ball *Obj = ((Ball *)(self->pDerivedObj));
//     free(Obj->hitbox);
//     free(Obj);
//     free(self);
// }
