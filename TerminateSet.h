#include"GameWindow.h"

#ifndef WINTERMINATE_H_INCLUDED
#define WINTERMINATE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class TerminateSet
{
public:
    TerminateSet(int score,int x, int y);
    void Draw();

private:
    bool WhetherWin;
    ALLEGRO_BITMAP* terminate_map;
    ALLEGRO_BITMAP* Girl;
    ALLEGRO_BITMAP* GoodGirl;
    ALLEGRO_BITMAP* Main;
    ALLEGRO_FONT* Font_30;

    int Score,Good_cnt,Normal_cnt;
    pair<int,int> main_postion;
    vector<pair<int,int>> good_position;
    vector<pair<int,int>> normal_position;

};


#endif // WINTERMINATE_H_INCLUDED
