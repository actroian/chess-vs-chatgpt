#ifndef L4_H
#define L4_H

#include "L3.h"

using namespace std;

class L4: public L3 {
    vector<unique_ptr<Move>> smartCapture(unique_ptr<Board>& b, Player* p2);

  public:
    L4(bool);
    unique_ptr<Move> chooseMove(unique_ptr<Board>& b, Player* p2) override;

};

#endif
