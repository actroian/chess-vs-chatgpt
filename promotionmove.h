#ifndef PROMOTIONMOVE_H
#define PROMOTIONMOVE_H

#include "move.h"

class PromotionMove : public Move {
public:
    char promotion_piece;

    PromotionMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char promotion_piece, char captured_piece = '\0');

    bool move(std::unique_ptr<Board>& board,  Player* movingplayer, Player* opponent, bool isPromotionMove = false) const override;
    void undo(Board& board) override;
    std::unique_ptr<Move> clone() const override;
    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~PromotionMove() override {}
};

#endif
