#include"Girl.h"

bool Girl :: BeingAttack(int harm)
{
    health = health - harm;
    if (health <= 0) return true;
    else return false;
}

void Girl :: CoolDown()
{
    cool_down_cnt ++;

    if(cool_down_cnt == COOL_DOWN_TIME)
    {
        IsAttacking = false;
        health = 100;
        cool_down_cnt = 0;
    }
}
