#ifndef BOARD_H
#define BOARD_H
#include <vector>
enum class Piece {
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

class Board 
{

public: 
    Board();
    Board(const Board& arBoard);
    void reset();

    void addPiece(enum ColumnName column,bool updateGameOver = true);
    Piece getNextPiece() const;

    Piece getPositionStatus(enum ColumnName column, int level);
    int howManyPiecesInColumn(enum ColumnName column);

    std::vector<Board> generateNextTurns();

    bool operator==(const Board& arBoard) const;
    bool canAddPiece(enum ColumnName column);
    bool isGameOver();
	void setGameOver(bool aGameOver);
    std::vector<int> getWinningPositions();
private:
    std::vector<Column> mColumns;
    Piece nextPiece;
    bool mGameOver;
    std::vector<int> mWinningPositions;
};
#endif  // BOARD_H
