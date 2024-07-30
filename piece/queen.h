#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "globals.h"

#include <vector>
#include <memory>

class Queen : public Piece {
public:
    Queen(int, int, Board&, bool);
    std::vector<std::unique_ptr<Move>> validMoves() const ;
    char getSymbol() const ;
};

#endif // QUEEN_H
