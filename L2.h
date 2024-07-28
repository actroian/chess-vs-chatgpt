#ifndef L2_H
#define L2_H

#include "L1.h"

class L2: public L1 {
    std::vector<Move> captureMoves(std::unique_ptr<Board>& b);
    std::vector<Move> checkMoves(std::unique_ptr<Board>& b);

  public:
    L2(bool);
    Move chooseMove(std::unique_ptr<Board>& b) override;
    
};

#endif
