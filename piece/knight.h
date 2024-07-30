#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "globals.h"

#include <vector>
#include <memory>

class Knight : public Piece {
public:
    Knight(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // KNIGHT_H
