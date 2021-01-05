#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include <iostream>
#include "NPC.h"
#include "MainCharacter.h"

class Master : public NPC
{
    public:
    Master(int pos_x, int pos_y) : NPC(pos_x, pos_y)
    {
        circle->r = 250;
        IsMovingLeft = true;

        speed = 1;
        if(!(npc_img = al_load_bitmap("./Character/army.png")))
            std::cout << "Failed to draw the master." << endl;
    }

    void Draw(int) override;
    bool DetectAttack(MainCharacter *maincharacter, int map_x);
    void TriggerAttack(MainCharacter *maincharacter);

};

#endif // MASTER_H_INCLUDED
