#ifndef MAINCHARACTER_H_INCLUDED
#define MAINCHARACTER_H_INCLUDED

using namespace std;

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "NPC.h"
#include "Girl.h"

#define Width 40
#define Height 40

class MainCharacter : public Object
{
public:
    MainCharacter(int, int);
    ~MainCharacter();

    void Draw(int map_x);
    //void ToggleClicked() {isClicked = !isClicked;}

    bool DetectAttack(Girl *girl);
    bool TriggerAttack(Girl *girl);
    int GetSpeed() {return speed;}
    void MoveLeft(bool WhetherMove);
    void MoveRight(bool WhetherMove);
    void Pause();

protected:

    int attack_harm_point = 10, speed = 0;
    ALLEGRO_BITMAP *attack_img = al_load_bitmap(".object/flash.png");
    ALLEGRO_BITMAP *img = al_load_bitmap("./character/boy_3.png");
};


#endif // MAINCHARACTER_H_INCLUDED
