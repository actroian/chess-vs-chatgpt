#include "L1.h"

L1::L1(bool isWhite) : Player{isWhite} {}

Move L1::chooseMove(unique_ptr<Board>& b) {
    // Implementation of choosing a move for L1
    return {{0, 0}, {0, 0}};
}

vector<Move> L1::getAllMoves() {
    // Implementation of getting all moves for L1

    return {};
}
