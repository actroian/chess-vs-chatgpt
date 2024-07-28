#ifndef L1_H
#define L1_H
#include "board.h"
#include "move.h"
#include "player.h"

class Move;

class L1: public Player {
  public:
    L1(bool);
    Move chooseMove(std::unique_ptr<Board>& b) override;
};

#endif
