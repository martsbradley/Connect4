#include "BoardStrengthTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <vector>
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
    CPPUNIT_ASSERT_EQUAL(1100, strength.getBoardStrength()) ;

  // For red
  //Vertical      600 300 100  -> 1000
  //Horizontal    100 100 100  ->  300
  //UpDiagonal    100 100 100  ->  300
  //Down Diagonal   0   0   0 
  // Total                        1600


  // For yellow
  //Vertical      100 100 100  ->  300
  //Horizontal    100 300 600  -> 1000
  //UpDiagonal      0   0   0  ->    0
  //Down Diagonal 100 100 100  ->  300      
  //                              1600

  //  Appears to me this board should give a score that draws
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

    CPPUNIT_ASSERT_EQUAL(1000700, strength.getBoardStrength()) ;
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


    VerticalSearch justForOutput;
    justForOutput.setGameState(&gameState);
    justForOutput.output();


    BoardStrength strength;
    strength.setTree(&gameState);

    CPPUNIT_ASSERT_EQUAL(0, strength.getBoardStrength()) ;


    //  This test illustrates that the logic of the board class is wrong.
    //  It should know enough to prevent further this state beign reached.
}
void BoardStrengthTest::testNonWin()
{
    mpBoard->addPiece((enum ColumnName) 3);
    mpBoard->addPiece((enum ColumnName) 3);
    mpBoard->addPiece((enum ColumnName) 1);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 5);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 1);
    mpBoard->addPiece((enum ColumnName) 3);
    mpBoard->addPiece((enum ColumnName) 1);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 0);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 2);
    mpBoard->addPiece((enum ColumnName) 3);
    mpBoard->addPiece((enum ColumnName) 0);
    mpBoard->addPiece((enum ColumnName) 1);
    mpBoard->addPiece((enum ColumnName) 1);
    mpBoard->addPiece((enum ColumnName) 0);
    mpBoard->addPiece((enum ColumnName) 0);
    mpBoard->addPiece((enum ColumnName) 5);

    GameState gameState;
    gameState.setGameState(*mpBoard);

    gameState.output();

    BoardStrength strength;
    strength.setTree(&gameState);

    std::cout << "Strength is " << strength.getBoardStrength() << std::endl;
    // CPPUNIT_ASSERT_EQUAL(0, strength.getBoardStrength()) ;

}

#include "ScoreVisitor.h"

void BoardStrengthTest::testNonWin2()
{
    mpBoard->addPiece((enum ColumnName)2);  //Me
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)2);  //Me
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)5);  //Me
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)2);  //Me
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)4);  //Me
    mpBoard->addPiece((enum ColumnName)5);
    mpBoard->addPiece((enum ColumnName)4);  //Me
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)2);  //Me

//    GameState gameState;
//    gameState.setGameState(*mpBoard);
//    gameState.output();

    TreeBuilder tree;
    tree.buildTree(*mpBoard);

    ScoreVisitor visitor;
    GameState* pState = tree.getTree();
    pState->accept(visitor);




    std::vector<GameState*>& nextStates = pState->getNextStates();

    std::cout  << std::endl;
    int columnx = 0;

    for (std::vector<GameState*>::iterator it = nextStates.begin();
         it != nextStates.end();
         ++it)
    {
    	BoardStrength strength;
    	strength.setTree(*it);
    	std::cout << "Column: " << columnx++ << " score: "<< strength.getBoardStrength() << std::endl;
    	(*it)->output();
    }



    int columnId = visitor.getBestCol();
    enum ColumnName column = (enum ColumnName)columnId;
   //"Yellow would move to column 2 to avoid loosing.
    CPPUNIT_ASSERT_EQUAL(2, columnId) ;
}


void BoardStrengthTest::testNonWin3()
{
	mpBoard->addPiece((enum ColumnName) 3); //Me
	mpBoard->addPiece((enum ColumnName) 3);
	mpBoard->addPiece((enum ColumnName) 5); //Me
	mpBoard->addPiece((enum ColumnName) 4);
	mpBoard->addPiece((enum ColumnName) 3); //Me
	mpBoard->addPiece((enum ColumnName) 4);
	mpBoard->addPiece((enum ColumnName) 5); //Me
	mpBoard->addPiece((enum ColumnName) 5);
	mpBoard->addPiece((enum ColumnName) 3); //Me
	mpBoard->addPiece((enum ColumnName) 4);
	mpBoard->addPiece((enum ColumnName) 4); //Me
	mpBoard->addPiece((enum ColumnName) 5);
	mpBoard->addPiece((enum ColumnName) 2); //Me
	mpBoard->addPiece((enum ColumnName) 5);
	mpBoard->addPiece((enum ColumnName) 5); //Me
	mpBoard->addPiece((enum ColumnName) 1);
	mpBoard->addPiece((enum ColumnName) 4); //Me
	mpBoard->addPiece((enum ColumnName) 1);
	mpBoard->addPiece((enum ColumnName) 1); //Me
	TreeBuilder tree;
	tree.buildTree(*mpBoard);

	ScoreVisitor visitor;
	GameState* pState = tree.getTree();
	pState->accept(visitor);
	//std::cout << "Game over?" << visitor.isGameOver() << std::endl;
	std::cout << "Moving to " << visitor.getBestCol() << std::endl;
}
void BoardStrengthTest::testNonWin4()
{
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)3);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)0);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)2);
    mpBoard->addPiece((enum ColumnName)3);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)1);
    mpBoard->addPiece((enum ColumnName)4);
    mpBoard->addPiece((enum ColumnName)0);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)5);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)6);
    mpBoard->addPiece((enum ColumnName)5);
    mpBoard->addPiece((enum ColumnName)5);

	TreeBuilder tree;
	tree.buildTree(*mpBoard);

	ScoreVisitor visitor;
	GameState* pState = tree.getTree();
	pState->accept(visitor);
//	std::cout << "Game over?" << visitor.isGameOver() << std::endl;
	std::cout << "Moving to " << visitor.getBestCol() << std::endl;
}
