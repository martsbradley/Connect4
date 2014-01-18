#include "BoardTest.h"
#include "Board.h"
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( BoardTest );


void BoardTest::setUp()
{
    mpBoard = new Board();
}


void BoardTest::tearDown()
{
    delete mpBoard;
}


void BoardTest::testColumnOneFull()
{
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN0);

    try {
        mpBoard->addPeice(RED, COLUMN0);
        CPPUNIT_FAIL( "Should have failed, too many pieces in column" );
    }
    catch (std::logic_error e) {
    }
}

void BoardTest::testGetPositionStatus() {
    mpBoard->addPeice(RED, COLUMN0);
    mpBoard->addPeice(RED, COLUMN1);
    mpBoard->addPeice(RED, COLUMN2);
    mpBoard->addPeice(RED, COLUMN3);
    mpBoard->addPeice(RED, COLUMN4);

    mpBoard->addPeice(YELLOW, COLUMN0);
    mpBoard->addPeice(YELLOW, COLUMN1);
    mpBoard->addPeice(YELLOW, COLUMN2);
    mpBoard->addPeice(YELLOW, COLUMN3);
    mpBoard->addPeice(YELLOW, COLUMN4);

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN0,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN0,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN1,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN1,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN2,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN2,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN3,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN3,1));

    CPPUNIT_ASSERT_EQUAL(RED,    mpBoard->getPositionStatus(COLUMN4,0));
    CPPUNIT_ASSERT_EQUAL(YELLOW, mpBoard->getPositionStatus(COLUMN4,1));
}
