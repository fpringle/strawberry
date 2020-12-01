#ifndef __NOLOT_POSITIONS_H
#define __NOLOT_POSITIONS_H

#include <string>
#include <vector>

const std::vector<std::string> positions = {
        "r3qb1k/1b4p1/p2pr2p/3n4/Pnp1N1N1/6RP/1B3PP1/1B1QR1K1 w - -",
        "r4rk1/pp1n1p1p/1nqP2p1/2b1P1B1/4NQ2/1B3P2/PP2K2P/2R5 w - -",
        "r2qk2r/ppp1b1pp/2n1p3/3pP1n1/3P2b1/2PB1NN1/PP4PP/R1BQK2R w KQkq -",
        "r1b1kb1r/1p1n1ppp/p2ppn2/6BB/2qNP3/2N5/PPP2PPP/R2Q1RK1 w kq -",
        "r2qrb1k/1p1b2p1/p2ppn1p/8/3NP3/1BN5/PPP3QP/1K3RR1 w - -",
        "rnbqk2r/1p3ppp/p7/1NpPp3/QPP1P1n1/P4N2/4KbPP/R1B2B1R b kq -",
        "1r1bk2r/2R2ppp/p3p3/1b2P2q/4QP2/4N3/1B4PP/3R2K1 w k -",
        "r3rbk1/ppq2ppp/2b1pB2/8/6Q1/1P1B3P/P1P2PP1/R2R2K1 w - -",
        "r4r1k/4bppb/2n1p2p/p1n1P3/1p1p1BNP/3P1NP1/qP2QPB1/2RR2K1 w - -",
        "r1b2rk1/1p1nbppp/pq1p4/3B4/P2NP3/2N1p3/1PP3PP/R2Q1R1K w - -",
        "r1b3k1/p2p1nP1/2pqr1Rp/1p2p2P/2B1PnQ1/1P6/P1PP4/1K4R1 w - -"
};

const std::vector<std::vector<std::string>> bestmoves = {
        {"Nxh6"},
        {"Rxc5"},
        {"Nxg5"},
        {"Nxe6"},
        {"e5"},
        {"axb5"},
        {"Rxd8+"},
        {"Bxh7+"},
        {"Ng5"},
        {"Rxf7"},
        {"Rxh6"}
};

bool test_position(std::string pos, std::vector<std::string> bms, int timeout);
int run_test_suite(int timeout);

#endif
