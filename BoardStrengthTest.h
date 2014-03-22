#ifndef BOARDTEST_H
#define BOARDTEST_H
#include <cppunit/extensions/HelperMacros.h>

class Board;

class BoardStrengthTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( BoardStrengthTest );

	//CPPUNIT_TEST( testEmptyBoard );
	//CPPUNIT_TEST( testFourRedSquares );
	//CPPUNIT_TEST( testThreeRedSquares );
	//CPPUNIT_TEST( testThreeRedThreeYellow );
	//CPPUNIT_TEST( testUpDiagonal );
	//CPPUNIT_TEST( testTwoWinners );
	//CPPUNIT_TEST( testNonWin );
	//CPPUNIT_TEST( testNonWin2 );
     CPPUNIT_TEST( testNonWin3 );
     CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testEmptyBoard();
    void testFourRedSquares();
    void testThreeRedSquares();
    void testThreeRedThreeYellow();
    void testUpDiagonal();
    void testTwoWinners();
    void testNonWin();
    void testNonWin2();
    void testNonWin3();
private:
    Board* mpBoard;
};

#endif  // BOARDTEST_H
