#ifndef L3_H
#define L3_H

#include "L2.h"

using namespace std;

class L3: public L2 {
    vector<unique_ptr<Move>> avoidCaptureMoves(unique_ptr<Board>& b, Player* p2);

  public:
    L3(bool);
    unique_ptr<Move> chooseMove(unique_ptr<Board>& b, Player* p2) override;

};

#endif
