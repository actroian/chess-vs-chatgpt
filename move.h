#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>
#include <memory>
#include "piece.h"
#include "player.h"
#include "board.h"

class Move {
public:
    std::pair<int, int> start;
    std::pair<int, int> end;
    char captured_piece;

    Move(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0');
    virtual ~Move() = 0;
    virtual std::unique_ptr<Move> clone() const = 0;
    virtual bool move(std::unique_ptr<Board>& board, Player* p1, Player* p2, bool isPromotionMove = false) const = 0;
    virtual void undo(Board& board) = 0;

    virtual bool operator==(const Move& other) const;
    virtual bool operator!=(const Move& other) const;
};

#endif // MOVE_H
