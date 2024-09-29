#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "gameend.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case Menu1_L:
        scene = New_Menu(Menu1_L);
        break;
    case Menu2_L:
        //printf("after menu 1\n");
        //printf("player1 is %d\n",p1);
        //printf("player2 is %d\n",p2);
        //printf("setted scene as %d\n",setted_scene);
        scene = New_Menu(Menu2_L);
        break;
    case Menu3_L:
        //printf("after menu 2\n");
        //printf("player1 is %d\n",p1);
        //printf("player2 is %d\n",p2);
        //printf("setted scene as %d\n",setted_scene);
        scene = New_Menu(Menu3_L);
        break;
    case GameScene_L:
        //printf("after menu 3\n");
        //printf("player1 is %d\n",p1);
        //printf("player2 is %d\n",p2);
        //printf("setted scene as %d\n",setted_scene);
        scene = New_GameScene(GameScene_L);
        break;
    case GameEnd_L:
        //printf("game end scene_sceneManager");
        scene = New_GameEnd(GameEnd_L);
        break;
    default:
        break;
    }
}
