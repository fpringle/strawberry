

/*
 * File:   checktestclass.h
 * Author: freddy
 *
 * Created on 08-Jun-2020, 20:21:02
 */

#ifndef CHECKTESTCLASS_H
#define CHECKTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class checktestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(checktestclass);

//    CPPUNIT_TEST(testIs_check);
//    CPPUNIT_TEST(testIs_checkmate);
//    CPPUNIT_TEST(testCheck_lastmove_pos3);
//    CPPUNIT_TEST(testCheck_lastmove_pos4);
//    CPPUNIT_TEST(testCheck_lastmove_pos5);

    CPPUNIT_TEST(testChecking_move_pos3);
//    CPPUNIT_TEST(testChecking_move_pos4);
    CPPUNIT_TEST(testChecking_move_pos5);

    CPPUNIT_TEST_SUITE_END();

public:
    checktestclass();
    virtual ~checktestclass();
    void setUp();
    void tearDown();

private:
    void testIs_check();
    void testIs_checkmate();
    void testCheck_lastmove_pos3();
    void testCheck_lastmove_pos4();
    void testCheck_lastmove_pos5();
    void testChecking_move_pos3();
    void testChecking_move_pos4();
    void testChecking_move_pos5();

};

#endif /* CHECKTESTCLASS_H */

