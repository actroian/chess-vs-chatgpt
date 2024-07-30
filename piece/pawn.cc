#include "pawn.h"
#include "board.h"
#include "move.h"
#include "globals.h"

using namespace std;

Pawn::Pawn(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Pawn::validMoves() const {
    vector<unique_ptr<Move>> moves;
    bool pawnDoubleMovedLast = false;
    const Move* lastMove = nullptr;

    // Check if prevMoves is not empty before accessing the top
    if (!b.prevMoves.empty()) {
        lastMove = b.prevMoves.top().get();

        // Check if lastMove is not nullptr and if lastMove->end has valid coordinates
        if (lastMove != nullptr && b.at(lastMove->end.first, lastMove->end.second) != nullptr &&
            !(b.prevMoves.size() <= 1) && tolower(b.at(lastMove->end.first, lastMove->end.second)->getSymbol()) == 'p' &&
            abs(lastMove->start.first - lastMove->end.first) == 2) {
            pawnDoubleMovedLast = true;
        }
    }
    bool first_piece_unmoved = b.at(row, col)->isUnmoved();

    if (isWhite) {
        if (row - 1 >= 0 && b.at(row - 1, col) == nullptr) {
            if (row - 1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row - 1, col}, 'Q'); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row - 1, col}, first_piece_unmoved);
            }
        }
        if (unmoved && row - 2 >= 0 && b.at(row - 1, col) == nullptr && b.at(row - 2, col) == nullptr) {
            emplaceNormalMove(moves, {row, col}, {row - 2, col}, first_piece_unmoved);
        }
        if (row - 1 >= 0 && col - 1 >= 0 && b.at(row - 1, col - 1) != nullptr && !b.at(row - 1, col - 1)->isWhitePiece()) {
            if (row - 1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row - 1, col - 1}, 'Q', b.at(row - 1, col - 1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row - 1, col - 1}, first_piece_unmoved, b.at(row - 1, col - 1).get());
            }
        }
        if (row - 1 >= 0 && col + 1 <= 7 && b.at(row - 1, col + 1) != nullptr && !b.at(row - 1, col + 1)->isWhitePiece()) {
            if (row - 1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row - 1, col + 1}, 'Q', b.at(row - 1, col + 1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row - 1, col + 1}, first_piece_unmoved, b.at(row - 1, col + 1).get());
            }
        }

        // en passant
        if (pawnDoubleMovedLast) {
            int r = row;
            if (lastMove->end == std::make_pair(r, col + 1) && !b.at(row, col + 1)->isWhitePiece()) {
                emplaceEnpassantMove(moves, {row, col}, {row - 1, col + 1}, {row, col + 1}, b.at(row, col + 1)->getSymbol());
            }
            if (lastMove->end == std::make_pair(r, col - 1) && !b.at(row, col - 1)->isWhitePiece()) {
                emplaceEnpassantMove(moves, {row, col}, {row - 1, col - 1}, {row, col - 1}, b.at(row, col - 1)->getSymbol());
            }
        }
    } else {
        if (row+1 <= 7 && b.at(row+1, col) == nullptr) {
            if (row+1 == 7) {
                emplacePromotionMove(moves, {row, col}, {row+1, col}, 'q'); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row+1, col}, first_piece_unmoved);
            }
        }
        if (unmoved && row+2 <= 7 && b.at(row+1, col) == nullptr && b.at(row+2, col) == nullptr) {
            emplaceNormalMove(moves, {row, col}, {row+2, col}, first_piece_unmoved);
        }
        if (row+1 <= 7 && col-1 >= 0 && b.at(row+1, col-1) != nullptr && b.at(row+1, col-1)->isWhitePiece()) {
            if (row+1 == 7) {
                emplacePromotionMove(moves, {row, col}, {row+1, col-1}, 'q', b.at(row+1, col-1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row+1, col-1}, first_piece_unmoved, b.at(row+1, col-1).get());
            }
        }
        if (row+1 <= 7 && col+1 <= 7 && b.at(row+1, col+1) != nullptr && b.at(row+1, col+1)->isWhitePiece()) {
            if (row+1 == 7) {
                emplacePromotionMove(moves, {row, col}, {row+1, col+1}, 'q', b.at(row+1, col+1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row+1, col+1}, first_piece_unmoved, b.at(row+1, col+1).get());
            }
        }
        // en passant
        if (pawnDoubleMovedLast && lastMove != nullptr) {
            int r = row;
            if (lastMove->end == std::make_pair(r, col+1) && b.at(row, col+1)->isWhitePiece()) {
                emplaceEnpassantMove(moves, {row, col}, {row+1, col+1}, {row, col+1}, b.at(row, col+1)->getSymbol());
            }
            if (lastMove->end == std::make_pair(r, col-1) && b.at(row, col-1)->isWhitePiece()) {
                emplaceEnpassantMove(moves, {row, col}, {row+1, col-1}, {row, col-1}, b.at(row, col-1)->getSymbol());
            }
        }
    }
    return moves;
}

char Pawn::getSymbol() const { return isWhite ? 'P' : 'p'; }
