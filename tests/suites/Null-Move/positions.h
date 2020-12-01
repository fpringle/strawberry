#ifndef __NOLOT_POSITIONS_H
#define __NOLOT_POSITIONS_H

#include <string>
#include <vector>

const std::vector<std::string> positions = {
        "8/8/p1p5/1p5p/1P5p/8/PPP2K1p/4R1rk w - - 0 1",
        "1q1k4/2Rr4/8/2Q3K1/8/8/8/8 w - - 0 1",
        "7k/5K2/5P1p/3p4/6P1/3p4/8/8 w - - 0 1",
        "8/6B1/p5p1/Pp4kp/1P5r/5P1Q/4q1PK/8 w - - 0 32",
        "8/8/1p1r1k2/p1pPN1p1/P3KnP1/1P6/8/3R4 b - - 0 1"
};

const std::vector<std::vector<std::string>> bestmoves = {
        {"Rf1"},
        {"Kh6"},
        {"g5"},
        {"Qxh4"},
        {"Nxd5"}
};

bool test_position(std::string pos, std::vector<std::string> bms, int timeout);
int run_test_suite(int timeout);

#endif







