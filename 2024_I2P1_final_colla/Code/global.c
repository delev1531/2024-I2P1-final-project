#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 120.0;//60
const int WIDTH= 1400;//900;
const int HEIGHT = 900;//672;
//int window = 0;
int dead1 = 0;  
int dead2 = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool key_state2[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
//bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
//Point mouse;
//bool debug_mode = true;
char catChoice[4][20]={"TA cat", "ddl warrior","beauty cat","bucket god cat"};
char sceneChoice[4][80]={"homework problems that no one can solve", "night before deadline", "Good night miss", "I apologize but I'm rich"};
int catHP[5]={250,200,180,280,150};
int catspeed[5]={7,7,6,8,5};
int cathit[4]={20,25,30,15};
int window =0;
int projectile_exit=0;
int p1=-1,p2=-1;
int setted_scene=-1,winnerPl=-1,winnerCat=-1,loserPl=-1,loserCat=-1;