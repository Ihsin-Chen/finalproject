#include "Master.h"

void
Master :: Draw(int map_x)
{
    if(map_x < 0) map_x = 0;
    else if(map_x > 2300) map_x = 2300;

    int x = circle->x - map_x;

    if (IsAttacking)
    {
        cout << "draw" << endl;
        al_draw_bitmap(npc_attack, x , circle->y, 0);
    }
    else al_draw_bitmap(npc_img, x , circle->y, 0);

}

bool
Master :: DetectAttack(MainCharacter *maincharacter, int map_x)
{
    Circle* tmp1 = new Circle(maincharacter->getX(), maincharacter->getY(), maincharacter->getRadius());
    Circle* tmp2 = new Circle(circle->x + map_x, circle->y,circle->r);

    if(Circle::isOverlap(tmp1, tmp2) && !(maincharacter->Freeze))
        return true;
    else
        return false;
}

void
Master :: TriggerAttack(MainCharacter *maincharacter)
{
    maincharacter->Freeze = true;
    IsAttacking = true;
}


