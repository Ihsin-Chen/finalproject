#include "GameWindow.h"
#include <iostream>

bool key_state[1000];

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL) show_err_msg(-1);

    if (display == NULL || event_queue == NULL) show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    /// load font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    Game_Status = GAME_SETTING;

    game_init();
}

void
GameWindow::game_init()
{
    ground = al_load_bitmap("./background/street.png");
    font = al_load_ttf_font("pirulen.ttf",40,0);
    start = al_load_bitmap("./background/start_map.png");
    cur = al_load_bitmap("./character/cursor.png");
    medicine = al_load_bitmap("./character/medicine.png");

    menu = new Menu();

    /// load image and sound
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }

    if(Game_Status == GAME_SETTING)
    {
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            key_state[event.keyboard.keycode] = true;
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    if (cursor->getX() == 100)
                        ground = al_load_bitmap("./background/street.png");
                    else if (cursor->getX() == 450)
                        ground = al_load_bitmap("./background/school.png");
                    else ground = al_load_bitmap("./background/farm.png");
                    al_start_timer(timer);
                    Game_Status = GAME_CONTINUE;
                    break;
                case ALLEGRO_KEY_LEFT:
                    cursor->Move_Left();
                    break;
                case ALLEGRO_KEY_RIGHT:
                    cursor->Move_Right();
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        key_state[event.keyboard.keycode] = false;
        draw_setting_map();
    }

    else if (Game_Status == GAME_CONTINUE)
    {
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(event.timer.source == timer)
            {
                instruction = game_update();
                draw_running_map();
                /// to do when timer edges come
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            key_state[event.keyboard.keycode] = true;
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_P:
                    /*TODO: handle pause event here*/
                    if (al_get_timer_started(timer)) al_stop_timer(timer);
                    else al_start_timer(timer);
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    Game_Status = GAME_SETTING;
                    game_reset();
                    al_stop_timer(timer);
                    break;
                case ALLEGRO_KEY_C:
                    if (medicine_cooldown == 0 && menu->getScore()>= medicine_price)
                    {
                        menu->BuyMedicine(medicine_price);
                        maincharacter->MedicineInitiate(3);
                        medicine_cooldown ++;
                    }
                    break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
            key_state[event.keyboard.keycode] = false;

        if ((Girl_Set.size() < 6 && npc_CoolDown > 240)|| Girl_Set.size() == 0)
        {
            Girl* n = NULL;
            Enemy* e = NULL;
            if(menu->getScore() % 500 == 0 && menu->getScore() && !HaveGoodLookingGirl)
            {
                n = create_girl(1);
                HaveGoodLookingGirl = true;
            }
            else n = create_girl(0);

            if (Enemy_Set.size() < 3 && menu->getScore() >= 300)
            {
                if (Enemy_Set.size() == 2) e = create_enemy(1);
                else e = create_enemy(0);
                Enemy_Set.push_back(e);
            }
            Girl_Set.push_back(n);
            npc_CoolDown = 0;
        }

        if(!(menu->getScore() % 700)&& menu->getScore() && !HaveMaster)
        {
            master = create_master();
            HaveMaster = true;
        }

        if (Time_Left <= 0)
        {
            Game_Status = GAME_TERMINATE;
            terminate = new TerminateSet(menu->getScore());
        }

    }

    if (Game_Status == GAME_TERMINATE)
    {
        draw_terminate_map();
        al_stop_timer(timer);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            key_state[event.keyboard.keycode] = true;
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    game_reset();
                    Game_Status = GAME_SETTING;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        key_state[event.keyboard.keycode] = false;
    }

    npc_CoolDown ++;
    return instruction;
}

void GameWindow::create_maincharacter()
{
    maincharacter = new MainCharacter(100, 450);
}

Enemy* GameWindow :: create_enemy(int IsGoodLooking)
{
    Enemy* e = new Enemy(npc_born_x, 600,IsGoodLooking);

    // if (npc_born_x == map_width) npc_born_x -= map_width;
    // else npc_born_x += map_width;

    return e;
}

Girl* GameWindow :: create_girl(int IsGoodLooking)
{
    Girl* n = new Girl(npc_born_x, npc_born_y,IsGoodLooking);

    if (npc_born_x == map_width) npc_born_x -= map_width;
    else npc_born_x += map_width;

    return n;
}

Master* GameWindow :: create_master()
{
    Master *m = new Master(npc_born_x, 450);
    return m;
}

void
GameWindow::game_begin()
{
    printf(">>> Start\n");

    draw_setting_map();

    //al_play_sample_instance(startSound);
    //while(al_get_sample_instance_playing(startSound));
    //al_play_sample_instance(backgroundSound);

//<<<<<<< HEAD
    al_start_timer(timer);

//=======
    //al_start_timer(timer);
//>>>>>>> d183356cbe186e7e4902099af4627d7e2768fb48
}

int
GameWindow::game_update()
{
    bool OutOfRange = false;

    if (map_x < -2300 || map_x > 0)
    {
        OutOfRange = true;
        if(map_x < -2300) map_x = -2300;
        else map_x = 0;
    }

    if (!OutOfRange)
    {
        map_speed = -maincharacter->GetSpeed();
        if (map_x == -2300 || map_x == 0) map_speed /= 5;
        map_x += map_speed;
    }


    for(std::vector <Girl*>::iterator it = Girl_Set.begin(); it != Girl_Set.end(); it++)
    {
        (*it)->Move();
        (*it)->CoolDown();
    }

    for(std::vector <Enemy*>::iterator it = Enemy_Set.begin(); it != Enemy_Set.end(); it++)
    {
        (*it)->Move();
    }

    if(HaveMaster) master->Move();

    if(HaveMaster)
    {
        if(master->DetectAttack(maincharacter, map_x))
        {
        master->TriggerAttack(maincharacter);
        FreezeTime = 100;
        }
    }

    if(key_state[ALLEGRO_KEY_LEFT] && key_state[ALLEGRO_KEY_RIGHT]) maincharacter->Pause();
    else if(key_state[ALLEGRO_KEY_LEFT] && !maincharacter->Freeze) maincharacter-> MoveLeft(map_x);
    else if(key_state[ALLEGRO_KEY_RIGHT] && !maincharacter->Freeze) maincharacter-> MoveRight(map_x);
    else maincharacter-> Pause();

    if(key_state[ALLEGRO_KEY_SPACE] && !maincharacter->Freeze)
    {
        maincharacter->IsAttacking = true;
            int i = 0;

        for(std::vector <Girl*>::iterator it = Girl_Set.begin(); it != Girl_Set.end(); ++it)
        {
            i++;
            Girl* girl = *it;
            if (maincharacter->DetectAttack(*it,map_x))
            {
                std :: cout << i << " " << (*it)->GetHealth() << std::endl;
                (*it)->IsAttacking = true;

                for(std::vector <Enemy*>::iterator itt = Enemy_Set.begin(); itt != Enemy_Set.end(); itt++)
                {
                    if ((*itt)->DetectAttack(*it,map_x))
                    {
                        std :: cout << "Attack " << std :: endl;
                        (*itt)->TriggerAttack(*it);
                    }
                }

                if(maincharacter->TriggerAttack(*it))
                {
                    if ((*it)->GetSpeed() == 2) // Normal Girl
                    {
                        menu->Change_Coin(10);
                        menu->Gain_Score(100);
                    }
                    else                        // IsGoodLooking
                    {
                        menu->Change_Coin(30);
                        menu->Gain_Score(300);
                        HaveGoodLookingGirl = false;
                    }
                    Girl_Set.erase(it);
                    --it;
                    delete(girl);
                }
                break;
            }
        }
    }
    else
    {
        maincharacter->IsAttacking = false;
        for(std::vector <Enemy*>::iterator itt = Enemy_Set.begin(); itt != Enemy_Set.end(); itt++)
            (*itt)->StatusReset();
        for(std::vector <Girl*>::iterator it = Girl_Set.begin(); it != Girl_Set.end(); ++it)
            (*it)->StatusReset();
    }

    if(FreezeTime > 0) FreezeTime--;
    else maincharacter->Freeze = false;

    if (medicine_cooldown > 0 && medicine_cooldown <= medicine_available)
    {
        medicine_cooldown ++;
        if (medicine_cooldown == medicine_available)
        {
            maincharacter->MedicineOver(3);
            medicine_cooldown == 0;
        }
    }

    Time_Left--;
    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{

    /// stop sample instance
    //al_stop_sample_instance(startSound);

    /// stop timer

    al_stop_timer(timer);
    cursor = new Cursor(100,200);
    create_maincharacter();
    map_speed = map_x = map_y = 0;
    Time_Left = TIME_LEFT;
    Girl_Set.clear();
    Enemy_Set.clear();
    menu->Reset();

    HaveGoodLookingGirl = false;
    HaveMaster = false;
}

void
GameWindow::draw_running_map()
{

    al_clear_to_color(al_map_rgb(200, 120, 120));

    if (map_x < -2300) al_draw_bitmap(ground,-2300,map_y,0);
    else if (map_x > 0) al_draw_bitmap(ground,0,map_y,0);
    else al_draw_bitmap(ground,map_x,map_y,0);

    maincharacter->Draw(-map_x);

    for(std::vector <Girl*>::iterator it = Girl_Set.begin(); it != Girl_Set.end(); it++)
        (*it)->Draw(-map_x);

    for(std::vector <Enemy*>::iterator it = Enemy_Set.begin(); it != Enemy_Set.end(); it++)
        (*it)->Draw(-map_x);

    if(HaveMaster) master->Draw(-map_x);

    al_draw_filled_rectangle(1150, 100 + (TIME_LEFT - Time_Left) * 600 / TIME_LEFT, 1180, 700, al_map_rgb(164,30,34));

    if (medicine_cooldown > 0 )
    al_draw_filled_rectangle(60, 55, 60 + (medicine_available - medicine_cooldown)/5, 75, al_map_rgb(164,30,34));
    al_draw_bitmap(medicine, 10, 10, 0);

    menu->Draw(-map_x);

    al_flip_display();
}

void
GameWindow::draw_terminate_map()
{
    al_clear_to_color(al_map_rgb(200, 120, 120));
    terminate->Draw();

    al_flip_display();
}

void
GameWindow::draw_setting_map()
{
    int x = cursor->getX();
    int y = cursor->getY();
    al_clear_to_color(al_map_rgb(200, 120, 120));
    al_draw_bitmap(start,0,0,0);
    al_draw_bitmap(cur,x,y,0);

    al_flip_display();
}



void
GameWindow::game_destroy()
{
    delete terminate;
    if(HaveMaster)
        delete master;
    delete maincharacter;
    al_destroy_bitmap(start);
    al_destroy_bitmap(ground);
    game_reset();

    delete menu;

}
