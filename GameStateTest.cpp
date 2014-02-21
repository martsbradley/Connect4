#include "GameStateTest.h"
#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "TreeBuilder.h"

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

void GameStateTest::testArrayIndex()
{
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(0, 5));
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(0, 4));
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(0, 3));
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(0, 2));
    CPPUNIT_ASSERT_EQUAL(1, getByteIndex(0, 1));
    CPPUNIT_ASSERT_EQUAL(1, getByteIndex(0, 0));
    CPPUNIT_ASSERT_EQUAL(1, getByteIndex(1, 5));
}

void GameStateTest::testGetPosition()
{
    CPPUNIT_ASSERT_EQUAL(0, getPosition(0, 5));
    CPPUNIT_ASSERT_EQUAL(1, getPosition(0, 4));
    CPPUNIT_ASSERT_EQUAL(2, getPosition(0, 3));
    CPPUNIT_ASSERT_EQUAL(3, getPosition(0, 2));
    CPPUNIT_ASSERT_EQUAL(4, getPosition(0, 1));
    CPPUNIT_ASSERT_EQUAL(5, getPosition(0, 0));
    CPPUNIT_ASSERT_EQUAL(6, getPosition(1, 5));
    CPPUNIT_ASSERT_EQUAL(12, getPosition(2, 5));
    CPPUNIT_ASSERT_EQUAL(42, getPosition(7, 5));
}

void GameStateTest::testIntraCharIdx()
{
    CPPUNIT_ASSERT_EQUAL(0, getByteOffset(0, 5));
    CPPUNIT_ASSERT_EQUAL(1, getByteOffset(0, 4));
    CPPUNIT_ASSERT_EQUAL(2, getByteOffset(0, 3));
    CPPUNIT_ASSERT_EQUAL(3, getByteOffset(0, 2));
    CPPUNIT_ASSERT_EQUAL(0, getByteOffset(0, 1));
    CPPUNIT_ASSERT_EQUAL(1, getByteOffset(0, 0));
    CPPUNIT_ASSERT_EQUAL(2, getByteOffset(1, 5));
}

void GameStateTest::testPieceBits() 
{
    unsigned char piece = 0b01000000; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 5, RED));

    piece = 0b00010000; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 4, RED));

    piece = 0b00001100; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 3, YELLOW));

    piece = 0b00000011; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 2, YELLOW));

    piece = 0b11000000; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 1, YELLOW));

    piece = 0b00010000; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(0, 0, RED));

    piece = 0b00000100; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(1, 5, RED));

    piece = 0b00000011; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(1, 4, YELLOW));

    piece = 0b01000000; 
    CPPUNIT_ASSERT_EQUAL(piece, getPieceBits(1, 3, RED));
}
void GameStateTest::testByteOffset() 
{
    CPPUNIT_ASSERT_EQUAL(0, getByteOffset(0) );
    CPPUNIT_ASSERT_EQUAL(1, getByteOffset(1) );
    CPPUNIT_ASSERT_EQUAL(2, getByteOffset(2) );
    CPPUNIT_ASSERT_EQUAL(3, getByteOffset(3) );
    CPPUNIT_ASSERT_EQUAL(0, getByteOffset(4) );
    CPPUNIT_ASSERT_EQUAL(1, getByteOffset(5) );
    CPPUNIT_ASSERT_EQUAL(2, getByteOffset(6) );
    CPPUNIT_ASSERT_EQUAL(3, getByteOffset(7) );
    CPPUNIT_ASSERT_EQUAL(0, getByteOffset(8) );
}
void GameStateTest::testByteIndex() 
{
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(0) );
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(1) );
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(2) );
    CPPUNIT_ASSERT_EQUAL(0, getByteIndex(3) );
    CPPUNIT_ASSERT_EQUAL(1, getByteIndex(4) );
    CPPUNIT_ASSERT_EQUAL(10, getByteIndex(42) );
}

void GameStateTest::testSetValue()
{
    mpGameState->setValue(0,3, RED);
    mpGameState->setValue(0,2, RED);
    mpGameState->setValue(0,1, YELLOW);
    mpGameState->setValue(0,0, RED);
    CPPUNIT_ASSERT_EQUAL(EMPTY,  mpGameState->getValueAtPosition(0) );
    CPPUNIT_ASSERT_EQUAL(EMPTY,  mpGameState->getValueAtPosition(1) );
    CPPUNIT_ASSERT_EQUAL(RED,    mpGameState->getValueAtPosition(2) );
    CPPUNIT_ASSERT_EQUAL(RED,    mpGameState->getValueAtPosition(3) );
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpGameState->getValueAtPosition(4) );
    CPPUNIT_ASSERT_EQUAL(RED,    mpGameState->getValueAtPosition(5) );
    mpGameState->setValue(6,5, RED);
    mpGameState->setValue(6,4, YELLOW);
    mpGameState->setValue(6,3, RED);
    mpGameState->setValue(6,2, RED);
    mpGameState->setValue(6,1, YELLOW);
    mpGameState->setValue(6,0, EMPTY);// logically makes no sense but testing anyway

    CPPUNIT_ASSERT_EQUAL(RED,     mpGameState->getValueAtPosition(36) );
    CPPUNIT_ASSERT_EQUAL(YELLOW,  mpGameState->getValueAtPosition(37) );
    CPPUNIT_ASSERT_EQUAL(RED,     mpGameState->getValueAtPosition(38) );
    CPPUNIT_ASSERT_EQUAL(RED,     mpGameState->getValueAtPosition(39) );
    CPPUNIT_ASSERT_EQUAL(YELLOW,  mpGameState->getValueAtPosition(40) );
    CPPUNIT_ASSERT_EQUAL(EMPTY,   mpGameState->getValueAtPosition(41) );
}
void GameStateTest::testSetGameState()
{
    Board board;

    mpGameState->setGameState(board);

    for (int pos = 0; pos < 42; pos++ )
    {
        CPPUNIT_ASSERT_EQUAL(EMPTY,    mpGameState->getValueAtPosition(pos) );
    }

    mpGameState->setGameState(board);

    Board newboard;

    newboard.addPiece(COLUMN0);// RED
    newboard.addPiece(COLUMN0);// YELLOW
    newboard.addPiece(COLUMN1);// RED

    mpGameState->setGameState(newboard);

    for (int pos = 0; pos < 42; pos++ )
    {
        if (pos == 4)
            CPPUNIT_ASSERT_EQUAL(YELLOW,    mpGameState->getValueAtPosition(pos) );
        else if (pos == 5)
            CPPUNIT_ASSERT_EQUAL(RED,    mpGameState->getValueAtPosition(pos) );
        else if (pos == 11)
            CPPUNIT_ASSERT_EQUAL(RED,    mpGameState->getValueAtPosition(pos) );
        else
            CPPUNIT_ASSERT_EQUAL(EMPTY,    mpGameState->getValueAtPosition(pos) );
    }

    TreeBuilder tree;
    tree.buildTree(newboard);
}
