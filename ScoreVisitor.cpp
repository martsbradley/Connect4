#include "ScoreVisitor.h"
#include "TreeBuilder.h"
#include <algorithm>
#include <iostream>

void ScoreVisitor::visit(GameState* apGameState)
{
    min(apGameState);
}


bool absLess(GameState* apA, GameState* apB)
{
   return apA->getScore() < apB->getScore();
}

void ScoreVisitor::setup(GameState* apGameState)
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

/*
    If you have children there do not get the score.
    


*/
