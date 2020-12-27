#include"NPC.h"
#include "GameWindow.h"

NPC :: NPC(int pos_x, int pos_y)
{
    this->range = new Circle(pos_x, pos_y, 30);
}

void NPC :: Move()
{
    if (range->x+30 > window_width-180  && IsMovingLeft == false) IsMovingLeft = true;   /// «Ý­×§ï***********
    else if(range->x - 30 < 0 && IsMovingLeft == true) IsMovingLeft = false;

    if(IsMovingLeft == true) range->x -= 3;
    else range->x += 3;
}

void NPC :: Draw()
{
    al_draw_bitmap(npc_img, range->x, range->y, 0);
}

NPC :: ~NPC()
{
    delete range;
    al_destroy_bitmap(npc_img);
}
