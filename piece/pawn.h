#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "globals.h"

#include <vector>
#include <memory>

class Pawn : public Piece {
public:
    Pawn(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // PAWN_H
