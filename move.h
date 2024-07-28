#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>
#include "piece.h"

class Move {
public:
    std::pair<int, int> start;
    std::pair<int, int> end;
    char captured_piece;

    Move(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0');
    virtual ~Move() = 0;

    virtual void move(Board& board) const = 0;
    virtual void undo(Board& board) const = 0;

    virtual bool operator==(const Move& other) const;
    virtual bool operator!=(const Move& other) const;
};

class NormalMove : public Move {
public:
    NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece = '\0');

    void move(Board& board) const override;
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

    void move(Board& board) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~CastleMove() override {}
};

class EnpassantMove : public Move {
public:
    std::pair<int, int> captured_position;

    EnpassantMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& captured_position, char captured_piece = '\0');

    void move(Board& board) const override;
    void undo(Board& board) const override;

    bool operator==(const Move& other) const override;
    bool operator!=(const Move& other) const override;

    ~EnpassantMove() override {}
};

#endif // MOVE_H
