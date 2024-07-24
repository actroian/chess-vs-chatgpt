#include "L2.h"

L2::L2(bool isWhite) : L1{isWhite} {}

Move L2::chooseMove(unique_ptr<Board>& b) {
    // Implementation of choosing a move for L2
    return {{0, 0}, {0, 0}};
}

vector<Move> L2::captureMoves() {
    // Implementation of getting capture moves for L2
    return {};
}

vector<Move> L2::checkMoves() {
    // Implementation of getting check moves for L2
    return {};
}