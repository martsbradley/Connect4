#include "Board.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>

void Column::addPeice(Peice status) {
    if (isFull()) {
        std::ostringstream s;
        s << "Column " << columnId << " is full";
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
: columnId(aId) {
}

int Column::getId() {
  return columnId;
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

Peice Column::getPositionStatus(int level) {
    checkLevel(level);

    if (level < colData.size()) {
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


Board::Board() {
    mColumns.push_back(Column(0));
    mColumns.push_back(Column(1));
    mColumns.push_back(Column(2));
    mColumns.push_back(Column(3));
    mColumns.push_back(Column(4));
    mColumns.push_back(Column(5));
    mColumns.push_back(Column(6));
}

void Board::reset()
{
    std::vector<Column>::iterator it;
    for (it = mColumns.begin(); it != mColumns.end(); it++) {
        it->reset();
    }
}

// helper method avoids polluting the interface of the class.
static void checkColumn(int column, std::vector<Column>& arColumns ) {
    if (column < 0 || column >= arColumns.size()) {
        throw std::logic_error("Index out of bounds");
    }
}

void Board::addPeice(Peice peice, enum ColumnName column) {
    checkColumn(column, mColumns);

    if (!mColumns[column].isFull()) {
        mColumns[column].addPeice(peice);
    }
}

Peice Board::getPositionStatus(enum ColumnName column, int level) {
   checkColumn(column, mColumns);
   return mColumns[column].getPositionStatus(level);   
}

int Board::howManyPeicesInColumn(enum ColumnName column){
   return mColumns[column].getCount();
}

