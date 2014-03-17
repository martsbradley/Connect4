#include "DisplayVisitor.h"
#include "TreeBuilder.h"
#include <iostream>
static int countChildren(GameState* apGameState)
{
    int children = 0;
    std::vector<GameState*>& states =  apGameState->getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        children++;
    }
    return children;
}

void DisplayVisitor::visit(GameState* apGameState)
{
    int score = apGameState->getScore();
    int level = apGameState->getLevel();
    int children = countChildren(apGameState);
    
    std::cout << "GameState level:" << level << " children:" << children << " score:" << score << std::endl;

    std::vector<GameState*>& states =  apGameState->getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        GameState* pGameState = *it;
        
        if (pGameState != 0)
            visit(pGameState);
    }
}

