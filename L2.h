#ifndef L2_H
#define L2_H

#include "L1.h"

class L2: public L1 {
    std::vector<std::unique_ptr<Move>> captureMoves(std::unique_ptr<Board>& b, Player* p2);
    std::vector<std::unique_ptr<Move>> checkMoves(std::unique_ptr<Board>& b, Player* p2);

  public:
    L2(bool);
    std::unique_ptr<Move> chooseMove(std::unique_ptr<Board>& b, Player* p2) override;
    
};

#endif
