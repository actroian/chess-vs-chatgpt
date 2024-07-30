#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
#include <memory>

class Board;  // Forward declaration
class Move;  // Forward declaration

class Piece {
protected:
    int row;
    int col;
    Board& b;
    bool isWhite, unmoved;
public:
    Piece(int r, int c, Board& board, bool isWhite);
    virtual std::vector<std::unique_ptr<Move>> validMoves() const = 0;
    virtual char getSymbol() const = 0;
    bool isWhitePiece();
    bool isUnmoved() const;
    void setUnmoved(bool);
    void setPosition(int, int);
    virtual ~Piece() {}
};

#endif // PIECE_H
