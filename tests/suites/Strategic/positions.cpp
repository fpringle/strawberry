#include "positions.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "play.h"
#include "move.h"
#include "init.h"

bool test_position(std::string pos, std::vector<std::string> bms, int timeout) {
    chessCore::board b(pos);
    chessCore::Searcher searcher;
    chessCore::move_t comp_move = searcher.search(&b, timeout, false);
    std::string comp_move_san = b.SAN_pre_move(comp_move);

//    chessCore::Player player(pos);
//    chessCore::move_t comp_move = player.iterative_deepening(timeout);

//    std::string comp_move_san = player.SAN_pre_move(comp_move);

    if (std::find(bms.begin(), bms.end(), comp_move_san) != bms.end()) return true;
    std::cout << b;
    std::cout << "    Error: calculated move: " << comp_move_san << std::endl;
    if (bms.size()==1) {
        std::cout << "                 best move: " << bms[0] << std::endl;
    }
    else {
        std::cout << "                best moves: " << bms[0] << std::endl;
        for (unsigned int i=1; i<bms.size(); i++) {
            std::cout << "                            " << bms[i] << std::endl;
        }
    }
    return false;
}

int run_test_theme(int theme, int timeout) {
    std::cout << "Starting Nolot/" << theme_names[theme] << " test suite.\n"
              << "Using iterative deepening search with timeout: "
              << timeout << " seconds.\n";

    std::vector<std::string> fens = positions[theme];
    std::vector<std::vector<std::string>> moves = bestmoves[theme];

    int num_correct = 0;
    int num_total = fens.size();
    std::string pos;
    std::vector<std::string> bms;

    for (int i=0; i<num_total; i++) {
        pos = fens[i];
        bms = moves[i];
        std::cout << "  Searching position " << i + 1 << "...\n" << std::flush;
        if (test_position(pos, bms, timeout)) {
            std::cout << "    Position " << i + 1 << " success.\n";
            num_correct++;
        }
        else {
            std::cout << "    Position " << i + 1 << " failed.\n";
        }
    }

    std::cout << "\nTotal: " << num_correct << " passed, "
              << num_total - num_correct << " failed.\n";

    if (num_total == num_correct) return 0;
    else return 1;
}

int run_test_suite(int timeout) {
    int result = 0;
    int theme;
    for (theme=0; theme<15; theme++) {
        if (run_test_theme(theme, timeout)) {
            std::cout << "Nolot/" << theme_names[theme]
                      << " failed.\n\n";
            result = 1;
        }
        else {
            std::cout << "Nolot/" << theme_names[theme]
                      << " passed!\n\n";
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    chessCore::init();
    int timeout = 30;
    try {
        timeout = std::stoi(argv[1]);
    } catch(...) {}

    return run_test_suite(timeout);
}
