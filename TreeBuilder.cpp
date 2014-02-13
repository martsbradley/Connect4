#include "Board.h"
#include "TreeBuilder.h"
#include <string.h>
GameState::GameState()
{
   memset(&state[0], sizeof(NextStates*), 11);
}

GameState::~GameState()
{
   //TODO   should delete the children
}

void GameState::setNextStates(NextStates* apNextStates)
{
   mpNextStates = apNextStates;
}

enum Piece GameState::getPosition(int aPos)
{
   return RED;
}

// Takes the current state of the Board
// And builds the associated GameState
void GameState::setGameState(Board& arBoard)
{
   // iterate over each column
   // for each spot get the 
   // byte that needs created.
}

void GameState::setValue(int column,int level, enum Piece aPiece)
{

}

int getPosition(int column, int level)
{
     int position = (6 - level)*(column+1);
     return position;
}

// Seven across six high.
// 
int arrayIndex(int column, int level)
{
   int position = getPosition(column,level);

   int byte = position % 4;

   // First four go into the first byte
   // Next four go into the next byte
   // Next four go into the next byte
   return 0;
}

int arrayIntraCharIndex(int column, int level)
{
    return 0;
}

GameState* NextStates::getGameState(int n)
{
    return 0;
}


TreeBuilder::TreeBuilder()
{
    mpGameState = new GameState();
}

void TreeBuilder::build(Board& arBoard, GameState* apGameState)
{
     apGameState->setGameState(arBoard);

     std::vector<Board> nextBoards = arBoard.generateNextTurns();

     if (!nextBoards.empty())
     {
         NextStates* pNextStates = new NextStates();
         apGameState->setNextStates(pNextStates);

         std::vector<Board>::iterator itBoard; 

         int n = 0;
         for(itBoard = nextBoards.begin(); itBoard != nextBoards.end(); ++itBoard) {
            build(*itBoard, pNextStates->getGameState(n++));
         }
     }
}
