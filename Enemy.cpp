#include "Enemy.h"

bool
Enemy :: DetectAttack(Girl *girl, int map_x)
{
    Circle* tmp1 = new Circle(girl->getX() + map_x, girl->getY(),girl->getRadius());
    Circle* tmp2 = new Circle(circle->x + map_x, circle->y,circle->r);

    if(Circle::isOverlap(tmp1, tmp2))
    {
        if (AttackCountDown > 0)
        {
            PreparingAttack = true;
            AttackCountDown -= 1;
        }
        else
        {
            IsAttacking = true;
            PreparingAttack = false;
        }
    }

    return IsAttacking;
}

void
Enemy :: TriggerAttack(Girl* girl)
{
    bool HealComplete;

    HealComplete = girl->BeingHealed(heal_point);

}


