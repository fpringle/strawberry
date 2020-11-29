/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   perfttestclass.cpp
 * Author: pi
 *
 * Created on Jun 11, 2020, 9:26:46 AM
 */

#include "perfttestclass.h"
#include "board.h"
#include "move.h"
#include "action.h"

#include <time.h>

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace chessCore;

CPPUNIT_TEST_SUITE_REGISTRATION(perfttestclass);

perfttestclass::perfttestclass() { }

perfttestclass::~perfttestclass() { }

void perfttestclass::setUp() { }

void perfttestclass::tearDown() { }

unsigned int PERFT_pseud(board b, int depth, bool print_progress = false) {
    move_t movelist[256];
    int n_moves, i;
    unsigned int ret = 0;
    board child;
    colour side;
    b.getSide(&side);

    if (depth == 0) {
        return 1;
    }

    n_moves = b.gen_moves(movelist);
    for (i = 0; i < n_moves; i++) {
        child = doMove(b, movelist[i]);
        if (child.is_check(side)) continue;
        ret += PERFT_pseud(child, depth - 1, false);
        if (print_progress) std::cout << "pseud completed: " << i + 1 << " / " << n_moves << std::endl;
    }
    return ret;
}

unsigned int PERFT_legalcheck_faster(board b, int depth, bool print_progress = false) {
    if (depth == 0) return 1;
    move_t movelist[256];
    int n_moves;
    int i;
    unsigned int ret = 0;
    board child;
    colour side;
    b.getSide(&side);

    n_moves = b.gen_legal_moves(movelist);

    if (depth == 1) {
        return n_moves;
    }

    for (i = 0; i < n_moves; i++) {
        child = doMove(b, movelist[i]);
        ret += PERFT_legalcheck_faster(child, depth - 1, false);
        if (print_progress) std::cout << "legal completed: " << i + 1 << " / " << n_moves << std::endl;
    }
    return ret;
}

void testBoard(board b, int depth, unsigned int* real) {
    init_rays();
    unsigned int n_nodes;
    std::stringstream ss;
    clock_t start;
    double duration;

    for (int i = 0; i < depth; i++) {
//        if (i == depth - 1) {
            start = clock();
//        }
        n_nodes = PERFT_legalcheck_faster(b, i);
//        if (i == depth - 1) {
            duration = double(clock() - start) / double(CLOCKS_PER_SEC);
//        }
        ss << "Error checking PERFT result for depth " << i << ". ";
        ss << "Real answer: " << real[i] << std::endl;
        ss << "Our answer:  " << n_nodes << std::endl;
        ss << "(Did you remember to init_rays()?" << std::endl;
        CPPUNIT_ASSERT_MESSAGE(ss.str(), n_nodes == real[i]);
        ss.str("");
        std::cout << "Completed depth " << i << std::endl;
//        if (i == depth - 1) {
            std::cout << "    Time taken: " << duration << std::endl;
//        }
    }
}

void perfttestclass::testStartBoard() {
    int depth = 6;
    board _board;
    unsigned int real[] = {1, 20, 400, 8902, 197281,
                            4865609, 119060324};

    testBoard(_board, depth, real);
}

void perfttestclass::testPosition2() {
    int depth = 6;
    board _board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");
    unsigned int real[] = {1, 48, 2039, 97862,
                           4085603, 193690690};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition3() {
    int depth = 6;
    board _board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    unsigned int real[] = {1, 14, 191, 2812,
                            43238, 674624, 11030083,
                            178633661};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition4() {
    int depth = 6;
    board _board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    unsigned int real[] = {1, 6, 264, 9467,
                           422333, 15833292};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition5() {
    int depth = 6;
    board _board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    unsigned int real[] = {1, 44, 1486, 62379,
                           2103487, 89941194};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition6() {
    int depth = 6;
    board _board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    unsigned int real[] = {1, 46, 2079, 89890,
                           3894594, 164075551};

    testBoard(_board, depth, real);
}

void divide_pseud(board _board, int depth, unsigned int * cache) {
    bool print_progress = false;
    bool _print_moves = 0;
    bool _print_total = 0;
    move_t moves[256];
    int num_moves = _board.gen_moves(moves);
    int num_children;
    board _child;
    int total = 0;
    colour side;
    _board.getSide(&side);
    int num_perft;
    prettyMove pm;

    for (int i = 0; i < num_moves; i++) {
        _child = doMove(_board, moves[i]);
        if (_child.is_check(side)) {
            continue;
        }
        num_perft = PERFT_pseud(_child, depth - 1, print_progress);
        if (_print_moves) {
            pm.data = moves[i];
            std::cout << pm;
            std::cout << ": " << num_perft << std::endl;
        }
        if (!is_promotion(moves[i])) {
            cache[ from_sq(moves[i])*64 + to_sq(moves[i]) ] = num_perft;
        }
        else {
            int _ind = 4096;
            +to_sq(moves[i])*4;
            if (to_sq(moves[i]) / 8 == 0) {
                _ind += to_sq(moves[i])*4;
            }
            else {
                _ind += 32 + (to_sq(moves[i]) % 8)*4;
            }
            switch (which_promotion(moves[i])) {
                case queen:
                    _ind += 0;
                    break;
                case rook:
                    _ind += 1;
                    break;
                case bishop:
                    _ind += 2;
                    break;
                case knight:
                    _ind += 3;
                    break;
            }
            cache[ _ind ] = num_perft;
            //            std::cout << "promotion at square " << to_sq(moves[i]);
            //            std::cout << "    adding ";
            //            std::cout << moves[i];
            //            std::cout << " to pseud_cache at index " << _ind << std::endl;
        }
        total += num_perft;
    }

    if (_print_total || _print_moves) std::cout << "  Pseud total: " << total << std::endl << std::endl;
}

bool divide_legal(board _board, int depth, unsigned int * cache) {
    bool print_progress = false;
    bool _print_moves = 0;
    bool _print_total = 0;
    move_t moves[256];
    int num_legal = _board.gen_legal_moves(moves);
    //    int num_moves = _board.gen_moves( moves );
    //    if ( num_moves != num_legal ) return false;
    //    else {
    //        std::cout << num_legal << std::endl;
    //        std::cout << num_moves << std::endl;
    //    }
    int num_children;
    board _child;
    int total = 0;
    colour side;
    _board.getSide(&side);
    int num_perft;

    for (int i = 0; i < num_legal; i++) {
        _child = doMove(_board, moves[i]);
        num_perft = PERFT_legalcheck_faster(_child, depth - 1, print_progress);
        if (_print_moves) {
            std::cout << moves[i];
            std::cout << ": " << num_perft << std::endl;
        }
        if (!is_promotion(moves[i])) {
            cache[ from_sq(moves[i])*64 + to_sq(moves[i]) ] = num_perft;
        }
        else {
            //            std::cout << "                     adding a promotion";
            int _ind = 4096; // + to_sq(moves[i])*4;
            if (to_sq(moves[i]) / 8 == 0) {
                _ind += to_sq(moves[i])*4;
            }
            else {
                _ind += 32 + (to_sq(moves[i]) % 8)*4;
            }
            switch (which_promotion(moves[i])) {
                case queen:
                    _ind += 0;
                    break;
                case rook:
                    _ind += 1;
                    break;
                case bishop:
                    _ind += 2;
                    break;
                case knight:
                    _ind += 3;
                    break;
            }
            cache[ _ind ] = num_perft;
            //            std::cout << "promotion at square " << to_sq(moves[i]);
            //            std::cout << "    adding ";
            //            std::cout << moves[i];
            //            std::cout << " to legal_cache at index " << _ind << std::endl;
        }
        total += num_perft;
    }

    if (_print_total || _print_moves) std::cout << "  Legal total: " << total << std::endl << std::endl;
    return true;
}

void perfttestclass::divideStartboard() {
    init_rays();
    board b;

    move_t a2a3 = make_move(8, 16, 0, 0, 0, 0);
    move_t d7d5 = make_move(51, 35, 0, 0, 0, 1);
    move_t d1a4 = make_move(3, 24, 0, 0, 0, 0);
    b = doMove(b, a2a3);
    //    b = doMove( b, d7d5 );
    //    b = doMove( b, d1a4 );

    b.print_board();

    int i;
    unsigned int _max = std::numeric_limits<unsigned int>::max();
    unsigned int pseud_cache[4096];
    unsigned int legal_cache[4096];
    int from_square;
    int to_square;

    for (i = 0; i < 4096; i++) {
        pseud_cache[i] = _max;
        legal_cache[i] = _max;
    }

    divide_pseud(b, 2, pseud_cache);
    if (divide_legal(b, 2, legal_cache)) {

        std::cout << "move   pseud   legal\n";

        for (i = 0; i < 4096; i++) {
            if (legal_cache[i] != _max || pseud_cache[i] != _max) {
                from_square = i / 64;
                to_square = i % 64;
                itos(from_square, std::cout);
                std::cout << " ";
                itos(to_square, std::cout);
                std::cout << ":  ";
                std::cout << pseud_cache[i] << "   ";
                std::cout << legal_cache[i] << "    ";
                if (pseud_cache[i] != legal_cache[i]) {
                    std::cout << "ERROR";
                }
                std::cout << std::endl;
            }
        }
    }

    else {
        move_t pseud[256];
        move_t legal[256];
        int n_pseud = b.gen_moves(pseud);
        int n_legal = b.gen_legal_moves(legal);
        std::cout << "real num: " << n_pseud << ", our num: " << n_legal << std::endl;
        int i;

        for (i = 0; i < std::max(n_pseud, n_legal); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::dividePos2() {
    init_rays();
    board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");

    move_t e1f1 = make_move(4, 5, 0, 0, 0, 0);
    move_t b6c4 = make_move(41, 26, 0, 0, 0, 0);
    move_t e2d1 = make_move(12, 3, 0, 0, 0, 0);
    move_t c4e3 = make_move(26, 20, 0, 0, 0, 0);
    //    b = doMove( b, e1f1 );
    //    b = doMove( b, b6c4 );
    //    b = doMove( b, e2d1 );
    //    b = doMove( b, c4e3 );

    b.print_board();
    std::cout << "\n\n";

    int i;
    unsigned int _max = std::numeric_limits<unsigned int>::max();
    unsigned int pseud_cache[4096];
    unsigned int legal_cache[4096];
    int from_square;
    int to_square;

    for (i = 0; i < 4096; i++) {
        pseud_cache[i] = _max;
        legal_cache[i] = _max;
    }

    divide_pseud(b, 5, pseud_cache);
    if (divide_legal(b, 5, legal_cache)) {

        std::cout << "move   pseud   legal\n";

        for (i = 0; i < 4096; i++) {
            if (legal_cache[i] != _max || pseud_cache[i] != _max) {
                from_square = i / 64;
                to_square = i % 64;
                itos(from_square, std::cout);
                std::cout << " ";
                itos(to_square, std::cout);
                std::cout << ":  ";
                std::cout << pseud_cache[i] << "   ";
                std::cout << legal_cache[i] << "    ";
                if (pseud_cache[i] != legal_cache[i]) {
                    std::cout << "ERROR";
                }
                std::cout << std::endl;
            }
        }
    }

    else {
        move_t pseud[256];
        move_t legal[256];
        int n_pseud = b.gen_moves(pseud);
        int n_legal = b.gen_legal_moves(legal);
        std::cout << "real num: " << n_pseud << ", our num: " << n_legal << std::endl;
        int i;

        for (i = 0; i < std::max(n_pseud, n_legal); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::dividePos3() {
    int depth = 5;
    init_rays();
    board b("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");

    move_t b4b1 = make_move(25,  1, 0, 0, 0, 0);
    move_t f4f3 = make_move(29, 21, 0, 0, 0, 0);
    move_t a5b4 = make_move(32, 25, 0, 0, 0, 0);
    move_t c7c5 = make_move(50, 34, 0, 0, 0, 1);
    move_t b1h1 = make_move(1, 7, 0, 0, 0, 0);
    //    b = doMove( b, b4b1 );
    //    b = doMove( b, f4f3 );
    //    b = doMove( b, a5b4 );
    //    b = doMove( b, c7c5 );
    //    b = doMove( b, f3g2 );
    //    b = doMove( b, b1h1 );

    b.print_board();
    std::cout << "\n\n";

    int i;
    unsigned int _max = std::numeric_limits<unsigned int>::max();
    unsigned int pseud_cache[4160];
    unsigned int legal_cache[4160];
    int from_square;
    int to_square;

    for (i = 0; i < 4160; i++) {
        pseud_cache[i] = _max;
        legal_cache[i] = _max;
    }

    divide_pseud(b, depth, pseud_cache);
    //    if ( divide_legal( b, 2, legal_cache ) ) {
    divide_legal(b, depth, legal_cache);
    if (1) {

        std::cout << "move   pseud   legal\n";

        for (i = 0; i < 4160; i++) {
            if (legal_cache[i] != _max || pseud_cache[i] != _max) {
                if (i < 4096) {
                    from_square = i / 64;
                    to_square = i % 64;
                    std::cout << make_move(from_square, to_square, 0, 0, 0, 0);
                }
                else {
                    to_square = i - 4096;
                    if (to_square < 32) to_square = to_square / 4;
                    else to_square = ((to_square - 32) / 4) + 56;
                    int j = i % 4;
                    std::cout << make_move(0, to_square, 1, 0, j / 2, j % 2);
                }
                std::cout << "   ";
                std::cout << pseud_cache[i] << "   ";
                std::cout << legal_cache[i] << "    ";
                if (pseud_cache[i] != legal_cache[i]) {
                    std::cout << "ERROR";
                }
                std::cout << std::endl;
            }
        }
    }

    else {
        move_t pseud[256];
        move_t legal[256];
        int n_pseud = b.gen_moves(pseud);
        int n_legal = b.gen_legal_moves(legal);
        std::cout << "real num: " << n_pseud << ", our num: " << n_legal << std::endl;
        int i;

        for (i = 0; i < std::max(n_pseud, n_legal); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::dividePos4() {
    init_rays();
    board b("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

    move_t b4c5 = make_move(25, 34, 0, 0, 0, 0);
    move_t a3d3 = make_move(16, 19, 0, 0, 0, 0);
    move_t h2h3 = make_move(15, 23, 0, 0, 0, 0);
    move_t b6c5 = make_move(41, 34, 0, 1, 0, 0);
    //    b = doMove( b, b4c5 );
    //    b = doMove( b, a3d3 );
    //    b = doMove( b, h2h3 );
    //    b = doMove( b, b6c5 );

    b.print_all();
    std::cout << "\n\n";

    int i;
    unsigned int _max = std::numeric_limits<unsigned int>::max();
    unsigned int pseud_cache[4096];
    unsigned int legal_cache[4096];
    int from_square;
    int to_square;

    for (i = 0; i < 4096; i++) {
        pseud_cache[i] = _max;
        legal_cache[i] = _max;
    }

    divide_pseud(b, 4, pseud_cache);
    if (divide_legal(b, 4, legal_cache)) {

        std::cout << "move   pseud   legal\n";

        for (i = 0; i < 4096; i++) {
            if (legal_cache[i] != _max || pseud_cache[i] != _max) {
                from_square = i / 64;
                to_square = i % 64;
                itos(from_square, std::cout);
                std::cout << " ";
                itos(to_square, std::cout);
                std::cout << ":  ";
                std::cout << pseud_cache[i] << "   ";
                std::cout << legal_cache[i] << "    ";
                if (pseud_cache[i] != legal_cache[i]) {
                    std::cout << "ERROR";
                }
                std::cout << std::endl;
            }
        }
    }

    else {
        move_t pseud[256];
        move_t legal[256];
        int n_pseud = b.gen_moves(pseud);
        int n_legal = b.gen_legal_moves(legal);
        std::cout << "real num: " << n_pseud << ", our num: " << n_legal << std::endl;
        int i;

        for (i = 0; i < std::max(n_pseud, n_legal); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::pos3b4b1f4f3e2e3f3g2b1h1() {
    init_rays();
    board b("8/2p5/3p4/KP5r/7k/4P3/6p1/7R b - - 1 1");
    b.print_board();
    move_t pseud_moves[256];
    move_t legal_moves[256];
    int num_pseud = b.gen_moves(pseud_moves);
    int _num_pseud = 0;
    int num_legal = b.gen_legal_moves(legal_moves);
    board child;

    std::cout << "pseud:\n";
    for (int i = 0; i < num_pseud; i++) {
        child = doMove(b, pseud_moves[i]);
        if (child.is_check(black)) continue;
        std::cout << "  ";
        std::cout << pseud_moves[i];
        std::cout << std::endl;
        _num_pseud++;
    }
    std::cout << "    Total: " << _num_pseud;

    std::cout << "\n\nlegal:\n";
    for (int i = 0; i < num_legal; i++) {
        std::cout << "  ";
        std::cout << legal_moves[i];
        std::cout << std::endl;
    }
    std::cout << "    Total: " << num_legal;
}
