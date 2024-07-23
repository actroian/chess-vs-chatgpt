#include "move.h"
using namespace std;

Move::Move(pair<int, int> start, pair<int, int> end)
    : start{start}, end{end}{}

Move Move::getMove() const {
    return Move{start, end};
}

bool Move::operator==(const Move& other) const {
    return start == other.start && end == other.end;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}
