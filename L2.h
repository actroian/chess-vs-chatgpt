#ifndef L2_H
#define L2_H

#include "L1.h"

using namespace std;

class L2: public L1 {
    vector<Move> captureMoves(unique_ptr<Board>& b);
    vector<Move> checkMoves(unique_ptr<Board>& b);

  public:
    L2(bool);
    Move chooseMove(unique_ptr<Board>& b) override;
    
};

#endif
