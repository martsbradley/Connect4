#ifndef TREEBUILDER_H
#define TREEBUILDER_H
//static unsigned char Empty =  0;
//static unsigned char Red   =  1;
//static unsigned char Yellow = 2;
#define MAX_GAME_STATE 11
#include "Board.h"

class NextStates;
class Board;
class Visitor;

int getPosition(int column, int level);
int getByteIndex(int column, int level);
int getByteIndex(int aPosition);

int getByteOffset(int column, int level);
int getByteOffset(int aPosition);

unsigned char getPieceBits(int aColumn, int aLevel, Piece aPiece);

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
    void setValue(int column,int level, enum Piece aPiece);
    enum Piece getValueAtPosition(int aPosition);

    void setGameState(Board& arBoard);
    void output();

    int getLevel();
    void setLevel(int aLevel);
    void accept(Visitor& arVisitor);

    int getScore();
    void setScore(int aScore);
    void setMinMaxValue(int aMinMaxValue);
    int getMinMaxValue();
    void addNextState(GameState* apGameState);
    std::vector<GameState*>& getNextStates();
    std::vector<int> getColumnsHeights();
private:

    //void getChilden(std::vector<GameState*>& children);
    int mLevel;
    int mScore;
    int mMinMaxValue;
    unsigned char mState[MAX_GAME_STATE];
    std::vector<GameState*> mNextStates;
};

class TreeBuilder
{
public:
    TreeBuilder();
    ~TreeBuilder();
    void build(Board& arBoard, GameState* apGameState);
    void buildTree(Board& arBoard);
    GameState* getTree();
private:
    GameState* mpGameState;

    std::vector<Board> generateNextBoards(Board& arBoard);
};
#endif // TREEBUILDER_H
