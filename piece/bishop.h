#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "globals.h"

#include <vector>
#include <memory>

class Bishop : public Piece {
public:
    Bishop(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // BISHOP_H
