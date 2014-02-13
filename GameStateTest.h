#ifndef GAMESTATETEST_H
#define GAMESTATETEST_H
#include <cppunit/extensions/HelperMacros.h>
#include "TreeBuilder.h"


class GameStateTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( GameStateTest );
    CPPUNIT_TEST( testSetGameState );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testSetGameState();

private:
    GameState* mpGameState;
};

#endif  // GAMESTATETEST_H
