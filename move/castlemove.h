#ifndef CASTLEMOVE_H
#define CASTLEMOVE_H

#include "move.h"
#include "board.h"
#include "player.h"

class CastleMove : public Move {
public:
    std::pair<int, int> rookstart;
    std::pair<int, int> rookend;

    CastleMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& rookstart, const std::pair<int, int>& rookend);

    bool move(std::unique_ptr<Board>& board, Player* p1, Player* p2, bool isPromotionMove = false) const;
    void undo(Board& board);
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;

    ~CastleMove() {}
};

#endif // CASTLEMOVE_H
