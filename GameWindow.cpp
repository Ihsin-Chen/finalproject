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

    game_init();
}

void
GameWindow::game_init()
{

    /// load image and sound
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        if(event.timer.source == timer)
        {
            instruction = game_update();
            draw_running_map();
            /// to do when timer edges come
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
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
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
        key_state[event.keyboard.keycode] = false;

    if ((NPC_Set.size() < 3 && npc_CoolDown > 360)|| NPC_Set.size() == 0)
    {
        NPC* n = create_npc();
        NPC_Set.push_back(n);
        npc_CoolDown = 0;
    }


    npc_CoolDown ++;
    return instruction;
}

void GameWindow::create_maincharacter()
{
    maincharacter = new MainCharacter(0, 500);
}

NPC* GameWindow :: create_npc()
{
    NPC* n = NULL;

    n = new Girl(npc_born_x, npc_born_y,0);

    if (npc_born_y == 400) npc_born_y += 100;
    else if (npc_born_y == 500) npc_born_y -= 100;

    return n;
}

void
GameWindow::game_begin()
{
    printf(">>> Start\n");

    draw_running_map();

    //al_play_sample_instance(startSound);
    //while(al_get_sample_instance_playing(startSound));
    //al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
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


    for(std::vector <NPC*>::iterator it = NPC_Set.begin(); it != NPC_Set.end(); it++)
        (*it)->Move();

    if(key_state[ALLEGRO_KEY_LEFT] && key_state[ALLEGRO_KEY_RIGHT]) maincharacter->Pause();
    else if(key_state[ALLEGRO_KEY_LEFT]) maincharacter-> MoveLeft(OutOfRange);
    else if(key_state[ALLEGRO_KEY_RIGHT]) maincharacter-> MoveRight(OutOfRange);
    else maincharacter-> Pause();

    printf("%d\n",map_x);

    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{

    /// stop sample instance
    //al_stop_sample_instance(startSound);

    /// stop timer
    ground = al_load_bitmap("./background/street.png");
    al_stop_timer(timer);
    create_maincharacter();
}

void
GameWindow::draw_running_map()
{

    al_clear_to_color(al_map_rgb(200, 120, 120));

    if (map_x < -2300) al_draw_bitmap(ground,-2300,map_y,0);
    else if (map_x > 0) al_draw_bitmap(ground,0,map_y,0);
    else al_draw_bitmap(ground,map_x,map_y,0);

    for(std::vector <NPC*>::iterator it = NPC_Set.begin(); it != NPC_Set.end(); it++)
        (*it)->Draw(-map_x);

    maincharacter->Draw(-map_x);


    al_flip_display();
}


void
GameWindow::game_destroy()
{
    game_reset();

}
