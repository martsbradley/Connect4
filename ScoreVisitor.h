#ifndef SCOREVISITOR_H
#define SCOREVISITOR_H

#include "Visitor.h"
#include "BoardStrength.h"

class GameState;


class ScoreVisitor: public Visitor
{

public:
    virtual void visit(GameState* apGameState);

private:
    void min(GameState* apGameState);
    void max(GameState* apGameState);
    void setup(GameState* apGameState);
    BoardStrength mStrength;
};
#endif // VISITOR_H
