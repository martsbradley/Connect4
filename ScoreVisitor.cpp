#include "ScoreVisitor.h"
#include "TreeBuilder.h"

void ScoreVisitor::visit(GameState& arGameState)
{
    mStrength.setTree(arGameState); 
    int score = mStrength.getBoardStrength();
    arGameState.setScore(score);

    std::vector<GameState*>& states =  arGameState.getNextStates();
    std::vector<GameState*>::iterator it; 

    for (it = states.begin(); it != states.end(); ++it) {
        GameState* pGameState = *it;
        
        if (pGameState != 0)
            visit(*pGameState);
    }
}
