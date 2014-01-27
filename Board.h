#ifndef BOARD_H
#define BOARD_H
#include <vector>
enum Peice {
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
       std::vector<Peice> colData;
       int columnId;
      
    public:
       Column(int id);
       int getId();
       const static int MaxHeight = 6;
       Peice getPositionStatus(int level);
       void addPeice(Peice position);
       const bool isFull();
};

class Board {

    private:
          std::vector<Column> mColumns;
   public: 
          Board();
          void init();

          void addPeice(Peice peice, enum ColumnName column);
      
          Peice getPositionStatus(enum ColumnName column, int level);
};

#endif  // BOARD_H
