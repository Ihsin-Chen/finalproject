#include"NPC.h"
#include "GameWindow.h"

NPC :: NPC(int pos_x, int pos_y)
{
    this->range = new Circle(pos_x, pos_y, 30);
}

void NPC :: Move()
{
    if (range->x+30 > map_width-180  && IsMovingLeft == false) IsMovingLeft = true;   /// «Ý­×§ï***********
    else if(range->x - 30 < 0 && IsMovingLeft == true) IsMovingLeft = false;

    if(IsMovingLeft == true) range->x -= 2;
    else range->x += 2;
}

void NPC :: Draw(int map_x)
{
    if(map_x < 0) map_x = 0;
    else if(map_x > 2300) map_x = 2300;

    int x = range->x - map_x;

    if (x <= 1200 && x >= -10) al_draw_bitmap(npc_img, x , range->y, 0);
}

NPC :: ~NPC()
{
    delete range;
    al_destroy_bitmap(npc_img);
}
