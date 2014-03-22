#ifndef SCOREVISITOR_H
#define SCOREVISITOR_H

#include "Visitor.h"
#include "BoardStrength.h"

class GameState;


class ScoreVisitor: public Visitor
{

public:
    ScoreVisitor();
    virtual void visit(GameState* apGameState);
    int getBestCol();
    bool isGameOver();

private:
    void min(GameState* apGameState);
    void max(GameState* apGameState);
    void setup(GameState* apGameState);
    BoardStrength mStrength;
    int mColumnToInsert;
    bool mGameOver;
};
#endif // VISITOR_H
