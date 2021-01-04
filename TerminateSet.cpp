#include"TerminateSet.h"

TerminateSet :: TerminateSet(int score)
{
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
}

void TerminateSet :: Draw()
{
    al_draw_bitmap(terminate_map,0,0,0);
}
