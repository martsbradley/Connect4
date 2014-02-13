#ifndef BOARDTEST_H
#define BOARDTEST_H
#include <cppunit/extensions/HelperMacros.h>

class Board;

class BoardTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( BoardTest );
    CPPUNIT_TEST( testNextPiece );
    CPPUNIT_TEST( testGetPositionStatus );
    CPPUNIT_TEST( testNextTurnBasic );
    CPPUNIT_TEST( testNextTurnAdvanced );
    CPPUNIT_TEST( testEquals );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testNextPiece();
    void testGetPositionStatus();
    void testNextTurnBasic();
    void testNextTurnAdvanced();
    void testEquals();

private:
    Board* mpBoard;
};

#endif  // BOARDTEST_H
