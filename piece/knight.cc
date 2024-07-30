#include "knight.h"
#include "board.h"
#include "move.h"
#include "globals.h"

using namespace std;

Knight::Knight(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Knight::validMoves() const {
    vector<unique_ptr<Move>> moves;
    bool first_piece_unmoved = b.at(row, col)->isUnmoved();
    if (row+1 <= 7 && col+2 <= 7 && b.moveable(isWhite, {row+1, col+2})) {
        emplaceNormalMove(moves, {row, col}, {row+1, col+2}, first_piece_unmoved, b.at(row+1, col+2).get());
    }
    if (row+2 <= 7 && col+1 <= 7 && b.moveable(isWhite, {row+2, col+1})) {
        emplaceNormalMove(moves, {row, col}, {row+2, col+1}, first_piece_unmoved, b.at(row+2, col+1).get());
    }
    if (row+1 <= 7 && col-2 >= 0 && b.moveable(isWhite, {row+1, col-2})) {
        emplaceNormalMove(moves, {row, col}, {row+1, col-2}, first_piece_unmoved, b.at(row+1, col-2).get());
    }
    if (row+2 <= 7 && col-1 >= 0 && b.moveable(isWhite, {row+2, col-1})) {
        emplaceNormalMove(moves, {row, col}, {row+2, col-1}, first_piece_unmoved, b.at(row+2, col-1).get());
    }
    if (row-1 >= 0 && col+2 <= 7 && b.moveable(isWhite, {row-1, col+2})) {
        emplaceNormalMove(moves, {row, col}, {row-1, col+2}, first_piece_unmoved, b.at(row-1, col+2).get());
    }
    if (row-2 >= 0 && col+1 <= 7 && b.moveable(isWhite, {row-2, col+1})) {
        emplaceNormalMove(moves, {row, col}, {row-2, col+1}, first_piece_unmoved, b.at(row-2, col+1).get());
    }
    if (row-1 >= 0 && col-2 >= 0 && b.moveable(isWhite, {row-1, col-2})) {
        emplaceNormalMove(moves, {row, col}, {row-1, col-2}, first_piece_unmoved, b.at(row-1, col-2).get());
    }
    if (row-2 >= 0 && col-1 >= 0 && b.moveable(isWhite, {row-2, col-1})) {
        emplaceNormalMove(moves, {row, col}, {row-2, col-1}, first_piece_unmoved, b.at(row-2,  col-1).get());
    }

    return moves;
}

char Knight::getSymbol() const { return isWhite ? 'N' : 'n'; }
