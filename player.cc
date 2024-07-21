#include "player.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <algorithm>

using namespace std;

Player::Player(bool isWhite): isWhite{isWhite}, inCheck{false} {}
Player::~Player() {}
bool Player::isP1() { return isWhite; }

vector<Move> Player::possibleMoves(unique_ptr<Board>& board) {
    vector<Move> moves;
    for(int row = 0; row <= 7; ++row ) {
        for(int col = 0; col <= 7; ++col) {
            if(board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
                vector<pair<int, int>> validMoves = board->at(row, col)->validMoves();
                for (auto& validmove: validMoves) {
                    if (board->at(validmove.first, validmove.second) == nullptr || board->at(validmove.first, validmove.second)->isWhitePiece() != isWhite) {
                        if (board->moveable(isWhite, validmove)) {
                            Move move = Move(row, col, validmove.first, validmove.second, board);
                            moves.push_back(move);
                        }
                    }
                }
            }
        }
    }
    return moves;
}

Human::Human(bool isWhite): Player{isWhite} {}

bool Human::move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) {
    vector<Move> allmoves = possibleMoves(b);
    Move currentmove = Move(startrow, startcol, endrow, endcol, b);
    if (std::find(allmoves.begin(), allmoves.end(), currentmove) != allmoves.end()) {
        b->placePiece(endrow, endcol, std::move(b->at(startrow, startcol)));
        b->print(cout);
        return true;
    } else {
        // not valid
        cout << "Invalid move, please pick a valid move!" << endl;
        return false;
    }
    return false;
}

Computer::Computer(bool isWhite) : Player(isWhite) {}

L1::L1(bool isWhite) : Computer(isWhite) {}

bool L1::move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) {
    // Implementation of L1 move logic
    return false;
}

pair<pair<int, int>, pair<int, int>> L1::chooseMove() {
    // Implementation of choosing a move for L1
    return {{0, 0}, {0, 0}};
}

vector<pair<int, int>> L1::getAllMoves() {
    // Implementation of getting all moves for L1
    return {};
}

L2::L2(bool isWhite) : L1(isWhite) {}

bool L2::move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) {
    // Implementation of L2 move logic
        return false;

}

pair<pair<int, int>, pair<int, int>> L2::chooseMove() {
    // Implementation of choosing a move for L2
    return {{0, 0}, {0, 0}};
}

vector<pair<int, int>> L2::captureMoves() {
    // Implementation of getting capture moves for L2
    return {};
}

vector<pair<int, int>> L2::checkMoves() {
    // Implementation of getting check moves for L2
    return {};
}

L3::L3(bool isWhite) : L2(isWhite) {}

bool L3::move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) {
    // Implementation of L3 move logic
        return false;

}

pair<pair<int, int>, pair<int, int>> L3::chooseMove() {
    // Implementation of choosing a move for L3
    return {{0, 0}, {0, 0}};
}

vector<pair<int, int>> L3::checkmateMoves() {
    // Implementation of getting checkmate moves for L3
    return {};
}

vector<pair<int, int>> L3::avoidCaptureMoves() {
    // Implementation of getting avoid capture moves for L3
    return {};
}
