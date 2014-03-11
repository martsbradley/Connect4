#include "ScoreVisitor.h"
#include "TreeBuilder.h"

//constructor is sent the maxLevel and the first boardposition
// it creates the gameStates

mMaxLevel
GameState* mpGameStateRoot;
Board& arBoard

GameStateBuilderVistor::GameStateBuilderVistor(int aMaxLevel, Board& arBoard)
{
    mpGameStateRoot = new GameState();
}

GameStateBuilderVistor::build() 
{
   visit(*mpGameStateRoot);
}


void GameStateBuilderVistor::visit(Board& arBoard)
{
     mpCurrent = new GameState();

     if (mpGameStateRoot == null) {
         mpGameStateRoot = mpCurrent;
         mpGameStateRoot->setLevel(0);
     }

     std::vector<Board> nextBoards = arBoard.generateNextTurns();
     if (



}
void GameStateBuilderVistor::visit(GameState& arGameState)
{
    setScoreOnGameState(arGameState);

    NextStates* pNextStates = arGameState.getNextStates();

    for (int idx = 0; pNextStates != 0 && idx < 7; ++idx) {
        GameState* pGameState = pNextStates->getGameState(idx);
        
        if (pGameState != 0)
            visit(*pGameState);
    }
}

void GameStateBuilderVistor::setScoreOnGameState(GameState& arGameState)
{
    mStrength.setTree(arGameState); 
    int score = mStrength.getBoardStrength();
    arGameState.setScore(score);
}
