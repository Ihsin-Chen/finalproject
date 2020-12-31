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

    if(IsMovingLeft == true) circle->x -= speed;
    else circle->x += speed;
}

void NPC :: Draw(int map_x)
{
    if(map_x < 0) map_x = 0;
    else if(map_x > 2300) map_x = 2300;

    int x = circle->x - map_x;

    if (!IsAttacking) al_draw_bitmap(npc_img, x , circle->y, 0);
    else al_draw_bitmap(npc_attack, x , circle->y, 0);

    if (health <= max_health*9/10 && health >= max_health*8/10) al_draw_bitmap(heart_1,x, circle->y - 150,0);
    else if (health < max_health*8/10 && health >= max_health*6/10) al_draw_bitmap(heart_2,x, circle->y - 150,0);
    else if (health < max_health*6/10 && health >= max_health*3/10) al_draw_bitmap(heart_3,x, circle->y - 150,0);
    else if (health < max_health*3/10 && health >= 0)al_draw_bitmap(heart_4,x, circle->y - 150,0);
}

NPC :: ~NPC()
{
    delete circle;
    al_destroy_bitmap(npc_img);
}
