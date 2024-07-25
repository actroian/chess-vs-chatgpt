#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>

#include "piece.h"

class Move {
  public:
    std::pair<int, int> start;
    std::pair<int, int> end;
    char captured_piece;

    Move(std::pair<int, int>, std::pair<int, int>, char = '\0');
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~Move() {}
};

#endif
