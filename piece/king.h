#ifndef KING_H
#define KING_H

#include "piece.h"
#include "globals.h"

#include <vector>
#include <memory>

class King : public Piece {
    bool canCastle;
public:
    King(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // KING_H
