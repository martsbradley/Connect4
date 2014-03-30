#include "ScoreVisitor.h"
#include "TreeBuilder.h"
#include <algorithm>
#include <iostream>
#include <functional>



bool absLess(GameState* apA, GameState* apB)
{
   return apA->getMinMaxValue() < apB->getMinMaxValue();
}

class ValueEquals 
{
private:
    int mScore;
public:
    ValueEquals(int aScore):mScore(aScore)
    {
    }

    bool operator()(GameState* apGameState)
    {
        return apGameState->getMinMaxValue() == mScore;
    }
};

ScoreVisitor::ScoreVisitor()
  : mColumnToInsert(0)
    //mGameOver(false)
{
}

//  bool ScoreVisitor::isGameOver()
//  {
//      return mGameOver;
//  }


void displayScore(GameState* pState)
{
	std::cout << "Score " << pState->getMinMaxValue() << std::endl;
}
void ScoreVisitor::visit(GameState* apGameState)
{
    min(apGameState);
  //if (abs(apGameState->getMinMaxValue()) >= 1000000)
  //{
  //   std::cout << "Game must be over because " << apGameState->getMinMaxValue() << std::endl;
  //	mGameOver = true;
  //}

    ValueEquals va(apGameState->getMinMaxValue());

    std::vector<GameState*>& states =  apGameState->getNextStates();
    //std::for_each(states.begin(), states.end(), displayScore);

    std::vector<GameState*>::iterator it = std::find_if(states.begin(),
                                                        states.end(),
                                                        va);
    if (it != states.end())
    {
        //std::cout << "Found it" << std::endl;
        //(*it)->output();

        std::vector<int> heightsBeforeMove = apGameState->getColumnsHeights();
        std::vector<int> heightsAfterMove = (*it)->getColumnsHeights();

        std::vector<int>::iterator itAfter = heightsAfterMove.begin();
        std::vector<int>::iterator itBefore = heightsBeforeMove.begin();

        int counter = 0;
        while (itAfter != heightsAfterMove.end())
        {
           int colHeightAfter = *itAfter;
           int colHeightBefore =  *itBefore;
         //  std::cout << "colHeightBefore " << colHeightBefore << " colHeightAfter " << colHeightAfter <<std::endl;

           if (colHeightAfter > colHeightBefore)
           {
               mColumnToInsert= counter;
               //break;
           }
           counter++;
           itAfter++;
           itBefore++;
        }
        //std::cout << "Counter = " << mColumnToInsert << std::endl;
    }
}


/*void ScoreVisitor::setup(GameState* apGameState)
{
    mStrength.setTree(apGameState); 
    int score = mStrength.getBoardStrength();
    apGameState->setScore(score);

    std::vector<GameState*>& states =  apGameState->getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        GameState* pGameState = *it;
        
        if (pGameState != 0)
        {
            mStrength.setTree(pGameState); 
            int score = mStrength.getBoardStrength();
            pGameState->setScore(score);
        }
    }
}


void ScoreVisitor::min(GameState* apGameState)
{
    setup(apGameState);

    std::vector<GameState*>& states =  apGameState->getNextStates();

    std::vector<GameState*>::iterator minIt = std::min_element(states.begin(), states.end(), absLess);
    if (minIt != states.end())
    {
       int minMaxScore = (*minIt)->getScore() ;

       apGameState->setMinMaxValue(minMaxScore);

       std::cout << "Min had " << minMaxScore << std::endl;
       max(*minIt);
    }
}

void ScoreVisitor::max(GameState* apGameState)
{
    setup(apGameState);

    std::vector<GameState*>& states =  apGameState->getNextStates();

    std::vector<GameState*>::iterator maxIt = std::max_element(states.begin(), states.end(), absLess);
    if (maxIt != states.end())
    {
       int minMaxScore = (*maxIt)->getScore() ;

       apGameState->setMinMaxValue(minMaxScore);

       std::cout << "Max had " << minMaxScore << std::endl;
       min(*maxIt);
    }
}
*/

/*
    If you have children there do not get the score.
    


*/
void ScoreVisitor::min(GameState* apGameState)
{
    std::vector<GameState*>& states =  apGameState->getNextStates();

    mStrength.setTree(apGameState);
	int score = mStrength.getBoardStrength();

	bool winner = false;

	if (abs(score) >= 1000000) winner = true;


    if (states.size() == 0 || winner)
    {
//        mStrength.setTree(apGameState);
//        int score = mStrength.getBoardStrength();
        apGameState->setMinMaxValue(score);
        //std::cout << "set the min score to " << score << std::endl;
    }
    else
    {
        std::vector<GameState*>::iterator it; 

        for (it = states.begin(); it != states.end(); ++it)
        {
           max(*it);
        }

        std::vector<GameState*>::iterator minIt = std::min_element(states.begin(), states.end(), absLess);

        if (minIt != states.end()) 
        {
            GameState* pState = *minIt;

            apGameState->setMinMaxValue(pState->getMinMaxValue());
        }
    }
}

int ScoreVisitor::getBestCol()
{
    return mColumnToInsert;
}

void ScoreVisitor::max(GameState* apGameState)
{
    std::vector<GameState*>& states =  apGameState->getNextStates();

    mStrength.setTree(apGameState);
  	int score = mStrength.getBoardStrength();
	bool winner = false;

	if (abs(score) >= 1000000) winner = true;



    if (states.size() == 0 || winner)
    {
//        mStrength.setTree(apGameState);
//        int score = mStrength.getBoardStrength();
        apGameState->setMinMaxValue(score);
        //std::cout << "set the max score" << std::endl;
    }
    else
    {
        std::vector<GameState*>::iterator it; 

        for (it = states.begin(); it != states.end(); ++it)
        {
           min(*it);
        }

        std::vector<GameState*>::iterator maxIt = std::max_element(states.begin(), states.end(), absLess);

        if (maxIt != states.end()) 
        {
            GameState* pState = *maxIt;

            apGameState->setMinMaxValue(pState->getMinMaxValue());
        }
    }
}
