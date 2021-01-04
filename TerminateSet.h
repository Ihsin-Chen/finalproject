#include"GameWindow.h"

#ifndef WINTERMINATE_H_INCLUDED
#define WINTERMINATE_H_INCLUDED

class TerminateSet
{
public:
    TerminateSet(int score);
    void Draw();

private:
    bool WhetherWin;
    ALLEGRO_BITMAP* terminate_map;

};


#endif // WINTERMINATE_H_INCLUDED
