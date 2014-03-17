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

void ScoreVisitor::visit(GameState* apGameState)
{
    min(apGameState);

    std::cout << "score is " << apGameState->getMinMaxValue() << std::endl;



    ValueEquals va(apGameState->getMinMaxValue());

    std::vector<GameState*>& states =  apGameState->getNextStates();

    std::vector<GameState*>::iterator it = std::find_if(states.begin(),
                                                        states.end(),
                                                        va);
    if (it != states.end())
    {
        std::cout <<" Found it" << std::endl;    
        VerticalSearch se;
        se.setGameState(*it);
        se.output();
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

    if (states.size() == 0)
    {
        mStrength.setTree(apGameState); 
        int score = mStrength.getBoardStrength();
        apGameState->setMinMaxValue(score);
        std::cout << "set the min score to " << score << std::endl;
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

void ScoreVisitor::max(GameState* apGameState)
{
    std::vector<GameState*>& states =  apGameState->getNextStates();

    if (states.size() == 0)
    {
        mStrength.setTree(apGameState); 
        int score = mStrength.getBoardStrength();
        apGameState->setMinMaxValue(score);
        std::cout << "set the max score" << std::endl;
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
