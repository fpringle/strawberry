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

unsigned int PERFT_pseud(Board b, int depth, bool print_progress = false) {
    unsigned int ret = 0;
    Board child;
    colour side;
    b.getSide(&side);

    if (depth == 0) {
        return 1;
    }

    MoveList moves = b.gen_moves();
    for (move_t move : moves) {
        child = doMove(b, move);
        if (child.is_check(side)) continue;
        ret += PERFT_pseud(child, depth - 1, false);
    }
    return ret;
}

unsigned int PERFT_legalcheck_faster(Board b, int depth, bool print_progress = false) {
    if (depth == 0) return 1;
    unsigned int ret = 0;
    Board child;
    colour side;
    b.getSide(&side);

    MoveList moves = b.gen_legal_moves();

    if (depth == 1) {
        return moves.size();
    }

    for (move_t move : moves) {
        child = doMove(b, move);
        ret += PERFT_legalcheck_faster(child, depth - 1, false);
    }
    return ret;
}

void testBoard(Board b, int depth, unsigned int* real) {
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
    Board _board;
    unsigned int real[] = {1, 20, 400, 8902, 197281,
                            4865609, 119060324};

    testBoard(_board, depth, real);
}

void perfttestclass::testPosition2() {
    int depth = 6;
    Board _board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");
    unsigned int real[] = {1, 48, 2039, 97862,
                           4085603, 193690690};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition3() {
    int depth = 6;
    Board _board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    unsigned int real[] = {1, 14, 191, 2812,
                            43238, 674624, 11030083,
                            178633661};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition4() {
    int depth = 6;
    Board _board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    unsigned int real[] = {1, 6, 264, 9467,
                           422333, 15833292};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition5() {
    int depth = 6;
    Board _board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    unsigned int real[] = {1, 44, 1486, 62379,
                           2103487, 89941194};

    testBoard(_board, depth, real);
}
void perfttestclass::testPosition6() {
    int depth = 6;
    Board _board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    unsigned int real[] = {1, 46, 2079, 89890,
                           3894594, 164075551};

    testBoard(_board, depth, real);
}

void divide_pseud(Board _board, int depth, unsigned int * cache) {
    bool print_progress = false;
    bool _print_moves = 0;
    bool _print_total = 0;
    MoveList moves = _board.gen_moves();
    int num_children;
    Board _child;
    int total = 0;
    colour side;
    _board.getSide(&side);
    int num_perft;

    for (move_t move : moves) {
        _child = doMove(_board, move);
        if (_child.is_check(side)) {
            continue;
        }
        num_perft = PERFT_pseud(_child, depth - 1, print_progress);
        if (_print_moves) {
            std::cout << mtos(move) << ": " << num_perft << std::endl;
        }
        if (!is_promotion(move)) {
            cache[ from_sq(move)*64 + to_sq(move) ] = num_perft;
        }
        else {
            int _ind = 4096;
            if (to_sq(move) / 8 == 0) {
                _ind += to_sq(move)*4;
            }
            else {
                _ind += 32 + (to_sq(move) % 8)*4;
            }
            switch (which_promotion(move)) {
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

bool divide_legal(Board _board, int depth, unsigned int * cache) {
    bool print_progress = false;
    bool _print_moves = 0;
    bool _print_total = 0;
    MoveList moves = _board.gen_legal_moves();
    //    int num_moves = _board.gen_moves( moves );
    //    if ( num_moves != num_legal ) return false;
    //    else {
    //        std::cout << num_legal << std::endl;
    //        std::cout << num_moves << std::endl;
    //    }
    int num_children;
    Board _child;
    int total = 0;
    colour side;
    _board.getSide(&side);
    int num_perft;

    for (move_t move : moves) {
        _child = doMove(_board, move);
        num_perft = PERFT_legalcheck_faster(_child, depth - 1, print_progress);
        if (_print_moves) {
            std::cout << move;
            std::cout << ": " << num_perft << std::endl;
        }
        if (!is_promotion(move)) {
            cache[ from_sq(move)*64 + to_sq(move) ] = num_perft;
        }
        else {
            //            std::cout << "                     adding a promotion";
            int _ind = 4096; // + to_sq(moves[i])*4;
            if (to_sq(move) / 8 == 0) {
                _ind += to_sq(move)*4;
            }
            else {
                _ind += 32 + (to_sq(move) % 8)*4;
            }
            switch (which_promotion(move)) {
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
    Board b;

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
        MoveList pseud = b.gen_moves();
        MoveList legal = b.gen_legal_moves();
        std::cout << "real num: " << pseud.size()
                  << ", our num: " << legal.size() << std::endl;
        int i;

        for (i = 0; i < std::max(pseud.size(), legal.size()); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::dividePos2() {
    init_rays();
    Board b("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 1 0");

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
        MoveList pseud = b.gen_moves();
        MoveList legal = b.gen_legal_moves();
        std::cout << "real num: " << pseud.size()
                  << ", our num: " << legal.size() << std::endl;
        int i;

        for (i = 0; i < std::max(pseud.size(), legal.size()); i++) {
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
    Board b("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");

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
        MoveList pseud = b.gen_moves();
        MoveList legal = b.gen_legal_moves();
        std::cout << "real num: " << pseud.size()
                  << ", our num: " << legal.size() << std::endl;
        int i;

        for (i = 0; i < std::max(pseud.size(), legal.size()); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::dividePos4() {
    init_rays();
    Board b("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

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
        MoveList pseud = b.gen_moves();
        MoveList legal = b.gen_legal_moves();
        std::cout << "real num: " << pseud.size()
                  << ", our num: " << legal.size() << std::endl;
        int i;

        for (i = 0; i < std::max(pseud.size(), legal.size()); i++) {
            std::cout << pseud[i];
            std::cout << "   ";
            std::cout << legal[i];
            std::cout << "\n";
        }
    }
}

void perfttestclass::pos3b4b1f4f3e2e3f3g2b1h1() {
    init_rays();
    Board b("8/2p5/3p4/KP5r/7k/4P3/6p1/7R b - - 1 1");
    b.print_board();
    MoveList pseud_moves = b.gen_moves();
    int _num_pseud = 0;
    MoveList legal_moves = b.gen_legal_moves();
    Board child;

    std::cout << "pseud:\n";
    for (move_t move : pseud_moves) {
        child = doMove(b, move);
        if (child.is_check(black)) continue;
        std::cout << "  ";
        std::cout << move;
        std::cout << std::endl;
        _num_pseud++;
    }
    std::cout << "    Total: " << _num_pseud;

    std::cout << "\n\nlegal:\n";
    for (move_t move : legal_moves) {
        std::cout << "  ";
        std::cout << move;
        std::cout << std::endl;
    }
    std::cout << "    Total: " << legal_moves.size();
}
