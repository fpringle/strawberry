
/*
 * File:   searchtestclass.cpp
 * Author: pi
 *
 * Created on Jun 30, 2020, 10:25:04 PM
 */

#include "searchtestclass.h"
#include "board.h"
#include "move.h"
#include "action.h"
#include "init.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace chessCore;

CPPUNIT_TEST_SUITE_REGISTRATION(searchtestclass);

searchtestclass::searchtestclass() { }

searchtestclass::~searchtestclass() { }

void searchtestclass::setUp() { }

void searchtestclass::tearDown() { }

int map_move(move_t move) {
    uint16_t from_square = from_sq(move);
    uint16_t to_square = to_sq(move);
    if (!is_promotion(move)) {
        return from_square * 64 + to_square;
    }
    else {
        int _ind = 4096;
        if (to_square / 8 == 0) {
            _ind += to_square * 4;
        }
        else {
            _ind += 32 + (to_square % 8) * 4;
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

        return _ind;
    }
}

std::string unmap_move(int num) {
    std::stringstream ss;
    int a = num / 64;
    int b = num % 64;
    //    std::cout << a << " " << b << " " ;
    ss << itos(a) << itos(b);
    //    std::cout << ss.str() << std::endl;
    return ss.str();
}

std::string unmap_moveset(uint64_t num) {
    std::stringstream ss;
    uint64_t x = num;
    while (x > 0) {
        //        std::cout << x%4160 << std::endl;
        ss << unmap_move(int(x % 4160)) << " ";
        x /= 4160;
    }

    return ss.str();
}

void search_tree(Board b, uint64_t ** dest, int32_t ** score, int depth, uint64_t moves_so_far = 0) {
    // size of dest == num
    if (depth == 0) {
        **dest = moves_so_far;
        (*dest)++;

        **score = b.getValue();
        (*score)++;
        //        std::cout << moves_so_far << ": " << unmap_move(moves_so_far) << std::endl;
    }

    else {
        moves_so_far *= 4160;
        Board child;
        MoveList moves = b.gen_legal_moves();
        uint64_t new_moveset;

        for (move_t move : moves) {
            child = doMove(b, move);
            new_moveset = moves_so_far + map_move(move);
            search_tree(child, dest, score, depth - 1, new_moveset);
        }
    }
}

void tree_file(Board b, int depth, int * expected, std::string suffix) {
    init_rays();
    int num = expected[ depth - 1 ];
    uint64_t * dest = new uint64_t[num];
    int32_t * score = new int32_t[num];
    std::string filename;

    for (int i = 1; i <= depth; i++) {
        num = expected[i - 1];
        filename = suffix + "_" + std::to_string(i) + ".txt";
        std::ofstream fil(filename);
        search_tree(b, &dest, &score, i);
        dest -= num;
        score -= num;
        for (int j = 0; j < num; j++) {
            fil << unmap_moveset(dest[j]) << ": ";
            fil << score[j] << std::endl;
        }
        fil.close();
    }
}

void searchtestclass::testSearch_tree() {
    Board b;
    int exp[] = {20, 400, 8902, 197281};
    std::string suff = "startpos";
    tree_file(b, 4, exp, suff);
}

void searchtestclass::testUnmap() {
    uint64_t x = 1550483193856;
    std::cout << x << std::endl;
    std::cout << x % 4160;
    std::cout << unmap_moveset(x) << std::endl;
}
