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

    void Draw(int map_x);
    void Move();
    bool IsAttacking = false;
    int GetSpeed() {return speed;}

protected:

    ALLEGRO_BITMAP * npc_img;
    ALLEGRO_BITMAP * npc_attack;
    ALLEGRO_BITMAP * heart_1 = al_load_bitmap("./Character/heart_1.png");
    ALLEGRO_BITMAP * heart_2 = al_load_bitmap("./Character/heart_2.png");
    ALLEGRO_BITMAP * heart_3 = al_load_bitmap("./Character/heart_3.png");
    ALLEGRO_BITMAP * heart_4 = al_load_bitmap("./Character/heart_4.png");

    int health,speed,max_health;
    int strength;
    bool IsMovingLeft = 1;
};


#endif // MAIN_CHARACTOR_H_INCLUDED
