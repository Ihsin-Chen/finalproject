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

    bool DetectAttack(Girl *girl,int map_x);
    bool TriggerAttack(Girl *girl);
    int GetSpeed() {return speed;}
    void MoveLeft(int map_x);
    void MoveRight(int map_x);
    void Pause();
    void MedicineInitiate(int x) {attack_harm_point += x;}
    void MedicineOver(int x) {attack_harm_point -= x;}
    bool Freeze = false;
    bool IsAttacking = false;

protected:

    int attack_harm_point = 4, speed = 0;
    ALLEGRO_BITMAP *attack_img = al_load_bitmap("./character/boy_3_attack.png");
    ALLEGRO_BITMAP *attack_img_right = al_load_bitmap("./character/boy_3_attack_right.png");
    ALLEGRO_BITMAP *img = al_load_bitmap("./character/boy_3.png");
    ALLEGRO_BITMAP *img_right = al_load_bitmap("./character/boy_3_right.png");
    ALLEGRO_BITMAP *freeze_img = al_load_bitmap("./character/boy_3_freeze_left.png");
    ALLEGRO_BITMAP *freeze_img_right = al_load_bitmap("./character/boy_3_freeze_right.png");
    bool IsMovingLeft = 1;
};


#endif // MAINCHARACTER_H_INCLUDED
