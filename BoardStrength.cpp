#include "BoardStrength.h"
#include <iostream>
#include "TreeBuilder.h"
#include <algorithm>
#include <assert.h>
#include <math.h>

SearchItem::SearchItem(char aValue, char aPosition)
  :mValue{aValue},
   mPosition{aPosition}
{
}

void SearchLine::appendItem(char aValue, char aPosition)
{
   mItems.push_back(SearchItem(aValue, aPosition));
}
void SearchLine::reverse()
{
   std::reverse(mItems.begin(), mItems.end());
}

void SearchLine::clear()
{
   mItems.clear();
   mWinningLine.clear();
}

static int scoreFourCells(std::vector<SearchItem>& arString)
{
    assert(arString.size() == 4);

    size_t reds = std::count_if(arString.begin(), arString.end(), 
    [](const SearchItem& arItem){ return arItem.mValue == 'R';});

    size_t yellows = std::count_if(arString.begin(), arString.end(), 
        [](const SearchItem& arItem) 
        { 
            return arItem.mValue == 'Y';
        }
    );

    int score = 0;
    if (reds > 0 && yellows > 0) // This means there are both reds and yellows present.
        return 0;

    switch(reds) {
       case 1:
           score = 100;
           break;
       case 2:
           score = 300;
           break;
       case 3:
           score = 600;
           break;
       case 4:
           //std::cout << "winner winner chicken dinner" << std::endl;
           score = WINNING_SCORE;
           break;
    }

    switch(yellows) {
       case 1:
           score = -100;
           break;
       case 2:
           score = -300;
           break;
       case 3:
           score = -600;
           break;
       case 4:
           //std::cout << "looser looser hit the boozer" << std::endl;
           score = LOOSING_SCORE;
           break;
    }

    return score;
}

int SearchLine::scoreSearch()
{
    int score = 0;
    unsigned int idx = 0;

    /*
    So does it for 0 then 1, then 2
    ****** Original string
    ****   0
     ****  1
      **** 2
    */

    int best = 0;
    int worst = 0;
    while (idx <= mItems.size() - 4) 
    {
        std::vector<SearchItem>::iterator begin = mItems.begin() + idx;
        std::vector<SearchItem>::iterator end  = begin + 4;
        std::vector<SearchItem> four(begin,end);

       int fourCellScore = scoreFourCells(four);
       // Below is nice line of debug...
       ///// std::cout << "score " << fourCellScore << "[" << four << "]"<< " for " << idx << std::endl;

       if (fourCellScore == WINNING_SCORE || fourCellScore == LOOSING_SCORE) 
       {
           score = fourCellScore;
           for (auto item: four) { mWinningLine.push_back(item.mPosition);}
           break;
       }
           
      if (fourCellScore > 0) best += fourCellScore;
      if (fourCellScore < 0) worst += fourCellScore;

      if (best > abs(worst))
          score = best;
      else
          score = worst;

       idx++;
    }
    return score;
}

void StrengthSearch::setGameState(GameState* apGameState)
{
    mSearchData.clear();
    std::vector<int>::iterator it = lineData.begin();

    SearchLine line;
    for (it = lineData.begin(); it != lineData.end(); it++) {
        if (*it == -1) {
            line.reverse();
            mSearchData.push_back(line);

            line.clear();
        }
        else {
            char value = ' ';
            enum Piece piece = apGameState->getValueAtPosition(*it);
            if (piece == Piece::YELLOW)
                value = 'Y';
            else if (piece == Piece::RED)
                value = 'R';

            line.appendItem(value, *it);
        }
    }
}

void StrengthSearch::output() 
{
//    std::vector<std::string >::iterator it;

//    std::cout << "There are " << mSearchData.size() << std::endl;
//    for (it = mSearchData.begin(); it != mSearchData.end(); ++it) {
//        std::cout << *it << std::endl;
//    }
}



int StrengthSearch::getStrength()
{
    // for each string in mSearchData get a score and return the 
    // sum of the scores

    int score = 0;
    int best = 0;
    int worst = 0;
    for (std::vector<SearchLine>::iterator it = mSearchData.begin();
         it != mSearchData.end();
         it++)
    {
        int thisScore = it->scoreSearch();
        if (thisScore > best) best = thisScore;

        if (thisScore < worst) worst = thisScore;

        if (thisScore == WINNING_SCORE || thisScore == LOOSING_SCORE) {
            score = thisScore;
            mWinningLine = it->getWinningPositions();
          //std::cout << "Start winner... "<< std::endl;
          //for (auto pos : winningLine)
          //{
          //    std::cout << "Winning pos " << pos << std::endl;
          //}
          //std::cout << "Start winner... "<< std::endl;
            break;
        }

        if (best > abs(worst))
             score = best;
        else if (best == abs(worst)) 
        {
              score = 0;
        }
        else
             score = worst;
        //std::cout << mName << " scored " << debugCount++ << " current " <<  thisScore << " total " << score << std::endl;
    }


    return score;
}
std::vector<int> StrengthSearch::getWinningPositions()
{
    return mWinningLine;
}

std::vector<int> BoardStrengthCalculator::getWinningPositions()
{
   return mWinningLine;
}

void StrengthSearch::setLines(int aLineInfoArray[])
{
    for (int idx = 0; aLineInfoArray[idx] != -2; idx++) {
        lineData.push_back(aLineInfoArray[idx]);
    }

    // The final -2 is not included so include a -1 to end
    // the last line.
    lineData.push_back(-1);
}

/******************************************************************************/
VerticalSearch::VerticalSearch()
{
    int verticalData[] ={0,  1,  2,  3,  4,  5,  -1,
                         6,  7,  8,  9,  10, 11, -1,
                         12, 13, 14, 15, 16, 17, -1,
                         18, 19, 20, 21, 22, 23, -1,
                         24, 25, 26, 27, 28, 29, -1,
                         30, 31, 32, 33, 34, 35, -1,
                         36, 37, 38, 39, 40, 41, -2};
     setLines(verticalData);
     mName = "verticalSearch";
};

/******************************************************************************/

HorizontalSearch::HorizontalSearch()
{
    int horizontalData[] ={0,  6,  12, 18, 24, 30, 36, -1,
                           1,  7,  13, 19, 25, 31, 37, -1,
                           2,  8,  14, 20, 26, 32, 38, -1,
                           3,  9,  15, 21, 27, 33, 39, -1,
                           4,  10, 16, 22, 28, 34, 40, -1,
                           5,  11, 17, 23, 29, 35, 41, -2};

     setLines(horizontalData);

     mName = "horizSearch";
}


/******************************************************************************/
UpDiagonal::UpDiagonal()
{
    int upDiagonalData[] ={ 3,  8,  13, 18, -1,     
                            4,  9,  14, 19, 24, -1, 
                            5,  10, 15, 20, 25, 30, -1,
                            11, 16, 21, 26, 31, 36, -1,
                            17, 22, 27, 32, 37, -1, 
                            23, 28, 33, 38, -2};
    setLines(upDiagonalData);
    mName = "upDiagonal";
}

/******************************************************************************/

DownDiagonal::DownDiagonal()
{
    int downDiagonalData[] ={ 18, 25, 32, 39, -1,     
                              12, 19, 26, 33, 40, -1, 
                              6,  13, 20, 27, 34, 41, -1,
                              0,  7,  14, 21, 28, 35, -1,
                              1,  8,  15, 22, 29, -1, 
                              2,  9,  16, 23, -2};
    setLines(downDiagonalData);

    mName = "downDiagonal";
}

/******************************************************************************/

BoardStrengthCalculator::BoardStrengthCalculator()
{
   mBoardSearches.push_back(&vertical);
   mBoardSearches.push_back(&horizontal);
   mBoardSearches.push_back(&upDiagonal);
   mBoardSearches.push_back(&downDiagonal);
}

void BoardStrengthCalculator::setTree(GameState* apGameState)
{
    //  This method will update the 4 StrengthSearch objects
    //  with the details of this GameState

    vertical.setGameState(apGameState);
    horizontal.setGameState(apGameState);
    upDiagonal.setGameState(apGameState);
    downDiagonal.setGameState(apGameState);
}
int BoardStrengthCalculator::getBoardStrength()
{
    int score = 0;
    int best = 0;
    int worst = 0;
    for (std::vector<StrengthSearch*>::iterator it = mBoardSearches.begin();
         it != mBoardSearches.end();
         it++) 
    {
        int currentScore = (*it)->getStrength();
        if (currentScore > 0) best += currentScore;
        if (currentScore < worst) worst += currentScore;

        //if (currentScore == WINNING_SCORE || currentScore == LOOSING_SCORE) {
        //   score = currentScore;
        //   break;
        //}
        for (auto pos : (*it)->getWinningPositions())
            mWinningLine.push_back(pos);

    }

    if (best > abs(worst))
         score = best;
    else if (best == abs(worst)) 
    {
          score = 0;
    }
    else
         score = worst;

    //std::cout << "BoardStrength is " << score << std::endl;
    return score;
}
