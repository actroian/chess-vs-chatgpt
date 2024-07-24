#ifndef L2_H
#define L2_H

#include "L1.h"

using namespace std;

class L2: public L1 {
  public:
    L2(bool);
    Move chooseMove(unique_ptr<Board>& b) override;
    vector<Move> captureMoves();
    vector<Move> checkMoves();
};

#endif
