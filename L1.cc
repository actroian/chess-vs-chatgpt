#include "L1.h"

L1::L1(bool isWhite) : Computer(isWhite) {}

bool L1::move(unique_ptr<Board>& b, const pair<int, int>& start, const pair<int, int>& end) {
    // Implementation of L1 move logic

    return false;
}

pair<pair<int, int>, pair<int, int>> L1::chooseMove() {
    // Implementation of choosing a move for L1
    return {{0, 0}, {0, 0}};
}

vector<pair<int, int>> L1::getAllMoves() {
    // Implementation of getting all moves for L1

    return {};
}