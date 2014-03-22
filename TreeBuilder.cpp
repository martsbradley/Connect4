#include "Board.h"
#include "TreeBuilder.h"
#include <string.h>
#include <iostream>
#include "Visitor.h"

static unsigned char RED_BYTE    = 0b01000000;
static unsigned char YELLOW_BYTE = 0b11000000;
static unsigned char BLANK_BYTE =  0b00000000; 

GameState::GameState()
   :mMinMaxValue(0),
    mLevel(0),
    mScore(0)
{
   for (int x = 0; x < 11;x++)
       mState[x] = BLANK_BYTE;
}

GameState::~GameState()
{
    // While leafs delete
  //std::vector<GameState*> children;
  //getChilden(children);
  //std::cout << "There are " << children.size() << std::endl;
 
    std::vector<GameState*>::iterator it; 

    for (it = mNextStates.begin(); it != mNextStates.end(); ++it) 
    {
        GameState* pState= *it;
        if (pState) delete pState;
    }
    //mNextStates.clear();
}


// Takes the current state of the Board
// And builds the associated GameState
void GameState::setGameState(Board& arBoard)
{
    for (int column = 0; column < 7; column++)
    {
        for (int level = 5; level >= 0; level--)
        {
            enum Piece piece = arBoard.getPositionStatus((enum ColumnName)column, level);
            setValue(column, level, piece);
        }
    }
}

unsigned char getPieceBits(int aColumn, int aLevel, Piece aPiece)
{
    unsigned char piece = BLANK_BYTE;
    if (aPiece == RED) {
        piece = RED_BYTE;
    }
    else if (aPiece == YELLOW) {
        piece = YELLOW_BYTE;
    }
       
    int shift = getByteOffset(aColumn, aLevel);
    return piece >> (2*shift);
}

void GameState::setValue(int aColumn,int aLevel, enum Piece aPiece)
{
    unsigned char pieceByte = getPieceBits(aColumn, aLevel, aPiece);
   
    int byte = getByteIndex(aColumn, aLevel);
    mState[byte] |= pieceByte;
}

enum Piece GameState::getValueAtPosition(int aPosition) 
{
    int byteIndex = getByteIndex(aPosition);
    int byteOffset = getByteOffset(aPosition);
    unsigned char theByte = mState[byteIndex];

    unsigned char mask = 0b11000000;
    mask = mask >> (2*byteOffset);

    theByte &= mask;
    theByte = theByte << (2*byteOffset);
     
    enum Piece result = EMPTY;
    if (theByte == RED_BYTE)
        result = RED;
    else if (theByte == YELLOW_BYTE)
        result = YELLOW;
    return result;
}
int GameState::getLevel() {
    return mLevel;
}
int GameState::setLevel(int aLevel) {
    mLevel = aLevel;
}

int GameState::getScore() {
    return mScore;
}
int GameState::setScore(int aScore) {
    mScore = aScore;
}

int GameState::getMinMaxValue() 
{
    return mMinMaxValue;
}
void GameState::setMinMaxValue(int aMinMaxValue)
{
    mMinMaxValue = aMinMaxValue;
}

/**
 * column values 0 to 6
 * level values  0 to 5
 */
int getPosition(int column, int level)
{
     int position = (column*6)+(6-level)-1;
     return position;
}

int getByteIndex(int aPosition)
{
   int byteIndex = aPosition / 4;
   return byteIndex;
}

// Seven across six high.
// 
int getByteIndex(int column, int level)
{
   int position = getPosition(column,level);

   int byte = getByteIndex(position);
   //Pos      Byte
   //0        0
   //1        0
   //2        0
   //3        0
   //4        1
   //5        1
   //6        1
   //7        1
   //8        2
   //9        2
   //10       2
   //11       2


   // First four go into the first byte
   // Next four go into the next byte
   // Next four go into the next byte
   return byte;
}

int getByteOffset(int column, int level)
{
   //Pos      Byte   Index
   //0        0      0
   //1        0      1
   //2        0      2
   //3        0      3
   //4        1      0
   //5        1      1
   //6        1      2
   //7        1      3
   //8        2      0
   //9        2      1
   //10       2      2
   //11       2      3
   int position = getPosition(column,level);
   int byteIndex = getByteIndex(column, level);
   int offset = position - byteIndex*4;

   return offset;
}
int getByteOffset(int aPosition)
{
    int byteIndex = getByteIndex(aPosition);
    int offset = aPosition - byteIndex*4;
    return offset;
}

TreeBuilder::TreeBuilder()
{
    mpGameState = new GameState();
    mpGameState->setLevel(0);
}

TreeBuilder::~TreeBuilder()
{
    delete mpGameState;
}

int MAX_LEVEL = 4;

void TreeBuilder::build(Board& arBoard, GameState* apGameState)
{
    apGameState->setGameState(arBoard);

    std::vector<Board> nextBoards = arBoard.generateNextTurns();

    if (!nextBoards.empty() && apGameState->getLevel() < MAX_LEVEL)
    {
        std::vector<Board>::iterator itBoard; 

        for(itBoard = nextBoards.begin(); itBoard != nextBoards.end(); ++itBoard)
        {
            GameState* pChild = new GameState();
            pChild->setLevel(apGameState->getLevel()+1);
            apGameState->addNextState(pChild);
            build(*itBoard, pChild);
        }
    }
}

void TreeBuilder::buildTree(Board& arBoard)
{
    //count = 0;
    build(arBoard, mpGameState);
}

void GameState::accept(Visitor& arVisitor) 
{
    arVisitor.visit(this);
}

GameState* TreeBuilder::getTree() {
    return mpGameState;
}

void GameState::addNextState(GameState* apGameState)
{
    mNextStates.push_back(apGameState);
}

struct BottomTop{
    BottomTop(int a,int b): bottom(a),top(b){} 
    int bottom;
    int top;
};

/**
  This method will compare this game state to that one.
  The returned result will contain the columsn that are different
  */
std::vector<int> GameState::getColumnsHeights()
{
    //  0   6   12  18  24  30  36
    //  1   7   13  19  25  31  37
    //  2   8   14  20  26  32  38
    //  3   9   15  21  27  33  39
    //  4   10  16  22  28  34  40
    //  5   11  17  23  29  35  41

     
    std::vector<BottomTop> startEnd;
    startEnd.push_back(BottomTop(5,0));
    startEnd.push_back(BottomTop(11,6));
    startEnd.push_back(BottomTop(17,12));
    startEnd.push_back(BottomTop(23,18));
    startEnd.push_back(BottomTop(29,24));
    startEnd.push_back(BottomTop(35,30));
    startEnd.push_back(BottomTop(41,36));

    std::vector<int> columnHeight;

    std::vector<BottomTop>::iterator it = startEnd.begin();

    while (it != startEnd.end())
    {
        int height = 0;
        for (int pos = it->bottom;pos >= it->top; pos--)
        {
            enum Piece piece = getValueAtPosition(pos);
            if (piece == EMPTY)
            {
                break;
            }
            else
            {
                height++;
            }
        }
        columnHeight.push_back(height);
        ++it;
    }
    return columnHeight;
}

std::vector<GameState*>& GameState::getNextStates() 
{
    return mNextStates;
}
void GameState::output()
{
    //  0   6   12  18  24  30  36
    //  1   7   13  19  25  31  37
    //  2   8   14  20  26  32  38
    //  3   9   15  21  27  33  39
    //  4   10  16  22  28  34  40
    //  5   11  17  23  29  35  41
    for (int rowStartPos = 0 ; rowStartPos <= 5;rowStartPos++)
    {
        int times = 0;
        int pos = rowStartPos;
        while(times < 7)
        {
            enum Piece piece = getValueAtPosition(pos);
            if (piece == RED)
            {
                std::cout << "R";
            }
            else if (piece == YELLOW) 
            {
                std::cout << "Y";
            }
            else
            {
                std::cout << " ";
            }
            pos += 6;
            times++;
        }
        std::cout << std::endl;
    }
}
