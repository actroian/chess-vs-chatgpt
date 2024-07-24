#include "L3.h"

L3::L3(bool isWhite) : L2{isWhite} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    // Implementation of choosing a move for L3
    return {{0, 0}, {0, 0}};
}

vector<Move> L3::checkmateMoves() {
    // Implementation of getting checkmate moves for L3
    return {};
}

vector<Move> L3::avoidCaptureMoves() {
    // Implementation of getting avoid capture moves for L3
    return {};
}
