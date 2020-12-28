#include "MainCharacter.h"

using namespace std;

MainCharacter :: MainCharacter(int pos_x = 0, int pos_y = 0)
{
    this->circle = new Circle (pos_x, pos_y, 50);
}

MainCharacter:: ~MainCharacter()
{
    delete circle;

    al_destroy_bitmap(img);
    al_destroy_bitmap(attack_img);
}

void
MainCharacter::Draw()
{
    al_draw_bitmap(img, circle->x, circle->y, 0);

}

bool
MainCharacter :: DetectAttack(Girl *girl)
{
    bool willAttack = false;

    if(Circle::isOverlap(this->circle, girl->getCircle())) willAttack = true;

    return willAttack;
}

bool
MainCharacter :: TriggerAttack(Girl* girl)
{
    bool isDestroyed = false;

    if(girl->GetHealth() < 0) isDestroyed = true;
    else
    {
        girl->BeingAttack(attack_harm_point);
        al_draw_bitmap(attack_img, girl->getX() , girl->getY(),0);
    }

    return isDestroyed;
}


