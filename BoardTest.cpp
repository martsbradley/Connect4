#include "BoardTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( BoardTest );


void BoardTest::setUp()
{
    mpBoard = new Board();
}


void BoardTest::tearDown()
{
    delete mpBoard;
}


void BoardTest::testNextPiece()
{
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(YELLOW,    mpBoard->getNextPiece());
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getNextPiece());
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(YELLOW,    mpBoard->getNextPiece());
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getNextPiece());
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(YELLOW,    mpBoard->getNextPiece());
    mpBoard->addPiece(COLUMN0);
    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getNextPiece());
}

void BoardTest::testGetPositionStatus() {
    mpBoard->addPiece(COLUMN0);//RED
    mpBoard->addPiece(COLUMN1);
    mpBoard->addPiece(COLUMN2);//RED
    mpBoard->addPiece(COLUMN3);
    mpBoard->addPiece(COLUMN4);//RED

    mpBoard->addPiece(COLUMN0);
    mpBoard->addPiece(COLUMN1);//RED
    mpBoard->addPiece(COLUMN2);
    mpBoard->addPiece(COLUMN3);//RED
    mpBoard->addPiece(COLUMN4);

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN0,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN0,1));

    CPPUNIT_ASSERT_EQUAL(YELLOW,    mpBoard->getPositionStatus(COLUMN1,0));
    CPPUNIT_ASSERT_EQUAL(RED, mpBoard->getPositionStatus(COLUMN1,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN2,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN2,1));

    CPPUNIT_ASSERT_EQUAL(YELLOW,    mpBoard->getPositionStatus(COLUMN3,0));
    CPPUNIT_ASSERT_EQUAL(RED, mpBoard->getPositionStatus(COLUMN3,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN4,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN4,1));
}

void BoardTest::testEquals() {
    mpBoard->addPiece(COLUMN0);//RED

    Board nextBoard;
    nextBoard.addPiece(COLUMN0);//RED
    CPPUNIT_ASSERT(*mpBoard == nextBoard);

    nextBoard.addPiece(COLUMN0);//YELLOW
    CPPUNIT_ASSERT(! (*mpBoard == nextBoard));

    mpBoard->addPiece(COLUMN0);//YELLOW
    CPPUNIT_ASSERT( *mpBoard == nextBoard);

    mpBoard->addPiece(COLUMN4);//RED
    nextBoard.addPiece(COLUMN4);//RED
    CPPUNIT_ASSERT( *mpBoard == nextBoard);
}


void BoardTest::testNextTurnBasic() {
    mpBoard->addPiece(COLUMN0);//RED

    Board nextBoard;
    nextBoard.addPiece(COLUMN0);// RED
    nextBoard.addPiece(COLUMN0);// YELLOW

    std::vector<Board> boards = mpBoard->generateNextTurns();
    CPPUNIT_ASSERT( boards[0] == nextBoard );

    Board nextBoard2;
    nextBoard2.addPiece(COLUMN0);// RED
    nextBoard2.addPiece(COLUMN1);// YELLOW

    CPPUNIT_ASSERT( boards[1] == nextBoard2);

    Board nextBoard3;
    nextBoard3.addPiece(COLUMN0);// RED
    nextBoard3.addPiece(COLUMN2);// YELLOW

    CPPUNIT_ASSERT( boards[2] == nextBoard3);



    /// SKIP TO THE LAST COLUMN
    Board nextBoard7;
    nextBoard7.addPiece(COLUMN0);// RED
    nextBoard7.addPiece(COLUMN6);// YELLOW

    CPPUNIT_ASSERT( boards[6] == nextBoard7);
}

void BoardTest::testNextTurnAdvanced() {
    mpBoard->addPiece(COLUMN6);//RED
    mpBoard->addPiece(COLUMN5);//YELLOW
    mpBoard->addPiece(COLUMN4);//RED
    
    std::vector<Board> boards = mpBoard->generateNextTurns();
    Board nextBoard;
    nextBoard.addPiece(COLUMN6);//RED
    nextBoard.addPiece(COLUMN5);//YELLOW
    nextBoard.addPiece(COLUMN4);//RED

    Board nextTurn1(nextBoard);
    nextTurn1.addPiece(COLUMN0);
    CPPUNIT_ASSERT( boards[0] == nextTurn1);

    Board nextTurn2(nextBoard);
    nextTurn2.addPiece(COLUMN1);
    CPPUNIT_ASSERT( boards[1] == nextTurn2);

    Board nextTurn3(nextBoard);
    nextTurn3.addPiece(COLUMN2);
    CPPUNIT_ASSERT( boards[2] == nextTurn3);

    Board nextTurn7(nextBoard);
    nextTurn7.addPiece(COLUMN6);
    CPPUNIT_ASSERT( boards[6] == nextTurn7);
}


void BoardTest::testGenerateNextTurns() {
    mpBoard->addPiece(COLUMN0);//RED
    mpBoard->addPiece(COLUMN0);//YELLOW
    mpBoard->addPiece(COLUMN0);//RED
    mpBoard->addPiece(COLUMN0);//YELLOW
    mpBoard->addPiece(COLUMN0);//RED
    mpBoard->addPiece(COLUMN0);//YELLOW

    CPPUNIT_ASSERT_EQUAL(RED, mpBoard->getNextPiece());

    std::vector<Board> nextBoards = mpBoard->generateNextTurns();

    CPPUNIT_ASSERT( 6 == nextBoards.size());

    std::vector<Board>::iterator it;

    for (it = nextBoards.begin(); it != nextBoards.end(); ++it)
    {
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN0) == false);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN1) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN2) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN3) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN4) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN5) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN6) == true);
        CPPUNIT_ASSERT_EQUAL(YELLOW, it->getNextPiece());
    }
    //  Checks two generations.
    CPPUNIT_ASSERT_EQUAL(RED, nextBoards[0].generateNextTurns()[0].getNextPiece());

    mpBoard->addPiece(COLUMN1);//RED
    mpBoard->addPiece(COLUMN1);//YELLOW
    mpBoard->addPiece(COLUMN1);//RED
    mpBoard->addPiece(COLUMN1);//YELLOW
    mpBoard->addPiece(COLUMN1);//RED
    mpBoard->addPiece(COLUMN1);//YELLOW

    nextBoards = mpBoard->generateNextTurns();
    CPPUNIT_ASSERT( 5 == nextBoards.size());
    for (it = nextBoards.begin(); it != nextBoards.end(); ++it)
    {
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN0) == false);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN1) == false);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN2) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN3) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN4) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN5) == true);
        CPPUNIT_ASSERT( it->canAddPiece(COLUMN6) == true);
    }
}
