#ifndef BOARDTEST_H
#define BOARDTEST_H
#include <cppunit/extensions/HelperMacros.h>

class Board;

class BoardTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( BoardTest );
    CPPUNIT_TEST( testColumnOneFull );
    CPPUNIT_TEST( testGetPositionStatus );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testColumnOneFull();
    void testGetPositionStatus();
private:
    Board* mpBoard;
};

#endif  // BOARDTEST_H
