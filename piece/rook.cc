#include "rook.h"
#include "board.h"
#include "move.h"
#include "globals.h"

using namespace std;

Rook::Rook(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Rook::validMoves() const {
    vector<unique_ptr<Move>> moves;

    // add all valid horizontal moves
    bool first_piece_unmoved = b.at(row, col)->isUnmoved();
    for (int c = col + 1; c <= 7; c++) {
        if (b.moveable(isWhite, {row, c})) {
            emplaceNormalMove(moves, {row, col}, {row, c}, first_piece_unmoved, b.at(row, c).get());
        }
        if (b.at(row, c) != nullptr) break;
    }
    for (int c = col - 1; c >= 0; c--) {
        if (b.moveable(isWhite, {row, c})) {
            emplaceNormalMove(moves, {row, col}, {row, c}, first_piece_unmoved, b.at(row, c).get());
        }
        if (b.at(row, c) != nullptr) break;
    }
    // add all valid vertical moves
    for (int r = row + 1; r <= 7; r++) {
        if (b.moveable(isWhite, {r, col})) {
            emplaceNormalMove(moves, {row, col}, {r, col}, first_piece_unmoved, b.at(r, col).get());
        }
        if (b.at(r, col) != nullptr) break;
    }
    for (int r = row - 1; r >= 0; r--) {
        if (b.moveable(isWhite, {r, col})) {
            emplaceNormalMove(moves, {row, col}, {r, col}, first_piece_unmoved, b.at(r, col).get());
        }
        if (b.at(r, col) != nullptr) break;
    }

    return moves;
}

char Rook::getSymbol() const { return isWhite ? 'R' : 'r'; }
