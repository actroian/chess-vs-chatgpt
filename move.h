#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>
#include "board.h"
using namespace std;

class Move {
  protected:
    int startrow;
    int startcol;
    int endrow;
    int endcol;
    bool isWhiteAttacking;
    bool isCapturingMove;
    unique_ptr<Board>& board;

  public:
    Move(int startrow, int startcol, int endrow, int endcol, unique_ptr<Board>& board);
    pair<int, int> getStartPos();
    pair<int, int> getEndPos();
    pair<pair<int, int>, pair<int, int> > getMove();
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~Move() {}
};

#endif
