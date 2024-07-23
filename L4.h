#ifndef L4_H
#define L4_H

#include "L3.h"

using namespace std;

class L4: public L3 {
  public:
    L4(bool);
    bool move(unique_ptr<Board>& b, const pair<int, int>&, const pair<int, int>&) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> checkmateMoves();
    vector<pair<int, int>> avoidCaptureMoves();
};

#endif
