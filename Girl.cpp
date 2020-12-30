#include"Girl.h"

bool Girl :: BeingAttack(int harm)
{
    health = health - harm;
    if (health <= 0) return true;
    else return false;
}
