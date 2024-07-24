#ifndef L3_H
#define L3_H

#include "L2.h"

using namespace std;

class L3: public L2 {
    int attempts;
  public:
    L3(bool);
    Move chooseMove(unique_ptr<Board>& b) override;
    vector<Move> checkmateMoves();
    vector<Move> avoidCaptureMoves();
};

#endif
