#include "GameStateTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( GameStateTest );


void GameStateTest::setUp()
{
    mpGameState = new GameState();
}


void GameStateTest::tearDown()
{
    delete mpGameState;
    mpGameState = 0;
}


void GameStateTest::testSetGameState()
{
    //CPPUNIT_ASSERT_EQUAL(1,2);
}

