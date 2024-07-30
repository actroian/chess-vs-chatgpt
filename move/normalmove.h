#ifndef NORMALMOVE_H
#define NORMALMOVE_H

#include "move.h"
#include "board.h"
#include "player.h"
#include <memory>


class NormalMove : public Move {
public:
    bool first_piece_move;
    bool captured_unmoved;

    NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0', bool first_piece_move = false, bool captured_unmoved = false);
    bool move(std::unique_ptr<Board>& board, Player* movingplayer, Player* opponent, bool isPromotionMove = false) const;
    void undo(Board& board);
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~NormalMove() {};
};

#endif // NORMALMOVE_H
