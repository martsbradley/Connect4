#ifndef BOARDTEST_H
#define BOARDTEST_H
#include <cppunit/extensions/HelperMacros.h>

class Board;

class StrengthSearchTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( StrengthSearchTest );
    CPPUNIT_TEST( testFourEmptySquares );
    CPPUNIT_TEST( testFourRedSquares );
    CPPUNIT_TEST( testFourYellowSquares );
    CPPUNIT_TEST( testUpDiagonal );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testFourEmptySquares();
    void testFourRedSquares();
    void testFourYellowSquares();
    void testUpDiagonal();

private:
    Board* mpBoard;
};

#endif  // BOARDTEST_H
