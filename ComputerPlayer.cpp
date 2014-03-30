#include "ComputerPlayer.h"
#include "assert.h"
#include "TreeBuilder.h"
#include "ScoreVisitor.h"
#include "Board.h"

enum ColumnName ComputerPlayer::takeYourTurn(Board& arBoard)
{
    TreeBuilder tree;
    tree.buildTree(arBoard);

    ScoreVisitor visitor;
    GameState* pState = tree.getTree();
    pState->accept(visitor);
    //std::cout << "MinMaxScore " << pState->getMinMaxValue() << std::endl;

    enum ColumnName column = (enum ColumnName)visitor.getBestCol();
    assert(arBoard.canAddPiece(column));
    return column;
}

