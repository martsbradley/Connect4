#ifndef COMPUTER_PLAYER_H 
#define COMPUTER_PLAYER_H 

#include "Board.h"

class ComputerPlayer
{
public: 
    enum ColumnName takeYourTurn(Board& arBoard);
};
#endif  // COMPUTER_PLAYER_H
