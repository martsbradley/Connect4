#ifndef BOARDSTRENGTH_H
#define BOARDSTRENGTH_H
#include <vector>
#include <string>
#include "Board.h"
class GameState;

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
    void setGameState(GameState& arGameState);
    void setLines(int aLineInfoArray[]);

    int getStrength();

    void output();
private:
    std::vector<std::string> searchData;
    //  The line data will show which positions
    //  Make up a line.  A -1 is a line break
    std::vector<int> lineData;
};

class BoardStrength// : public  BoardListener
{
 public:
    BoardStrength();
    void setTree(GameState& arGameState);

    enum ColumnName bestNextMove();

    void peiceAdded(enum Piece aPiece, enum ColumnName aCol, int aLevel);
private:
    StrengthSearch vertical;
    StrengthSearch horizontal;
    StrengthSearch upDiagonal;
    StrengthSearch downDiagonal;
};
#endif //BOARDSTRENGTH_H
