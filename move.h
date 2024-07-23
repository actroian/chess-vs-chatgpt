#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>
#include "board.h"
using namespace std;

class Move {
  protected:
    pair<int, int> start;
    pair<int, int> end;
    bool isWhiteAttacking;
    bool isCapturingMove;
    unique_ptr<Board>& board;

  public:
    Move(pair<int, int>, pair<int, int>, unique_ptr<Board>& board);
    pair<int, int> getStartPos();
    pair<int, int> getEndPos();
    pair<pair<int, int>, pair<int, int> > getMove();
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~Move() {}
};

#endif
