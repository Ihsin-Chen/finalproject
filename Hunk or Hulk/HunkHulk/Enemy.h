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
        if (IsGoodlooking)
        {
            strength = 9;
            if (!(npc_img = al_load_bitmap("./Character/boy_1.png")))
            std::cout << " Failed to draw boss enemy." << std::endl;
        }
        else
        {
            strength = 5;
            if(!(npc_img = al_load_bitmap("./Character/boy_2.png")))
            std::cout << " Failed to draw normal enemy." << std::endl;
        }
    }

    int Getstrength() {return strength;}
    bool DetectAttack ( MainCharacter maincharacter);
};

#endif // ENEMY_H_INCLUDED
