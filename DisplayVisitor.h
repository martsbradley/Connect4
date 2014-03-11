#ifndef DISPLAYVISITOR_H
#define DISPLAYVISITOR_H

#include "Visitor.h"

class GameState;


class DisplayVisitor: public Visitor
{

public:
    virtual void visit(GameState& arGameState);

private:
};
#endif // VISITOR_H
