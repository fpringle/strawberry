
/*
 * File:   checktestclass.cpp
 * Author: freddy
 *
 * Created on 10-Jun-2020, 19:43:00
 */

#include "checktestclass.h"
#include "board.h"
#include "move.h"
#include "action.h"

using namespace chessCore;

CPPUNIT_TEST_SUITE_REGISTRATION(checktestclass);

checktestclass::checktestclass() { }

checktestclass::~checktestclass() { }

void checktestclass::setUp() { }

void checktestclass::tearDown() { }

void checktestclass::testIs_check() {
    init_rays();

    // board 1: black in checkmate, white nothing
    bitboard pb1[12] = {0x000000000040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0007000000000000,
        0x0000000001000000,
        0x0000000000000000,
        0x2000000000000000,
        0x0200000000000000,
        0x0400000000000000};

    bool castling1[] = {0, 0, 0, 0};
    board _board1(pb1, castling1, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in check in test 1", _board1.is_check(black));
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is not in check in test 1", !_board1.is_check(white));


    // board 2: black in check, white nothing
    bitboard pb2[12] = {0x000000000040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0007000000000000,
        0x0000000001000000,
        0x0000000000000000,
        0x2000000000000000,
        0x0000000000000000,
        0x0400000000000000};

    bool castling2[] = {0, 0, 0, 0};
    board _board2(pb2, castling2, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in check in test 2", _board2.is_check(black));
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is not in check in test 2", !_board2.is_check(white));


    // board 3: black in check, white in check
    bitboard pb3[12] = {0x000000004040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0005020000000000,
        0x0000000001000000,
        0x0000000000800000,
        0x2000000000000000,
        0x0200000000000000,
        0x0400000000000000};

    bool castling3[] = {0, 0, 0, 0};
    board _board3(pb3, castling3, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in check in test 3", _board3.is_check(black));
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is in check in test 3", _board3.is_check(white));


    // board 4: black in check, white in checkmate
    bitboard pb4[12] = {0x000000004040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0005020000000000,
        0x0000000001000000,
        0x0000000000800000,
        0x2000000000000000,
        0x0100000000000000,
        0x0400000000000000};

    bool castling4[] = {0, 0, 0, 0};
    board _board4(pb4, castling4, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in check in test 4", _board4.is_check(black));
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is in check in test 4", _board4.is_check(white));


    // board 5: black in check, white in checkmate - testing "no castling through/out of check"
    bitboard pb5[12] = {0x0000000000000000,
        0x0000000000000080,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000010,

        0x0000000000000000,
        0x0000002008000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000100000000000,
        0x8000000000000000};

    bool castling5[] = {1, 0, 0, 0};
    board _board5(pb5, castling5, 0, 0, 3, 3, white, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in check in test 5", _board5.is_check(black));
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is in check in test 5", _board5.is_check(white));

}

void checktestclass::testIs_checkmate() {
    init_rays();

    // board 1: black in checkmate, white nothing
    bitboard pb1[12] = {0x000000000040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0007000000000000,
        0x0000000001000000,
        0x0000000000000000,
        0x2000000000000000,
        0x0200000000000000,
        0x0400000000000000};

    bool castling1[] = {0, 0, 0, 0};
    board _board1(pb1, castling1, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is in checkmate in test 1", _board1.is_checkmate());
    _board1.set_side(white);
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is not in checkmate in test 1", !_board1.is_checkmate());


    // board 2: black in check, white nothing
    bitboard pb2[12] = {0x000000000040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0007000000000000,
        0x0000000001000000,
        0x0000000000000000,
        0x2000000000000000,
        0x0000000000000000,
        0x0400000000000000};

    bool castling2[] = {0, 0, 0, 0};
    board _board2(pb2, castling2, 0, 0, 3, 3, black, 200, 100);

    //    if ( _board2.is_checkmate( black ) ) {
    //        _board2.print_board();
    //    }
    //
    //    move_t c8b8 ( 58, 57, 0, 0, 0, 0 );
    //
    //    board child;
    //    child = doMove( _board2, c8b8 );
    //    std::cout << "CHILD\n";
    //    child.print_board();

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is not in checkmate in test 2", !_board2.is_checkmate());
    _board2.set_side(white);
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is not in checkmate in test 2", !_board2.is_checkmate());


    // board 3: black in check, white in check
    bitboard pb3[12] = {0x000000004040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0005020000000000,
        0x0000000001000000,
        0x0000000000800000,
        0x2000000000000000,
        0x0200000000000000,
        0x0400000000000000};

    bool castling3[] = {0, 0, 0, 0};
    board _board3(pb3, castling3, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is not in checkmate in test 3", !_board3.is_checkmate());
    _board3.set_side(white);
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is not in checkmate in test 3", !_board3.is_checkmate());


    // board 4: black in check, white in checkmate
    bitboard pb4[12] = {0x000000004040a000,
        0x0000000000000020,
        0x0000000000000000,
        0x0000002000000000,
        0x0000000000000008,
        0x0000000000000040,

        0x0005020000000000,
        0x0000000001000000,
        0x0000000000800000,
        0x2000000000000000,
        0x0100000000000000,
        0x0400000000000000};

    bool castling4[] = {0, 0, 0, 0};
    board _board4(pb4, castling4, 0, 0, 3, 3, black, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is not in checkmate in test 4", !_board4.is_checkmate());
    _board4.set_side(white);
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is in checkmate in test 4", _board4.is_checkmate());


    // board 5: black in check, white in checkmate - testing "no castling through/out of check"
    bitboard pb5[12] = {0x0000000000000000,
        0x0000000000000080,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000010,

        0x0000000000000000,
        0x0000002008000000,
        0x0000000000000000,
        0x0000000000000000,
        0x0000100000000000,
        0x8000000000000000};

    bool castling5[] = {1, 0, 0, 0};
    board _board5(pb5, castling5, 0, 0, 3, 3, white, 200, 100);

    CPPUNIT_ASSERT_MESSAGE("failed to recognise that white is in checkmate in test 5", _board5.is_checkmate());
    _board5.set_side(black);
    CPPUNIT_ASSERT_MESSAGE("failed to recognise that black is not in checkmate in test 5", !_board5.is_checkmate());

}

bool perft_lastmove_check(board* b, int depth) {
    if (depth == 0) return true;
    MoveList moves = b->gen_legal_moves();
    board* child;
    colour side;
    bool lastmove_check, in_check;
    for (move_t move : moves) {
        child = doMove(b, move);
        child->getSide(&side);
        lastmove_check = child->was_lastmove_check(move);
        in_check = child->is_check(side);
        if (lastmove_check ^ in_check) {
            std::cout << *b << b->FEN() << std::endl << *child
                      << b->SAN_pre_move(move) << std::endl;
            std::cout << "Check: " << (in_check ? "true\n" : "false\n");
            std::cout << "Was lastmove check: " << (lastmove_check ? "true\n" : "false\n");
            return false;
        }
        if (! perft_lastmove_check(child, depth-1)) return false;
    }
    return true;
}

void test_lastmove_check(board* b, int depth) {
    CPPUNIT_ASSERT(perft_lastmove_check(b,depth));
}

void checktestclass::testCheck_lastmove_pos3() {
    init_rays();
    board* pos3 = new board("8/2p5/3p4/KP5r/1R2ppk1/8/4P1P1/8 b - - 0 0");
    test_lastmove_check(pos3, 5);
}

void checktestclass::testCheck_lastmove_pos4() {
    init_rays();
    board* pos4 = new board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    test_lastmove_check(pos4, 5);
}

void checktestclass::testCheck_lastmove_pos5() {
    init_rays();
    board* pos5 = new board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    test_lastmove_check(pos5, 5);
}

bool perft_checking_move(board* b, int depth) {
    if (depth == 0) return true;
    MoveList moves = b->gen_legal_moves();
    board* child;
    colour side;
    bool checking, in_check;
    for (move_t move : moves) {
        child = doMove(b, move);
        child->getSide(&side);
        checking = b->is_checking_move(move);
        in_check = child->is_check(side);
        if (checking ^ in_check) {
            std::cout << *b << b->FEN() << std::endl << *child
                      << b->SAN_pre_move(move) << std::endl;
            std::cout << "Check: " << (in_check ? "true\n" : "false\n");
            std::cout << "Is checking move: " << (checking ? "true\n" : "false\n");
            return false;
        }
        if (! perft_lastmove_check(child, depth-1)) return false;
    }
    return true;
}

void test_checking_move(board* b, int depth) {
    CPPUNIT_ASSERT(perft_checking_move(b,depth));
}

void checktestclass::testChecking_move_pos3() {
    init_rays();
    board* pos3 = new board("8/2p5/3p4/KP5r/1R2ppk1/8/4P1P1/8 b - - 0 0");
    test_checking_move(pos3, 5);
}

void checktestclass::testChecking_move_pos4() {
    init_rays();
    board* pos4 = new board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    test_checking_move(pos4, 5);
}

void checktestclass::testChecking_move_pos5() {
    init_rays();
    board* pos5 = new board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    test_checking_move(pos5, 5);
}
