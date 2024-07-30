#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "board.h"
#include "move.h"
#include "globals.h"

using namespace std;

Queen::Queen(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Queen::validMoves() const {
    // a Queen can move like a Rook or Bishop
    // so, we'll instantiate a Rook and Bishop at the same coords as the Queen and find their possible moves
    Rook r{row, col, b, isWhite};
    Bishop bish{row, col, b, isWhite};

    vector<unique_ptr<Move>> rookMoves = r.validMoves();
    vector<unique_ptr<Move>> bishopMoves = bish.validMoves();

    // merge all possible moves into one vector
    vector<unique_ptr<Move>> mergedMoves;
    for (auto& move : rookMoves) {
        mergedMoves.push_back(std::move(move));
    }
    for (auto& move : bishopMoves) {
        mergedMoves.push_back(std::move(move));
    }

    return mergedMoves;
}

char Queen::getSymbol() const { return isWhite ? 'Q' : 'q'; }
