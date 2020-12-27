#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *HunkHulk= new GameWindow();

    HunkHulk->game_play();

    delete HunkHulk;
    return 0;
}
