#include "StrengthSearchTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "TreeBuilder.h"
#include "BoardStrength.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( StrengthSearchTest );


void StrengthSearchTest::setUp()
{
    mpBoard = new Board();
}


void StrengthSearchTest::tearDown()
{
    delete mpBoard;
}


void StrengthSearchTest::testFourEmptySquares()
{
    GameState gameState;
    gameState.setGameState(*mpBoard);
    VerticalSearch vertical;
    vertical.setGameState(gameState);

    CPPUNIT_ASSERT_EQUAL(0, vertical.getStrength()) ;
}
void StrengthSearchTest::testFourRedSquares()
{
    GameState gameState;
    // COlUMN 1 will have four reds.
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN6);// 
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN4);//
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN2);//
    mpBoard->addPiece(COLUMN0);// RED

    gameState.setGameState(*mpBoard);
    VerticalSearch vertical;
    vertical.setGameState(gameState);
    //vertical.output();

    CPPUNIT_ASSERT_EQUAL(WINNING_SCORE, vertical.getStrength()) ;

}

void StrengthSearchTest::testFourYellowSquares()
{
    GameState gameState;
    // Column 6 will have four YELLOWS
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN6);// 
    mpBoard->addPiece(COLUMN1);// RED
    mpBoard->addPiece(COLUMN6);//
    mpBoard->addPiece(COLUMN2);// RED
    mpBoard->addPiece(COLUMN6);//
    mpBoard->addPiece(COLUMN3);// RED
    mpBoard->addPiece(COLUMN6);//
    mpBoard->addPiece(COLUMN4);// RED

    gameState.setGameState(*mpBoard);
    VerticalSearch vertical;
    vertical.setGameState(gameState);

    CPPUNIT_ASSERT_EQUAL(LOOSING_SCORE, vertical.getStrength()) ;
}
void StrengthSearchTest::testUpDiagonal()
{
    // Column 6 will have four YELLOWS
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN1);// YELLOW
    mpBoard->addPiece(COLUMN1);// RED

    mpBoard->addPiece(COLUMN2);// YELLOW
    mpBoard->addPiece(COLUMN2);// RED                              //    R                
                                                                   //   RR                
    mpBoard->addPiece(COLUMN3);// YELLOW                           //  RRY                 
    mpBoard->addPiece(COLUMN2);// RED                              // RYYYY                   
    mpBoard->addPiece(COLUMN3);// YELLOW
    mpBoard->addPiece(COLUMN3);// RED
    mpBoard->addPiece(COLUMN4);// YELLOW
    mpBoard->addPiece(COLUMN3);// RED        




    GameState gameState;
    gameState.setGameState(*mpBoard);
    UpDiagonal upDiagonal;
    upDiagonal.setGameState(gameState);

    CPPUNIT_ASSERT_EQUAL(WINNING_SCORE, upDiagonal.getStrength()) ;
}
