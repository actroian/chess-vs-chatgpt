#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human: public Player {
  public:
    Human(bool);
    std::unique_ptr<Move> chooseMove(std::unique_ptr<Board>& b, Player* p2) override;
};

#endif
