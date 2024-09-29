#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    Menu1_L ,
    Menu2_L ,
    Menu3_L ,
    GameScene_L,
    GameEnd_L
} SceneType;
void create_scene(SceneType);

#endif