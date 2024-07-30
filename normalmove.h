#ifndef NORMALMOVE_H
#define NORMALMOVE_H

#include "move.h"

class NormalMove : public Move {
  public:
    bool first_piece_move;
    bool captured_unmoved;
    NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0', bool first_piece_move = false, bool captured_unmoved = false);

    bool move(std::unique_ptr<Board>& board,  Player* p1, Player* p2, bool isPromotionMove = false) const override;
    void undo(Board& board) override;
    std::unique_ptr<Move> clone() const override;
    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~NormalMove() override {}
};

#endif
