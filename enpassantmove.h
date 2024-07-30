#ifndef ENPASSANTMOVE_H
#define ENPASSANTMOVE_H

#include "move.h"

class EnpassantMove : public Move {
  public:
    std::pair<int, int> captured_position;

    bool first_piece_move;
    bool captured_unmoved;
    EnpassantMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& captured_position, char captured_piece = '\0');

    bool move(std::unique_ptr<Board>& board,  Player* movingplayer, Player* opponent, bool isPromotionMove = false) const override;
    void undo(Board& board) override;
    std::unique_ptr<Move> clone() const override;
    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~EnpassantMove() override {}
};

#endif
