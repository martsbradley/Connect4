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

class SearchItem
{
public:
    SearchItem(char aValue, char aPosition);
    char mValue;
    char mPosition;
};

class BoardScore
{
public:
    BoardScore();
    void addWinningPosition(int aPosition);
    std::vector<int> getWinningPosition();
    void setScore(int aScore);
    bool setScore(int aScore, const std::vector<SearchItem>& arFour);
    int getScore() const;
    bool isGameWinningScore() const;
    bool operator>(const BoardScore& arOther) const;
    bool operator==(const BoardScore& arOther) const;
    BoardScore& operator+=(const BoardScore& arOther);
    
private:
    std::vector<int> mWinningPositions;
    int mScore;
    int mBest;
    int mWorst;
};

std::ostream& operator<<(std::ostream& os, const BoardScore& dt);


class SearchLine
{
public :
    void appendItem(char aValue, char aPosition);
    void reverse();
    void clear();
    BoardScore scoreSearch();
    std::vector<int> getWinningPositions() { return mWinningLine;}

private:
   std::vector<SearchItem> mItems;
   std::vector<int> mWinningLine;

};

class StrengthSearch 
{
public:
    void setGameState(GameState* apGameState);
    void setLines(int aLineInfoArray[]);

    BoardScore getStrength();

    void output();

    std::vector<int> getWinningPositions();

protected:
    std::string mName;
private:
    std::vector<SearchLine> mSearchData;
    //  The line data will show which positions
    //  Make up a line.  A -1 is a line break
    std::vector<int> lineData;
    std::vector<int> mWinningLine;
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


class BoardStrengthCalculator
{
 public:
    BoardStrengthCalculator();

    //  TODO this really needs its name fixed.
    void setTree(GameState* apGameState);

    BoardScore getBoardStrength();
    std::vector<int> getWinningPositions();
private:
    std::vector<StrengthSearch*> mBoardSearches;
    VerticalSearch vertical;
    HorizontalSearch horizontal;
    UpDiagonal upDiagonal;
    DownDiagonal downDiagonal;
    std::vector<int> mWinningLine;
};
#endif //BOARDSTRENGTH_H
