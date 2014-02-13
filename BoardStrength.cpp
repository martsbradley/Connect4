#include "BoardStrength.h"
#include <iostream>

CellState::CellState()
{
}

CellState::CellState(int aPosition)
 : mState(EMPTY),
   mPosition(aPosition)
{
}

void CellState::setState(enum Piece aPiece) 
{
    mState = aPiece;
}

enum Piece CellState::getState() {
    return mState;
}


void CellState::setPosition(int aPosition)
{
    mPosition = aPosition;
}

void StrengthSearch::addSearchArray(CellState* apCells, int aCellIds[])
{
    int val = aCellIds[0];
    std::vector<CellState*> searchDataList;

    while (val != -1) 
    {
        searchDataList.push_back(apCells+val);
    }
         
}   

int StrengthSearch::getStrength()
{
    return 0;
}
//    std::vector<std::vector<CellState*>> searchData;

BoardStrength::BoardStrength()
{
     int MaxCells = 42;
     for (int idx = 0; idx < MaxCells; idx++)
     {
         cells[idx].setPosition(idx);
     }
     int array[] =  {0,1,2,3,4,5,6, -1};

     vertical.addSearchArray(&cells[0], array);
}

void BoardStrength::peiceAdded(enum Piece aPiece, enum ColumnName aCol, int aLevel)
{
    std::cout << " Pecie added at col " << aCol << " on level " << aLevel << std::endl;
}
void BoardStrength::clearBoarded()
{
}
