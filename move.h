#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>
#include <memory>
#include "piece.h"
#include "player.h"
class Player;
class Move {
public:
    std::pair<int, int> start;
    std::pair<int, int> end;
    char captured_piece;

    Move(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0');
    virtual ~Move() = 0;

    virtual bool move(std::unique_ptr<Board>& board, std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) const = 0;
    virtual void undo(Board& board) const = 0;

    virtual bool operator==(const Move& other) const;
    virtual bool operator!=(const Move& other) const;
};

class NormalMove : public Move {
public:
    NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0');

    bool move(std::unique_ptr<Board>& board, std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~NormalMove() override {}
};

class CastleMove : public Move {
public:
    std::pair<int, int> rookstart;
    std::pair<int, int> rookend;

    CastleMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& rookstart, const std::pair<int, int>& rookend);

    bool move(std::unique_ptr<Board>& board, std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~CastleMove() override {}
};

class EnpassantMove : public Move {
public:
    std::pair<int, int> captured_position;

    EnpassantMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& captured_position, char captured_piece = '\0');

    bool move(std::unique_ptr<Board>& board, std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~EnpassantMove() override {}
};

class PromotionMove : public Move {
public:
    char promotion_piece;

    PromotionMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char promotion_piece, char captured_piece = '\0');

    bool move(std::unique_ptr<Board>& board, std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~PromotionMove() override {}
};

#endif // MOVE_H
