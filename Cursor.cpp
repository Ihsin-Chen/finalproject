#include"Cursor.h"
#include<iostream>

using namespace std;

Cursor :: ~Cursor()
{
    delete circle;
}

Cursor :: Cursor(int pos_x, int pos_y)
{
    this->circle = new Circle(pos_x, pos_y, 0);
}

void
Cursor :: Move_Right()
{
    if(circle->x < 800) circle->x += 350;
}

void
Cursor :: Move_Left()
{
    if(circle->x > 100) circle->x -= 350;
}

void
Cursor :: Draw(int map_x)
{

}
