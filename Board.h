#ifndef BOARD_H
#define BOARD_H
#include <vector>
enum Piece {
   RED,
   YELLOW,
   EMPTY
};
enum ColumnName {
   COLUMN0 = 0,
   COLUMN1,
   COLUMN2,
   COLUMN3,
   COLUMN4,
   COLUMN5,
   COLUMN6,
};


class BoardListener
{
public:
    virtual void peiceAdded(enum Piece aPiece, enum ColumnName aCol, int level) = 0;
    virtual void clearBoarded() = 0;
};


class Column {
private:
    std::vector<Piece> colData;
    int mColumnId;
       
      
public:
   
    bool operator==(const Column& arColumn) const;
    Column(int id);
    int getId() const;
    int getCount();
    const static int MaxHeight = 6;
    Piece getPositionStatus(int level);
    void addPiece(Piece position);
    const bool isFull();
    void reset();
};

class Board {

public: 
    Board();
    Board(const Board& arBoard);
    void reset();

    void addPiece(enum ColumnName column);
    Piece getNextPiece() const;

    Piece getPositionStatus(enum ColumnName column, int level);
    int howManyPiecesInColumn(enum ColumnName column);

    void addBoardListener(BoardListener* apBoardListener);

    std::vector<Board> generateNextTurns();

    bool operator==(const Board& arBoard) const;
    bool canAddPiece(enum ColumnName column);
private:
    std::vector<Column> mColumns;
    std::vector<BoardListener*> mListeners;
    Piece nextPiece;
};
#endif  // BOARD_H
