#include "move.h"
#include "board.h"
using namespace std;

Move::Move(int startrow, int startcol, int endrow, int endcol, unique_ptr<Board>& board)
    : startrow(startrow), startcol(startcol), endrow(endrow), endcol(endcol), board(board){
        isWhiteAttacking = board->at(startrow, startcol)->isWhitePiece();
        isCapturingMove = board->at(endrow, endcol) == nullptr;
      }

pair<int, int> Move::getStartPos() {
    return make_pair(startrow, startcol);
}

pair<int, int> Move::getEndPos() {
    return make_pair(endrow, endcol);
}

pair<pair<int, int>, pair<int, int>> Move::getMove() {
    return make_pair(getStartPos(), getEndPos());
}

bool Move::operator==(const Move& other) const {
    return startrow == other.startrow &&
           startcol == other.startcol &&
           endrow == other.endrow &&
           endcol == other.endcol &&
           isWhiteAttacking == other.isWhiteAttacking &&
           isCapturingMove == other.isCapturingMove;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}