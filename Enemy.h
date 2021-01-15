#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <iostream>
#include "NPC.h"
#include "MainCharacter.h"

class Enemy : public NPC
{
    public:
    Enemy(int pos_x, int pos_y, int IsGoodlooking) : NPC(pos_x, pos_y)
    {
        max_health = health = 100;
        circle->r = 250;
        IsMovingLeft = true;

        if (IsGoodlooking)
        {
            heal_point = 3;
            speed = 2;
            if (!(npc_img = al_load_bitmap("./Character/boy_1.png")))
            std::cout << " Failed to draw boss enemy." << std::endl;
            npc_attack = al_load_bitmap("./Character/boy_1_attack.png");
            npc_prepare = al_load_bitmap("./Character/boy_1_prepare.png");
        }
        else
        {
            heal_point = 2;
            speed = 2;
            if(!(npc_img = al_load_bitmap("./Character/boy_2.png")))
            std::cout << " Failed to draw normal enemy." << std::endl;
            npc_attack = al_load_bitmap("./Character/boy_2_attack.png");
            npc_prepare = al_load_bitmap("./Character/boy_2_prepare.png");
        }
    }

    int Getstrength() {return strength;}
    bool DetectAttack(Girl *girl, int map_x);
    void TriggerAttack(Girl* girl);

    int heal_point;
};

#endif // ENEMY_H_INCLUDED
