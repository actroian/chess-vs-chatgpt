#include "king.h"
#include "board.h"
#include "move.h"
#include "castlemove.h"
#include "globals.h"

using namespace std;

King::King(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite}, canCastle{true} {}

vector<unique_ptr<Move>> King::validMoves() const {
    vector<unique_ptr<Move>> moves;
    for (int r = -1; r <= 1; ++r) {
        int newRow = row + r;
        for (int c = -1; c <= 1; ++c) {
            int newCol = col + c;
            if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7 && b.moveable(isWhite, {newRow, newCol})) {
                emplaceNormalMove(moves, {row, col}, {newRow, newCol}, b.at(row, col)->isUnmoved(), b.at(newRow, newCol).get());
            }
        }
    }
    if (canCastle && unmoved) {
        if (b.at(row, 0) != nullptr && col - 2 >= 0) {
            if (tolower(b.at(row, 0)->getSymbol()) == 'r' && b.at(row, 0)->isUnmoved()) {
                bool flag = true;
                for (int i = 1; i < col; ++i) {
                    if (b.at(row, i) != nullptr) {
                        flag = false;
                        break;
                    }
                }
                // all spaces between are empty: castling is a valid move
                if (flag && col - 2 >= 0 && b.at(row, 0)->isUnmoved()) {
                    moves.emplace_back(std::make_unique<CastleMove>(std::make_pair(row, col), std::make_pair(row, col - 2), std::make_pair(row, 0), std::make_pair(row, 3)));
                }
            }
        }

        if (b.at(row, 7) != nullptr && col + 2 <= 7) {
            if (tolower(b.at(row, 7)->getSymbol()) == 'r' && b.at(row, 7)->isUnmoved()) {
                bool flag = true;
                for (int i = 6; i > col; --i) {
                    if (b.at(row, i) != nullptr) {
                        flag = false;
                        break;
                    }
                }
                // all spaces between are empty: castling is a valid move
                if (flag && col + 2 <= 7 && b.at(row, 7)->isUnmoved()) {
                    moves.emplace_back(std::make_unique<CastleMove>(std::make_pair(row, col), std::make_pair(row, col + 2), std::make_pair(row, 7), std::make_pair(row, 5)));
                }
            }
        }
    }

    return moves;
}

char King::getSymbol() const { return isWhite ? 'K' : 'k'; }
