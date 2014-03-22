#ifndef GAMESTATETEST_H
#define GAMESTATETEST_H
#include <cppunit/extensions/HelperMacros.h>
#include "TreeBuilder.h"


class GameStateTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( GameStateTest );
    CPPUNIT_TEST( testGetPosition );
    CPPUNIT_TEST( testArrayIndex );
    CPPUNIT_TEST( testIntraCharIdx );
    CPPUNIT_TEST( testPieceBits );
    CPPUNIT_TEST( testByteOffset );
    CPPUNIT_TEST( testByteIndex );
    CPPUNIT_TEST( testSetValue );
    CPPUNIT_TEST( testSetGameState );
    CPPUNIT_TEST( testColumnHeightsEmpty );
    CPPUNIT_TEST( testColumnHeightsAcending );
    CPPUNIT_TEST( testColumnHeightsFullColumn );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testGetPosition();
    void testArrayIndex();
    void testIntraCharIdx();
    void testPieceBits();
    void testByteOffset();
    void testByteIndex();
    void testSetValue();
    void testSetGameState();
    void testColumnHeightsEmpty();
    void testColumnHeightsAcending();
    void testColumnHeightsFullColumn();

private:
    GameState* mpGameState;
};

#endif  // GAMESTATETEST_H
