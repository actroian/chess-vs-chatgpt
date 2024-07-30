#include "bishop.h"
#include "board.h"
#include "move.h"
#include "globals.h"
using namespace std;

Bishop::Bishop(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Bishop::validMoves() const {
    vector<unique_ptr<Move>> moves;

    // while loops that go diagonally in each direction on the Game until its out of bounds
    bool first_piece_unmoved = b.at(row, col)->isUnmoved();
    int r = row + 1, c = col + 1;
    while (r <= 7 && c <= 7) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, first_piece_unmoved, b.at(r, c).get());
        }
        if (b.at(r, c) != nullptr) break;
        ++r; ++c;
    }
    r = row - 1; c = col - 1;
    while (r >= 0 && c >= 0) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, first_piece_unmoved, b.at(r, c).get());
        }
        if (b.at(r, c) != nullptr) break;
        --r; --c;
    }
    r = row + 1; c = col - 1;
    while (r <= 7 && c >= 0) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, first_piece_unmoved, b.at(r, c).get());
        }
        if (b.at(r, c) != nullptr) break;
        ++r; --c;
    }
    r = row - 1; c = col + 1;
    while (r >= 0 && c <= 7) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, first_piece_unmoved, b.at(r, c).get());
        }
        if (b.at(r, c) != nullptr) break;
        --r; ++c;
    }

    return moves;
}

char Bishop::getSymbol() const { return isWhite ? 'B' : 'b'; }
