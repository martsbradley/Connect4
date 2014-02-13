#ifndef TREEBUILDER_H
#define TREEBUILDER_H
static unsigned char Empty =  0;
static unsigned char Red   =  1;
static unsigned char Yellow = 2;
#define MAX_GAME_STATE 11
#include "Board.h"

class NextStates;
class Board;

int arrayIndex(int column, int level);
int arrayIntraCharIndex(int column, int level);

class GameState
{
   // This class holds the game state
   // There will be many instances of this type of object
   // This will store the least amount of data to represent
   // A board state.
   // Thinking as follows
   // Three possible states for each location
   // So that needs two bits
   // 42 * 2 = 84
   // So 11 bytes needed.


   // The treebuilder will create these immutable objects
   // The StrenghSearch class will be able to 
   // interrogate these GameStates and figure out the 
   // a good ness number to assign to the board 
public:
    GameState();
    ~GameState();
    void setNextStates(NextStates* apNextStates);
    void setValue(int column,int level, enum Piece aPiece);

   void setGameState(Board& arBoard);
   enum Piece getPosition(int aPos);
private:

   unsigned char state[MAX_GAME_STATE];
   NextStates* mpNextStates; // Each non terminal GameState
                            // Will have further possible
                            // GameStates that proceed it.
};

class NextStates
{
    // This class holds at most seven different choices
    // that a player could have made for thier turn

public:
    GameState* getGameState(int n);
    
private:
    GameState gameState[7];
};



class TreeBuilder
{
    TreeBuilder();
    void build(Board& arBoard, GameState* apGameState);
private:
    GameState* mpGameState;

    std::vector<Board> generateNextBoards(Board& arBoard);
};
#endif // TREEBUILDER_H
