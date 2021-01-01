#include"Girl.h"

bool Girl :: BeingAttack(int harm)
{
    health = health - harm;
    if (health <= 0) return true;
    else return false;
}

bool Girl :: BeingHealed(int heal)
{
    if (health < max_health) health = health + heal;
    if (health == max_health) return true;
    else return false;
}

/*void Girl :: CoolDown()
{
    cool_down_cnt ++;

    if(cool_down_cnt == COOL_DOWN_TIME)
    {
        IsAttacking = false;
        health = max_health;
        cool_down_cnt = 0;
    }
}*/

void Girl :: CoolDown()
{
    if (health < max_health) health += 1;
}
