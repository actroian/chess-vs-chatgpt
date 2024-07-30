#include "move.h"
#include "board.h"
using namespace std;

Move::Move(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece)
    : start(start), end(end), captured_piece(captured_piece) {}

Move::~Move() {}

bool Move::operator==(const Move& other) const {
    return start == other.start && end == other.end && captured_piece == other.captured_piece;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}
