#include "piece.h"
#include "board.h"
#include "move.h"

using namespace std;

// Helper function to create and emplace a NormalMove
void emplaceNormalMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, char capturedPiece = '\0') {
    moves.emplace_back(std::make_unique<NormalMove>(start, end, capturedPiece));
}

// Helper function to create and emplace an EnpassantMove
void emplaceEnpassantMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& capturedPosition, char capturedPiece) {
    moves.emplace_back(std::make_unique<EnpassantMove>(start, end, capturedPosition, capturedPiece));
}

// Helper function to create and emplace a PromotionMove
void emplacePromotionMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, char promotedTo, char capturedPiece = '\0') {
    moves.emplace_back(std::make_unique<PromotionMove>(start, end, promotedTo, capturedPiece));
}

Piece::Piece(int r, int c, Board& b, bool isWhite): row{r}, col{c}, b{b}, isWhite{isWhite}, unmoved{true} {}
bool Piece::isWhitePiece(){return isWhite;}
void Piece::moved() { unmoved = false; }
void Piece::setPosition(int newRow, int newCol) { row = newRow; col = newCol; }
bool Piece::isUnmoved() const { return unmoved; }

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

    if (isWhite) {
        if (row-1 >= 0 && b.at(row-1, col) == nullptr) {
            if (row-1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row-1, col}, 'Q'); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row-1, col});
            }
        }
        if (unmoved && row-2 >= 0 && b.at(row-1, col) == nullptr && b.at(row-2, col) == nullptr) {
            emplaceNormalMove(moves, {row, col}, {row-2, col});
        }
        if (row-1 >= 0 && col-1 >= 0 && b.at(row-1, col-1) != nullptr && !b.at(row-1, col-1)->isWhitePiece()) {
            if (row-1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row-1, col-1}, 'Q', b.at(row-1, col-1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row-1, col-1}, b.at(row-1, col-1)->getSymbol());
            }
        }
        if (row-1 >= 0 && col+1 <= 7 && b.at(row-1, col+1) != nullptr && !b.at(row-1, col+1)->isWhitePiece()) {
            if (row-1 == 0) {
                emplacePromotionMove(moves, {row, col}, {row-1, col+1}, 'Q', b.at(row-1, col+1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row-1, col+1}, b.at(row-1, col+1)->getSymbol());
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
                emplaceNormalMove(moves, {row, col}, {row+1, col});
            }
        }
        if (unmoved && row+2 <= 7 && b.at(row+1, col) == nullptr && b.at(row+2, col) == nullptr) {
            emplaceNormalMove(moves, {row, col}, {row+2, col});
        }
        if (row+1 <= 7 && col-1 >= 0 && b.at(row+1, col-1) != nullptr && b.at(row+1, col-1)->isWhitePiece()) {
            if (row+1 == 7) {
                emplacePromotionMove(moves, {row, col}, {row+1, col-1}, 'q', b.at(row+1, col-1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row+1, col-1}, b.at(row+1, col-1)->getSymbol());
            }
        }
        if (row+1 <= 7 && col+1 <= 7 && b.at(row+1, col+1) != nullptr && b.at(row+1, col+1)->isWhitePiece()) {
            if (row+1 == 7) {
                emplacePromotionMove(moves, {row, col}, {row+1, col+1}, 'q', b.at(row+1, col+1)->getSymbol()); // Assume promotion to Queen
            } else {
                emplaceNormalMove(moves, {row, col}, {row+1, col+1}, b.at(row+1, col+1)->getSymbol());
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

King::King(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite}, canCastle{true} {}

vector<unique_ptr<Move>> King::validMoves() const {
    vector<unique_ptr<Move>> moves;
    for (int r = -1; r <= 1; ++r) {
        int newRow = row + r;
        for (int c = -1; c <= 1; ++c) {
            int newCol = col + c;
            if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7 && b.moveable(isWhite, {newRow, newCol})) {
                emplaceNormalMove(moves, {row, col}, {newRow, newCol}, b.at(newRow, newCol) == nullptr ? '\0' : b.at(newRow, newCol)->getSymbol());
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

Bishop::Bishop(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Bishop::validMoves() const {
    vector<unique_ptr<Move>> moves;

    // while loops that go diagonally in each direction on the Game until its out of bounds
    int r = row + 1, c = col + 1;
    while (r <= 7 && c <= 7) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, b.at(r, c) == nullptr ? '\0' : b.at(r, c)->getSymbol());
        }
        if (b.at(r, c) != nullptr) break;
        ++r; ++c;
    }
    r = row - 1; c = col - 1;
    while (r >= 0 && c >= 0) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, b.at(r, c) == nullptr ? '\0' : b.at(r, c)->getSymbol());
        }
        if (b.at(r, c) != nullptr) break;
        --r; --c;
    }
    r = row + 1; c = col - 1;
    while (r <= 7 && c >= 0) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, b.at(r, c) == nullptr ? '\0' : b.at(r, c)->getSymbol());
        }
        if (b.at(r, c) != nullptr) break;
        ++r; --c;
    }
    r = row - 1; c = col + 1;
    while (r >= 0 && c <= 7) {
        if (b.moveable(isWhite, {r, c})) {
            emplaceNormalMove(moves, {row, col}, {r, c}, b.at(r, c) == nullptr ? '\0' : b.at(r, c)->getSymbol());
        }
        if (b.at(r, c) != nullptr) break;
        --r; ++c;
    }

    return moves;
}

char Bishop::getSymbol() const { return isWhite ? 'B' : 'b'; }

Rook::Rook(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Rook::validMoves() const {
    vector<unique_ptr<Move>> moves;

    // add all valid horizontal moves
    for (int c = col + 1; c <= 7; c++) {
        if (b.moveable(isWhite, {row, c})) {
            emplaceNormalMove(moves, {row, col}, {row, c}, b.at(row, c) == nullptr ? '\0' : b.at(row, c)->getSymbol());
        }
        if (b.at(row, c) != nullptr) break;
    }
    for (int c = col - 1; c >= 0; c--) {
        if (b.moveable(isWhite, {row, c})) {
            emplaceNormalMove(moves, {row, col}, {row, c}, b.at(row, c) == nullptr ? '\0' : b.at(row, c)->getSymbol());
        }
        if (b.at(row, c) != nullptr) break;
    }
    // add all valid vertical moves
    for (int r = row + 1; r <= 7; r++) {
        if (b.moveable(isWhite, {r, col})) {
            emplaceNormalMove(moves, {row, col}, {r, col}, b.at(r, col) == nullptr ? '\0' : b.at(r, col)->getSymbol());
        }
        if (b.at(r, col) != nullptr) break;
    }
    for (int r = row - 1; r >= 0; r--) {
        if (b.moveable(isWhite, {r, col})) {
            emplaceNormalMove(moves, {row, col}, {r, col}, b.at(r, col) == nullptr ? '\0' : b.at(r, col)->getSymbol());
        }
        if (b.at(r, col) != nullptr) break;
    }

    return moves;
}

char Rook::getSymbol() const { return isWhite ? 'R' : 'r'; }

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

Knight::Knight(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}

vector<unique_ptr<Move>> Knight::validMoves() const {
    vector<unique_ptr<Move>> moves;

    if (row+1 <= 7 && col+2 <= 7 && b.moveable(isWhite, {row+1, col+2})) {
        emplaceNormalMove(moves, {row, col}, {row+1, col+2});
    }
    if (row+2 <= 7 && col+1 <= 7 && b.moveable(isWhite, {row+2, col+1})) {
        emplaceNormalMove(moves, {row, col}, {row+2, col+1});
    }
    if (row+1 <= 7 && col-2 >= 0 && b.moveable(isWhite, {row+1, col-2})) {
        emplaceNormalMove(moves, {row, col}, {row+1, col-2});
    }
    if (row+2 <= 7 && col-1 >= 0 && b.moveable(isWhite, {row+2, col-1})) {
        emplaceNormalMove(moves, {row, col}, {row+2, col-1});
    }
    if (row-1 >= 0 && col+2 <= 7 && b.moveable(isWhite, {row-1, col+2})) {
        emplaceNormalMove(moves, {row, col}, {row-1, col+2});
    }
    if (row-2 >= 0 && col+1 <= 7 && b.moveable(isWhite, {row-2, col+1})) {
        emplaceNormalMove(moves, {row, col}, {row-2, col+1});
    }
    if (row-1 >= 0 && col-2 >= 0 && b.moveable(isWhite, {row-1, col-2})) {
        emplaceNormalMove(moves, {row, col}, {row-1, col-2});
    }
    if (row-2 >= 0 && col-1 >= 0 && b.moveable(isWhite, {row-2, col-1})) {
        emplaceNormalMove(moves, {row, col}, {row-2, col-1});
    }

    return moves;
}

char Knight::getSymbol() const { return isWhite ? 'N' : 'n'; }