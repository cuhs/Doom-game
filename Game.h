// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Board.h"


class Game
{
public:
    //constructor initializes the board
    Game(int goblinSmellDistance) :m_board(0, goblinSmellDistance) {
        gobSmellDistance = goblinSmellDistance;
    };

    void play();

private:

    Board m_board;
    int level;
    int gobSmellDistance;
    



 
};

#endif // GAME_INCLUDED
