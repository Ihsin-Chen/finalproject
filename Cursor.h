#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include"Circle.h"
#include"Object.h"

class Cursor : public Object
{
public:
    Cursor(int, int);
    ~Cursor();
    void Draw(int map_x);
    void Move_Left();
    void Move_Right();

private:

};

#endif // CURSOR_H_INCLUDED
