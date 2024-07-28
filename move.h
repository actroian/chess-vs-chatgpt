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
    std::pair<int, int> rookstart;
    std::pair<int, int> rookend;
    bool isCastleMove;

    Move(std::pair<int, int> start, std::pair<int, int> end, char capturedPiece = '\0',std::pair<int, int> rookstart = std::make_pair(-1,-1), std::pair<int, int> rookend = std::make_pair(-1,-1), bool isCastleMove = false);
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~Move() {}
};

#endif
