#include"NPC.h"
#include "GameWindow.h"

NPC :: NPC(int pos_x, int pos_y)
{
    this->circle = new Circle(pos_x, pos_y, 50);
}

void NPC :: Move()
{
    if (circle->x+30 > map_width-180  && IsMovingLeft == false) IsMovingLeft = true;   /// «Ý­×§ï***********
    else if(circle->x - 30 < 0 && IsMovingLeft == true) IsMovingLeft = false;

    if(IsMovingLeft == true) circle->x -= 2;
    else circle->x += 2;
}

void NPC :: Draw(int map_x)
{
    if(map_x < 0) map_x = 0;
    else if(map_x > 2300) map_x = 2300;

    int x = circle->x - map_x;

    al_draw_bitmap(npc_img, x , circle->y, 0);
}

NPC :: ~NPC()
{
    delete circle;
    al_destroy_bitmap(npc_img);
}
