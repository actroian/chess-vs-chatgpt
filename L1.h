#ifndef L1_H
#define L1_H
#include "board.h"
#include "move.h"
#include "computer.h"
using namespace std;

class Move;
class Computer;

class L1: public Computer {
  public:
    L1(bool);
    bool move(unique_ptr<Board>& b, const pair<int, int>&, const pair<int, int>&) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> getAllMoves();
};

#endif
