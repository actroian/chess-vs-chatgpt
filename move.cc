#include "move.h"
using namespace std;

Move::Move(pair<int, int> start, pair<int, int> end, char captured_piece, pair<int, int> rookstart, pair<int, int> rookend, bool isCastleMove)
    : start{start}, end{end}, captured_piece{captured_piece}, rookstart{rookstart}, rookend{rookend}, isCastleMove{isCastleMove} {}

bool Move::operator==(const Move& other) const {
    return start == other.start && end == other.end;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}
