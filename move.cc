#include "move.h"
#include "board.h"
using namespace std;

Move::Move(pair<int, int> start, pair<int, int> end, unique_ptr<Board>& board)
    : start(start), end(end), board(board){
        isWhiteAttacking = board->at(start.first, start.second)->isWhitePiece();
        isCapturingMove = board->at(end.first, end.second) == nullptr;
      }

pair<int, int> Move::getStartPos() {
    return make_pair(start.first, start.second);
}

pair<int, int> Move::getEndPos() {
    return make_pair(end.first, end.second);
}

pair<pair<int, int>, pair<int, int>> Move::getMove() {
    return make_pair(getStartPos(), getEndPos());
}

bool Move::operator==(const Move& other) const {
    return start == other.start &&
           end == other.end &&
           isWhiteAttacking == other.isWhiteAttacking &&
           isCapturingMove == other.isCapturingMove;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}