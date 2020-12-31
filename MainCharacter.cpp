#include "MainCharacter.h"
#include "GameWindow.h"
#include "Circle.h"

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
MainCharacter::Draw(int map_x)
{
    if (!IsAttacking) al_draw_bitmap(img, circle->x, circle->y, 0);
    else al_draw_bitmap(attack_img, circle->x, circle->y, 0);
}

bool
MainCharacter :: DetectAttack(Girl *girl,int map_x)
{
    bool willAttack = false;
    Circle* tmp = new Circle(girl->getX()+map_x, girl->getY(),girl->getRadius());


    if(Circle::isOverlap(this->circle, tmp)) willAttack = true;
    //std :: cout << getX() << " " << circle->y << " " << tmp->x << " " << tmp->y << std :: endl;

    return willAttack;
}

bool
MainCharacter :: TriggerAttack(Girl* girl)
{
    bool isDestroyed;

    isDestroyed = girl->BeingAttack(attack_harm_point);

    return isDestroyed;
}

void
MainCharacter :: MoveLeft(int map_x)
{
    speed = -7;
    if((map_x <= -2300 || map_x >=0) && circle->x >= 0) circle->x += speed;
}

void
MainCharacter::MoveRight(int map_x)
{
    speed = 7;
    if((map_x <= -2300 || map_x >=0) && circle->x <= window_width-120) circle->x += speed;
}

void
MainCharacter :: Pause()
{
    speed = 0;
}


