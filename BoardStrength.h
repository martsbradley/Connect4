#ifndef BOARDSTRENGTH_H
#define BOARDSTRENGTH_H
#include <vector>
#include "Board.h"

class CellState 
{
public:
   CellState();
   CellState(int aPosition);
   void setState(enum Piece aPiece);
   enum Piece getState();
   void setPosition(int aPosition);

private:
   enum Piece mState;
   int mPosition;
};


/**
     Split the search up into looking at blocks of 4
     So if the line has six there will be 3 searches

        _ _ _ _ _ _
        <     >
          <     >
            <     >
     There will be a variable called target color.
     and anti target colour.
     So if we are counting for RED then RED would be TargetCount
     Yellow AntiTargetCount
     
     AntiTargetCount | TargetCount |  EmptyCell |  Score
          Any             -              -          -1
          None            1              3           7  (1*4+3)
          None            2              2           10 (2*4+2)
          None            3              1           13 (3*4+1)
          None            4              0           16 (4*4)
*/


class StrengthSearch 
{
public:
    void addSearchArray(CellState* apCells, int aCellIds[]);

    int getStrength();
private:
    std::vector<std::vector<CellState*> > searchData;
};

class BoardStrength : public  BoardListener
{
     BoardStrength();

      void peiceAdded(enum Piece aPiece, enum ColumnName aCol, int aLevel);
      void clearBoarded();

     // array of all the board positions.
     //CellState[]  cells;
     
   //StrengthSearch horizontal;
     StrengthSearch vertical;
   //StrengthSearch upDiagonal;
   //StrengthSearch downDiagonal;
     CellState cells[42];
};
#endif //BOARDSTRENGTH_H
