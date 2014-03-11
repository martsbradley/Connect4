#ifndef VISITOR_H
#define VISITOR_H

class GameState;


class Visitor
{
public:
    virtual void visit(GameState& arGameState) = 0;
};
#endif // VISITOR_H
