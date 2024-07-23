#ifndef L2_H
#define L2_H

#include "L1.h"

using namespace std;

class L2: public L1 {
  public:
    L2(bool);
    bool move(unique_ptr<Board>& b, const pair<int, int>&, const pair<int, int>&) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> captureMoves();
    vector<pair<int, int>> checkMoves();
};

#endif
