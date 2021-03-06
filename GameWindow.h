#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>
#include <time.h>
#include "NPC.h"
#include "MainCharacter.h"
#include "Girl.h"
#include "Enemy.h"
#include "TerminateSet.h"
#include "Cursor.h"
#include "Menu.h"
#include "Master.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

#define medicine_price 300
#define medicine_available 1000
#define window_width 1200
#define window_height 800
#define map_width 3600
#define TIME_LEFT 3600                                                                 ///**********

// clock rate
const float FPS = 60;

class GameWindow
{
public:
    // constructor
    GameWindow();

    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();
    void draw_terminate_map();
    void draw_setting_map();

    // process of updated event
    int process_event();
    int Game_Status = GAME_SETTING;

    Girl* create_girl(int IsGoodLooking);
    Enemy* create_enemy(int IsGoodLooking);

    //+++
    void create_maincharacter();

    Master* create_master();


public:
    bool initial = true;

private:
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;

    ALLEGRO_BITMAP *ground = NULL;
    ALLEGRO_BITMAP *start = NULL;
    ALLEGRO_BITMAP *cur = NULL;
    ALLEGRO_BITMAP *medicine = NULL;
    const ALLEGRO_FONT *font;

    Menu *menu = NULL;

    std::vector<Girl*> Girl_Set;
    std::vector<Enemy*> Enemy_Set;

    int npc_CoolDown = 0, medicine_cooldown = 0;
    int npc_born_x = map_width, npc_born_y = 550;
    int map_x = 0, map_y = 0, map_speed;
    int Time_Left = TIME_LEFT;
    bool HaveGoodLookingGirl = false;
    bool HaveMaster = false;
    int FreezeTime = 0;
    int Hunt_Goodlooking = 0, Hunt_Normal = 0;

    //+++
    Master *master = NULL;
    MainCharacter* maincharacter;
    TerminateSet* terminate;
    Cursor* cursor;

};

#endif // GAMEWINDOW_H_INCLUDED
