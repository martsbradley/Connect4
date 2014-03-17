#include "BoardStrengthTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "TreeBuilder.h"
#include "BoardStrength.h"


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( BoardStrengthTest );


void BoardStrengthTest::setUp()
{
    mpBoard = new Board();
}


void BoardStrengthTest::tearDown()
{
    delete mpBoard;
}


void BoardStrengthTest::testEmptyBoard()
{
    GameState gameState;
    gameState.setGameState(*mpBoard);

    BoardStrength strength;
    strength.setTree(&gameState);

    CPPUNIT_ASSERT_EQUAL(0, strength.getBoardStrength()) ;
}

void BoardStrengthTest::testFourRedSquares()
{
    // COlUMN 1 will have four reds.
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN6);// 
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN4);//
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN2);//
    mpBoard->addPiece(COLUMN0);// RED

    GameState gameState;
    gameState.setGameState(*mpBoard);

    BoardStrength strength;
    strength.setTree(&gameState);

    CPPUNIT_ASSERT_EQUAL(WINNING_SCORE, strength.getBoardStrength()) ;

}

void BoardStrengthTest::testThreeRedSquares()
{
    // COlUMN 1 will have four reds.
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN6);// 
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN4);//
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN2);//

    GameState gameState;
    gameState.setGameState(*mpBoard);

    BoardStrength strength;
    strength.setTree(&gameState);

    std::cout << "testThreeRedSquares" << std::endl;
    HorizontalSearch justForOutput;
    justForOutput.setGameState(&gameState);
    justForOutput.output();

  /* Result is 1000 because looking from a vertical stand point.

    *             |
    *            ||
    *           |||
    R           |||
    R           ||
    R Y  Y  Y   |        There are three potential wins
                         One at level 3 (600) one at level 2 (300)
                         and one at level 1( 100) ie 600 + 300 + 100
   */
    CPPUNIT_ASSERT_EQUAL(1000, strength.getBoardStrength()) ;
}

void BoardStrengthTest::testThreeRedThreeYellow()
{
    // COlUMN 1 will have three reds.
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN6);// 
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN5);//
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN4);//

/*          *******
            *******
            *******
            R******
            R******
            R***YYY                     */

    GameState gameState;
    gameState.setGameState(*mpBoard);

    BoardStrength strength;
    strength.setTree(&gameState);

    VerticalSearch justForOutput;
    justForOutput.setGameState(&gameState);
    justForOutput.output();

    std::cout << "testThreeRedThreeYellow" << std::endl;
    CPPUNIT_ASSERT_EQUAL(0, strength.getBoardStrength()) ;
}

void BoardStrengthTest::testUpDiagonal()
{
    // Column 6 will have four YELLOWS
    mpBoard->addPiece(COLUMN0);// RED
    mpBoard->addPiece(COLUMN1);// YELLOW
    mpBoard->addPiece(COLUMN1);// RED

    mpBoard->addPiece(COLUMN2);// YELLOW
    mpBoard->addPiece(COLUMN2);// RED   
                                        
    mpBoard->addPiece(COLUMN3);// YELLOW

    mpBoard->addPiece(COLUMN2);// RED   

    mpBoard->addPiece(COLUMN3);// YELLOW
    mpBoard->addPiece(COLUMN3);// RED
    mpBoard->addPiece(COLUMN5);// YELLOW
    mpBoard->addPiece(COLUMN3);// RED        

/*
            *******
            *******
            ***R***
            **RR***
            *RRY***
            RYYY*Y*
*/
    GameState gameState;
    gameState.setGameState(*mpBoard);
    BoardStrength strength;
    strength.setTree(&gameState);

    CPPUNIT_ASSERT_EQUAL(WINNING_SCORE, strength.getBoardStrength()) ;
}

//  This test is very close to the one above only there are two winners.
//  Its an impoosible situation in real life but the code deals with it
//  as returning a board strength of 0 to indicate they are equal.
void BoardStrengthTest::testTwoWinners()
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

  //VerticalSearch justForOutput;
  //justForOutput.setGameState(gameState);
  //justForOutput.output();

    BoardStrength strength;
    strength.setTree(&gameState);

    CPPUNIT_ASSERT_EQUAL(0, strength.getBoardStrength()) ;
}
