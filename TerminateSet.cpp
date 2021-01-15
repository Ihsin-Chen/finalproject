#include"TerminateSet.h"

using namespace std;

TerminateSet :: TerminateSet(int score, int x, int y)
{
    good_position.clear();
    normal_position.clear();

    if (score > 2000)
    {
        this->WhetherWin = true;
        this->terminate_map = al_load_bitmap("./background/lose_map.png");
    }
    else
    {
        this->WhetherWin = false;
        this->terminate_map = al_load_bitmap("./background/lose_map.png");
    }
    Font_30 = al_load_ttf_font("pirulen.ttf", 30, 0);
    Score = score;
    Good_cnt = x;
    Normal_cnt = y;
    Girl = al_load_bitmap("./Character/girl_1_attack.png");
    GoodGirl = al_load_bitmap("./Character/girl_5_attack_right.png");
    Main = al_load_bitmap("./Character/boy_3_right.png");

    main_postion = make_pair(0, 500);
    int z = -150;
    for(int i=0; i<Good_cnt; i++)
    {
        good_position.push_back(make_pair(z,500));
        z -= 150;
    }
    for(int i=0; i<Normal_cnt; i++)
    {
        normal_position.push_back(make_pair(z,500));
        z -= 150;
    }
}

void TerminateSet :: Draw()
{
    char buffer[80];
    vector<pair<int,int>> :: iterator it;
    //al_draw_bitmap(terminate_map,0,0,0);

    sprintf(buffer, "YOU GOT %d SCORE IN THIS MATCH", Score);
    al_draw_text(Font_30, al_map_rgb(255, 255, 255), 200, 200, 0, buffer);

    al_draw_bitmap(Main, main_postion.first, main_postion.second,0);
    main_postion.first += 2;

    for(it = good_position.begin(); it != good_position.end(); ++it)
    {
        al_draw_bitmap(GoodGirl, (*it).first, (*it).second,0);
        (*it).first += 2;
    }
    for(it = normal_position.begin(); it != normal_position.end(); ++it)
    {
        al_draw_bitmap(Girl, (*it).first, (*it).second,0);
        (*it).first += 2;
    }
}
