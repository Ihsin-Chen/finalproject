#ifndef NORMAL_GIRL_H_INCLUDED
#define NORMAL_GIRL_H_INCLUDED
#include<iostream>
#include "NPC.h"
#define COOL_DOWN_TIME 100

class Girl : public NPC
{
public:
    Girl(int pos_x, int pos_y,int IsGoodlooking) : NPC(pos_x, pos_y)
    {
        if (IsGoodlooking)
        {
            max_health = health = 400;
            speed = 3;
            npc_img = al_load_bitmap("./Character/girl_5.png");
            npc_attack = al_load_bitmap ("./Character/girl_5_attack.png");
        }
        else
        {
            max_health = health = 300;
            speed = 2;
            npc_img = al_load_bitmap ("./Character/girl_1.png");
            npc_attack = al_load_bitmap ("./Character/girl_1_attack.png");
        }
    }
    int GetHealth() {return health;}
    bool BeingAttack(int harm);
    bool BeingHealed(int heal);
    void CoolDown();

    int cool_down_cnt = 0;
};

#endif // NORMAL_GIRL_H_INCLUDED
