
/*
 * File:   movetestclass.cpp
 * Author: freddy
 *
 * Created on 09-Jun-2020, 09:10:00
 */

#include "movetestclass.h"
#include "board.h"
#include "move.h"
#include "init.h"
#include "twiddle.h"
#include <string>
#include <sstream>
#include "action.h"
#include <vector>
#include <algorithm>


using namespace chessCore;

CPPUNIT_TEST_SUITE_REGISTRATION(movetestclass);

movetestclass::movetestclass() { }

movetestclass::~movetestclass() { }

void movetestclass::setUp() { }

void movetestclass::tearDown() { }

void movetestclass::testItos() {
    int i, j;
    std::stringstream ss;
    std::stringstream ss2;
    char real[64][2];
    std::string real_string[64];
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            real[i * 8 + j][0] = 'a' + j;
            real[i * 8 + j][1] = '1' + i;
            real_string[i * 8 + j] = "  ";
            real_string[i * 8 + j][0] = 'a' + j;
            real_string[i * 8 + j][1] = '1' + i;
        }
    }

    char dest[2];
    std::string _string = "  ";

    for (i = 0; i < 64; i++) {
        ss << "wrong string at square ";
        ss << real[i][0] << real[i][1];
        itos(i, dest);
        _string = itos(i);
        itos(i, ss2);
        CPPUNIT_ASSERT_MESSAGE(ss.str(), dest[0] == real[i][0]);
        CPPUNIT_ASSERT_MESSAGE(ss.str(), dest[1] == real[i][1]);
        CPPUNIT_ASSERT_MESSAGE(ss.str(), _string == real_string[i]);
        CPPUNIT_ASSERT_MESSAGE(ss.str(), _string == ss2.str());
        ss.str("");
        ss2.str("");
    }
}

void movetestclass::testStoi() {
    int i, j;
    std::stringstream ss;
    char real[64][2];
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            real[i * 8 + j][0] = 'a' + j;
            real[i * 8 + j][1] = '1' + i;
        }
    }

    for (i = 0; i < 64; i++) {
        ss << "wrong index at square ";
        ss << real[i][0] << real[i][1];
        CPPUNIT_ASSERT_MESSAGE(ss.str(), _stoi(real[i]) == i);
        ss.str("");
    }
}

bool test_move(int from, int to, bool prom, bool cap, bool s1, bool s0) {
    move_t _move = make_move(from, to, prom, cap, s1, s0);
    bool _is_quiet = !(prom || cap || s1 || s0);
    int data = from + (to * (1ULL << 6)) + (cap * (1ULL << 12)) +
            (s0 * (1ULL << 13)) + (s1 * (1ULL << 14)) + (prom * (1ULL << 15));

    if (from_sq(_move) != from) return false;
    if (to_sq(_move) != to) return false;
    if (is_quiet(_move) != _is_quiet) return false;
    if (is_promotion(_move) != prom) return false;
    if (is_capture(_move) != cap) return false;
    if (is_ep_capture(_move) != (cap && s0)) return false;
    if (is_doublePP(_move) != (s0 && !(s1 || cap || prom))) return false;
    if (is_kingCastle(_move) != (s1 && !(s0 || cap || prom))) return false;
    if (is_queenCastle(_move) != (s1 && s0 && !(cap || prom))) return false;
    if (is_castle(_move) != (s1 && !(cap || prom))) return false;
    if (_move != data) return false;

    return true;
}

void movetestclass::testMove_t() {
    // normal capture
    CPPUNIT_ASSERT(test_move(10, 19, false, true, false, false));
    // promotion
    CPPUNIT_ASSERT(test_move(15, 7, true, false, false, false));
    // kingside castle
    CPPUNIT_ASSERT(test_move(4, 6, false, false, true, false));
    // queenside castle
    CPPUNIT_ASSERT(test_move(60, 57, false, false, true, true));
    // ep capture
    CPPUNIT_ASSERT(test_move(38, 45, false, true, false, true));
    // double pawn push
    CPPUNIT_ASSERT(test_move(50, 34, false, false, false, true));
}

void movetestclass::testOperatorPrint() {
    std::stringstream ss1, ss2;

    move_t move1 = make_move(10, 19, false, true, false, false);
    move_t move2 = make_move(15, 7, true, false, false, false);
    move_t move3 = make_move(4, 6, false, false, true, false);
    move_t move4 = make_move(60, 57, false, false, true, true);
    move_t move5 = make_move(38, 45, false, true, false, true);
    move_t move6 = make_move(50, 34, false, false, false, true);

    ss1     << move1 << std::endl
            << move2 << std::endl
            << move3 << std::endl
            << move4 << std::endl
            << move5 << std::endl
            << move6 << std::endl;

    ss2 << "c2d3\n"
        << "h2h1Q\n"
        << "e1g1\n"
        << "e8b8\n"
        << "g5f6\n"
        << "c7c5\n";

    CPPUNIT_ASSERT(ss1.str() == ss2.str());
}

void movetestclass::testInit_rays() {
    init_rays();

    CPPUNIT_ASSERT(rays[0][ 5] == 0x2020202020202000);
    CPPUNIT_ASSERT(rays[1][17] == 0x4020100804000000);
    CPPUNIT_ASSERT(rays[2][63] == 0x0000000000000000);
    CPPUNIT_ASSERT(rays[3][11] == 0x0000000000000010);
    CPPUNIT_ASSERT(rays[4][32] == 0x0000000001010101);
    CPPUNIT_ASSERT(rays[5][ 0] == 0x0000000000000000);
    CPPUNIT_ASSERT(rays[6][ 9] == 0x0000000000000100);
    CPPUNIT_ASSERT(rays[7][55] == 0x4000000000000000);

}

void movetestclass::testPawnPushNaive() {
    int sq = 19;
    bitboard blockers = (1ULL << 11) | (1ULL << 25) |
            (1ULL << 28) | (1ULL << 35) |
            (1ULL << 39) | (1ULL << 42) |
            (1ULL << 51) | (1ULL << 62);
    colour mc = white;
    bitboard bb_real = 0x0000000008000000;

    CPPUNIT_ASSERT(pawnPushNaive(sq, blockers, mc) == bb_real);
}

void movetestclass::testPawnAttackNaive() {
    int sq = 19;
    colour mc = white;
    bitboard bb_real = 0x0000000014000000;

    CPPUNIT_ASSERT(pawnAttackNaive(sq, mc) == bb_real);
}

void movetestclass::testPawnAttacks() {
    int sq = 19;
    colour mc = white;
    bitboard _white = (1ULL << 11) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62);

    bitboard _black = (1ULL << 25) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = 0x0000000010000000;

    CPPUNIT_ASSERT(pawnAttacks(sq, _white, _black, mc) == bb_real);
}

void movetestclass::testPawnTargets() {
    int sq = 19;
    colour mc = white;
    bitboard _white = (1ULL << 11) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62);

    bitboard _black = (1ULL << 25) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = 0x0000000018000000;

    CPPUNIT_ASSERT(pawnTargets(sq, _white, _black, mc) == bb_real);
}

void movetestclass::testKnightPushNaive() {
    int sq = 9;
    bitboard bb_real = (1ULL << 3) | (1ULL << 19) |
            (1ULL << 26) | (1ULL << 24);

    CPPUNIT_ASSERT(knightPushNaive(sq) == bb_real);
}

void movetestclass::testKnightTargets() {
    int sq = 9;
    colour mc = white;
    bitboard _white = (1ULL << 24) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62);

    bitboard _black = (1ULL << 26) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = (1ULL << 3) | (1ULL << 19) |
            (1ULL << 26);

    CPPUNIT_ASSERT(knightTargets(sq, _white, _black, mc) == bb_real);
}

void movetestclass::testKingPushNaive() {
    int sq = 19;
    bitboard bb_real = (1ULL << 27) | (1ULL << 11) |
            (1ULL << 20) | (1ULL << 18) |
            (1ULL << 28) | (1ULL << 10) |
            (1ULL << 26) | (1ULL << 12);

    CPPUNIT_ASSERT(kingPushNaive(sq) == bb_real);
}

void movetestclass::testKingTargets() {
    int sq = 19;
    colour mc = white;
    bitboard _white = (1ULL << 11) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62);

    bitboard _black = (1ULL << 25) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = (1ULL << 27) |
            (1ULL << 20) | (1ULL << 18) |
            (1ULL << 28) | (1ULL << 10) |
            (1ULL << 26) | (1ULL << 12);

    CPPUNIT_ASSERT(kingTargets(sq, _white, _black, mc) == bb_real);
}

void movetestclass::testBishopPushNaive() {
    int sq = 19;
    bitboard blockers = (1ULL << 11) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62) |
            (1ULL << 62) |
            (1ULL << 25) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = (1ULL << 1) | (1ULL << 10) |
            (1ULL << 12) | (1ULL << 5) |
            (1ULL << 28) | (1ULL << 26) |
            (1ULL << 33);

    CPPUNIT_ASSERT(bishopPushNaive(sq, blockers) == bb_real);
}

void movetestclass::testBishopTargets() {
    int sq = 19;
    colour mc = white;
    bitboard _white = (1ULL << 11) | (1ULL << 35) |
            (1ULL << 42) | (1ULL << 62) |
            (1ULL << 62);

    bitboard _black = (1ULL << 25) | (1ULL << 28) |
            (1ULL << 31) | (1ULL << 51);

    bitboard bb_real = (1ULL << 27) |
            (1ULL << 20) | (1ULL << 18) |
            (1ULL << 28) | (1ULL << 10) |
            (1ULL << 26) | (1ULL << 12);

    CPPUNIT_ASSERT(bishopTargets(sq, _white, _black, mc) == bb_real);
}

bool testGen(board b) {
    MoveList all_moves = b.gen_legal_moves();
    MoveList cap_moves = b.gen_captures();
    int j=0, i;

    MoveList all_vec;

    for (move_t move : all_moves) {
        if (is_capture(move)) {
            all_vec.push_back(move);
        }
    }
    if (all_vec.size() != cap_moves.size()) return false;

    std::sort(all_vec.begin(), all_vec.end());
    std::sort(cap_moves.begin(), cap_moves.end());

    return all_vec == cap_moves;
}

bool testGenPerft(board b, int depth) {
    if (! testGen(b)) {
        std::cout << b << b.FEN() << std::endl;
        return false;
    }
    if (depth == 0) return true;
    board child;
    MoveList moves = b.gen_legal_moves();
    for (move_t move : moves) {
        child = doMove(b, move);
        if (! testGenPerft(child, depth-1)) {
            return false;
        }
    }
    return true;
}

void movetestclass::testGenCaptures() {
/*
    board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/4P3/p1N2Q2/1PPBBPpP/R4K1R w kq - 0 0");
    std::cout << b;
    std::cout << testGen(b) << std::endl;
    return;
*/
    board b1;
    board b2("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");
    board b3("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    board b4("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    board b5("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    board b6("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");

    CPPUNIT_ASSERT(testGenPerft(b1, 4));
    std::cout << "Checked board 1 to depth 4, good\n";
    CPPUNIT_ASSERT(testGenPerft(b2, 3));
    std::cout << "Checked board 2 to depth 3, good\n";
    CPPUNIT_ASSERT(testGenPerft(b3, 4));
    std::cout << "Checked board 3 to depth 4, good\n";
    CPPUNIT_ASSERT(testGenPerft(b4, 4));
    std::cout << "Checked board 4 to depth 4, good\n";
    CPPUNIT_ASSERT(testGenPerft(b5, 3));
    std::cout << "Checked board 5 to depth 3, good\n";
    CPPUNIT_ASSERT(testGenPerft(b6, 3));
    std::cout << "Checked board 6 to depth 3, good\n";

}

bool perftSAN(board b, int depth) {
    if (depth == 0) return true;

    std::string san_pre, san_post;
    MoveList moves = b.gen_legal_moves();
    board child;

    for (move_t move : moves) {
        san_pre = b.SAN_pre_move(move);
        child = b;
        child.doMoveInPlace(move);
        san_post = child.SAN_post_move(move);
        if (san_pre != san_post) {
            std::cout << b << b.FEN() << std::endl
                      << "pre:  " << san_pre << std::endl
                      << "post: " << san_post << std::endl;
            return false;
        }
        if (! perftSAN(child, depth-1)) return false;
    }

    return true;
}

void movetestclass::testSANoutput() {
    init();
    board b1;
    board b2("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");
    board b3("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    board b4("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    board b5("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    board b6("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");

    CPPUNIT_ASSERT(perftSAN(b1, 5));
    std::cout << "Successful b1\n";
    CPPUNIT_ASSERT(perftSAN(b2, 5));
    std::cout << "Successful b2\n";
    CPPUNIT_ASSERT(perftSAN(b3, 5));
    std::cout << "Successful b3\n";
    CPPUNIT_ASSERT(perftSAN(b4, 5));
    std::cout << "Successful b4\n";
    CPPUNIT_ASSERT(perftSAN(b5, 5));
    std::cout << "Successful b5\n";
    CPPUNIT_ASSERT(perftSAN(b6, 5));
    std::cout << "Successful b6\n";
}

void testOneSANinput(board* b, move_t move) {
    std::string san = b->SAN_pre_move(move);
    move_t calcmove = b->move_from_SAN(san);
    std::string errormsg = "Correct move: " + mtos(move) +
                           ", calculated move: " + mtos(calcmove) +
                           ", correct SAN: " + san + '\n';
    std::stringstream ss;
    b->print_board(ss);
    errormsg += ss.str();
    CPPUNIT_ASSERT_EQUAL_MESSAGE(errormsg, move, calcmove);
}

void testSANperft(board* b, int depth) {
    if (depth == 0) return;
    board* child;
    MoveList moves  = b->gen_legal_moves();
    for (move_t move : moves) {
        testOneSANinput(b, move);
        child = doMove(b, move);
        testSANperft(child, depth - 1);
    }
}

void movetestclass::testSANinput() {
    board* pos2 = new board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");
    testSANperft(pos2, 4);

    board* pos3 = new board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    testSANperft(pos3, 3);

    board* pos4 = new board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    testSANperft(pos4, 4);

    board* pos5 = new board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    testSANperft(pos5, 4);
}
