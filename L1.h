#ifndef L1_H
#define L1_H
#include "board.h"
#include "move.h"
#include "player.h"
using namespace std;

class Move;

class L1: public Player {
  public:
    L1(bool);
    Move chooseMove(unique_ptr<Board>& b) override;
    vector<Move> getAllMoves();
};

#endif
