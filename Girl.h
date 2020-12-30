#ifndef NORMAL_GIRL_H_INCLUDED
#define NORMAL_GIRL_H_INCLUDED
#include<iostream>
#include "NPC.h"

class Girl : public NPC
{
public:
    Girl(int pos_x, int pos_y,int IsGoodlooking) : NPC(pos_x, pos_y)
    {
        if (IsGoodlooking)
        {
            health = 200;
            npc_img = al_load_bitmap("./Character/girl_4.jpg");
        }
        else
        {
            health = 100;
            npc_img = al_load_bitmap ("./Character/girl_1.png");
        }
    }
    int GetHealth() {return health;}
    bool BeingAttack(int harm);
};

#endif // NORMAL_GIRL_H_INCLUDED
