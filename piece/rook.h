#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "globals.h"
#include <vector>
#include <memory>

class Rook : public Piece {
public:
    Rook(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // ROOK_H
