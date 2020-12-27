#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include"Object.h"
#include "Circle.h"


class NPC : public Object
{
public:

    NPC(int,int);
    virtual ~NPC();

    void Draw();
    void Move();

protected:

    Circle* range;
    ALLEGRO_BITMAP * npc_img;
    int health;
    int strength;
    bool IsMovingLeft = 1;
};


#endif // MAIN_CHARACTOR_H_INCLUDED
