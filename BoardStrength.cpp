#include "BoardStrength.h"
#include <iostream>

#include "TreeBuilder.h"


void StrengthSearch::setGameState(GameState& arGameState)
{
    searchData.clear();
    std::vector<int>::iterator it = lineData.begin();

    std::string line;
    for (it = lineData.begin(); it != lineData.end(); it++) {
        if (*it == -1)
            searchData.push_back(line);
        else {
            char value = ' ';
            enum Piece piece = arGameState.getValueAtPosition(*it);
            if (piece == YELLOW)
                value = 'Y';
            else if (piece == RED)
                value = 'R';

            line.push_back(value);
        }
    }
}

void StrengthSearch::output() 
{
    std::vector<std::string>::iterator it;

    for (it = searchData.begin(); it != searchData.end(); ++it) {
        std::cout << *it << std::endl;
    }
}


int StrengthSearch::getStrength()
{
    return 0;
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

void BoardStrength::setTree(GameState& arGameState)
{
    //  This method will update the 4 StrengthSearch objects
    //  with the details of this GameState

    vertical.setGameState(arGameState);
    vertical.setGameState(arGameState);
    //horizontal;
    ////upDiagonal;
    //downDiagonal;

}
int verticalData[] ={0,  1,  2,  3,  4,  5,  -1,
                     6,  7,  8,  9,  10, 11, -1,
                     12, 13, 14, 15, 16, 17, -1,
                     18, 19, 20, 21, 22, 23, -1,
                     24, 25, 26, 27, 28, 29, -1,
                     30, 31, 32, 33, 34, 35, -1,
                     36, 37, 38, 39, 40, 41, -2};


int horizontalData[] ={0,  6,  12, 18, 24, 30, 36, -1,
                       1,  7,  13, 19, 25, 31, 37, -1,
                       2,  8,  14, 20, 26, 32, 38, -1,
                       3,  9,  15, 21, 27, 33, 39, -1,
                       4,  10, 16, 22, 28, 34, 40, -1,
                       5,  11, 17, 23, 29, 35, 41, -2};


int upDiagonalData[] ={ 3,  8,  13, 18, -1,     
                        4,  9,  14, 19, 24, -1, 
                        5,  10, 15, 20, 25, 30, -1,
                        11, 16, 21, 26, 31, 36, -1,
                        17, 22, 27, 32, 37, -1, 
                        23, 28, 33, 38, -1};

int downDiagonalData[] ={ 18, 25, 32, 39, -1,     
                          12, 19, 26, 33, 40, -1, 
                          6,  13, 20, 27, 34, 41, -1,
                          0,  7,  14, 21, 28, 35, -1,
                          1,  8,  15, 22, 29, -1, 
                          2,  9,  16, 23, -1};

BoardStrength::BoardStrength()
{
     vertical.setLines(verticalData);
     horizontal.setLines(horizontalData);
     upDiagonal.setLines(upDiagonalData);
     downDiagonal.setLines(downDiagonalData);
}
