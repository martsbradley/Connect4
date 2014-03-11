#include "DisplayVisitor.h"
#include "TreeBuilder.h"
#include <iostream>
static int countChildren(GameState& arGameState)
{
    int children = 0;
    std::vector<GameState*>& states =  arGameState.getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        children++;
    }
    return children;
}

void DisplayVisitor::visit(GameState& arGameState)
{
    int score = arGameState.getScore();
    int level = arGameState.getLevel();
    int children = countChildren(arGameState);
    
    std::cout << "GameState level:" << level << " children:" << children << " score:" << score << std::endl;

    std::vector<GameState*>& states =  arGameState.getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        GameState* pGameState = *it;
        
        if (pGameState != 0)
            visit(*pGameState);
    }
}

