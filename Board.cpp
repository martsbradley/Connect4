#include "Board.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>



void Column::addPiece(Piece status) {
    if (isFull()) {
        std::ostringstream s;
        s << "Column " << mColumnId << " is full";
        std::string reason;
        reason = s.str();
        throw std::logic_error(reason);
    }

    colData.push_back(status);
}

const bool Column::isFull() {
    return colData.size() >= Column::MaxHeight;
}

Column::Column(int aId)
: mColumnId(aId) {
}

int Column::getId() const {
  return mColumnId;
}
void Column::reset() {
  return colData.clear();
}

//  Checks that the level is in bounds.
static void checkLevel(int level) {
    if (level < 0 || level > Column::MaxHeight) {
        throw std::logic_error("row out of bounds");
    }
}

Piece Column::getPositionStatus(int level) {
    checkLevel(level);
    int columnSize = colData.size(); 

    if (level < columnSize) {
       return colData[level];
    }
    else {
       return EMPTY;
    }
}

int Column::getCount() 
{
    return colData.size();
}

bool Column::operator==(const Column& arColumn) const
{
    return mColumnId == arColumn.mColumnId
           && colData == arColumn.colData;
}


Board::Board() {
    mColumns.push_back(Column(0));
    mColumns.push_back(Column(1));
    mColumns.push_back(Column(2));
    mColumns.push_back(Column(3));
    mColumns.push_back(Column(4));
    mColumns.push_back(Column(5));
    mColumns.push_back(Column(6));
    nextPiece = RED;
    mGameOver = false;
}
Board::Board(const Board& arBoard) {
    mColumns.push_back(arBoard.mColumns[0]);
    mColumns.push_back(arBoard.mColumns[1]);
    mColumns.push_back(arBoard.mColumns[2]);
    mColumns.push_back(arBoard.mColumns[3]);
    mColumns.push_back(arBoard.mColumns[4]);
    mColumns.push_back(arBoard.mColumns[5]);
    mColumns.push_back(arBoard.mColumns[6]);
    nextPiece = arBoard.nextPiece;
    mGameOver = arBoard.mGameOver;
}

void Board::reset()
{
    std::vector<Column>::iterator it;
    for (it = mColumns.begin(); it != mColumns.end(); it++) {
        it->reset();
    }
    mGameOver = false;
}

// helper method avoids polluting the interface of the class.
static void checkColumn(unsigned int column, std::vector<Column>& arColumns ) {
    if (column < 0 || column >= arColumns.size()) {
        throw std::logic_error("Index out of bounds");
    }
}

void Board::addPiece(enum ColumnName column) {
    checkColumn(column, mColumns);

    if (!mColumns[column].isFull()) {
        mColumns[column].addPiece(nextPiece);
        
        if (nextPiece == RED) {
            nextPiece = YELLOW;
        }
        else {
            nextPiece = RED;
        }
    }
}
Piece Board::getNextPiece() const
{
    return nextPiece;
}

Piece Board::getPositionStatus(enum ColumnName column, int level) {
   checkColumn(column, mColumns);
   return mColumns[column].getPositionStatus(level);   
}

int Board::howManyPiecesInColumn(enum ColumnName column){
   return mColumns[column].getCount();
}

void Board::addBoardListener(BoardListener* apBoardListener)
{
    mListeners.push_back(apBoardListener);
}

bool Board::operator==(const Board& arBoard) const
{
    bool isNextPieceSame = arBoard.getNextPiece() == nextPiece;
    if (!isNextPieceSame) return isNextPieceSame;

    std::vector<Column>::const_iterator itMyCol;
    std::vector<Column>::const_iterator itHisCol;
    bool colsSame = true;

    for (itMyCol = mColumns.begin(),
         itHisCol = arBoard.mColumns.begin(); 
         colsSame && itMyCol != mColumns.end(); 
         itMyCol++, itHisCol++) {
         const Column& rMyColumn = *itMyCol;
         const Column& rHisColumn = *itHisCol;

        colsSame  = rMyColumn == rHisColumn;
    }

    return colsSame;
}

std::vector<Board> Board::generateNextTurns()
{
    std::vector<Board> boards;

    std::vector<Column>::iterator it;

    for (it = mColumns.begin(); it != mColumns.end(); it++)
    {
        Column& rColumn = *it;
        if (rColumn.isFull()) continue;

        Board board(*this); //  copy of this board
        board.addPiece((enum ColumnName)rColumn.getId());
        boards.push_back(board);
    }


    return boards;
}

bool Board::canAddPiece(enum ColumnName column)
{
    checkColumn(column, mColumns);

    return !mColumns[column].isFull();
}


bool Board::isGameOver()
{
	return mGameOver;
}

void Board::setGameOver(bool aGameOver)
{
	mGameOver = aGameOver;
}



