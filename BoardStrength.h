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

#define WINNING_SCORE 1000000
#define LOOSING_SCORE -1000000


class StrengthSearch 
{
public:
    void setGameState(GameState& arGameState);
    void setLines(int aLineInfoArray[]);

    int getStrength();


    void output();

protected:
    std::string mName;
private:
    std::vector<std::string> mSearchData;
    //  The line data will show which positions
    //  Make up a line.  A -1 is a line break
    std::vector<int> lineData;
};

class VerticalSearch : public StrengthSearch 
{
public: 
    VerticalSearch();
};

class HorizontalSearch : public StrengthSearch 
{
public: 
    HorizontalSearch();
};

class UpDiagonal : public StrengthSearch 
{
public: 
    UpDiagonal();
};

class DownDiagonal : public StrengthSearch 
{
public: 
    DownDiagonal();
};


class BoardStrength
{
 public:
    BoardStrength();

    //  TODO this really needs its name fixed.
    void setTree(GameState& arGameState);

    int getBoardStrength();
private:
    std::vector<StrengthSearch*> mBoardSearches;
    VerticalSearch vertical;
    HorizontalSearch horizontal;
    UpDiagonal upDiagonal;
    DownDiagonal downDiagonal;
};
#endif //BOARDSTRENGTH_H
