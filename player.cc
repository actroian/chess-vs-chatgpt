#include "player.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(bool isWhite): isWhite{isWhite}, inCheck{false} {}
Player::~Player() {}
bool Player::isInCheck() const { return inCheck; }
bool Player::isP1() { return isWhite; }
void Player::setInCheck(bool inCheck) { 
    this->inCheck = inCheck; 
    if (inCheck) {
        cout << (isWhite ? "P1 " : "P2 ") << "is in check!" << endl;
    }
}
std::unique_ptr<Move> Player::checkCastle(std::unique_ptr<Board>& b, const std::pair<int, int>& start, const std::pair<int, int>& end) {
    if (tolower(b->at(start.first, start.second)->getSymbol()) == 'k') {
        if (start.second == end.second + 2 && isWhite == b->at(start.first, start.second - 4)->isWhitePiece()) {
            return std::make_unique<Move>(std::make_pair(start.first, start.second - 4), std::make_pair(start.first, start.second - 1)); // left side
        }
        if (start.second == end.second - 2 && isWhite == b->at(start.first, start.second + 3)->isWhitePiece()) {
            return std::make_unique<Move>(std::make_pair(start.first, start.second + 3), std::make_pair(start.first, start.second + 1)); // right side
        }
    }
    return nullptr;
}

bool Player::move(unique_ptr<Board>& b, const pair<int,int>& start, const pair<int,int>& end) {
  unique_ptr<Move> castle_move = checkCastle(b, start, end);
  if(castle_move != nullptr) {
    b->placePiece(castle_move->end.first, castle_move->end.second, std::move(b->at(castle_move->start.first, castle_move->start.second)));
    b->placePiece(end.first, end.second, std::move(b->at(start.first, start.second)));
    return true;
  }
  bool movedToEmpty = b->at(end.first, end.second) == nullptr;
  b->placePiece(end.first, end.second, std::move(b->at(start.first, start.second)));
  Pawn* p = dynamic_cast<Pawn*>(b->at(end.first, end.second).get());
  // check if a pawn moved
  if (p) {
    // check for en passant - if so, remove pawn that got jumped
    if (movedToEmpty && start.first != end.first) {
        b->removePiece(start.first, end.second);
    }

    // check for pawn promotion
    if ((end.first == 0 && isP1()) || (end.first == 7 && !isP1())) {
      string promotion = getInput("pawn promotion", validPromotions);
      promotion = isP1() ? toupper(promotion[0]) : tolower(promotion[0]);
      b->placePiece(end.first, end.second, b->createPiece(promotion, end));
      cout << "Pawn promoted to " << promotion << endl;
    }
  }
  return true;
}
vector<Move> Player::possibleMoves(unique_ptr<Board>& board) {
  vector<Move> moves;
  for(int row = 0; row <= 7; ++row ) {
    for(int col = 0; col <= 7; ++col) {
      if(board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
        vector<pair<int, int>> validMoves = board->at(row, col)->validMoves();
        for (auto& validmove: validMoves) {
          if (board->moveable(isWhite, validmove)) {
            Move move = Move({row, col}, {validmove.first, validmove.second});
            if (inCheck) {
              // TODO: if this player is currently in check, only add to moves if the move gets them out of check
            }
            moves.push_back(move);
          }
        }
      }
    }
  }
  return moves;
}

Human::Human(bool isWhite): Player{isWhite} {}

bool Human::move(unique_ptr<Board>& b, const pair<int,int>& start, const pair<int,int>& end) {
    vector<Move> allmoves = possibleMoves(b);
    Move currentmove{start, end};
    if (std::find(allmoves.begin(), allmoves.end(), currentmove) != allmoves.end()) {
        Player::move(b, start, end);
        return true;
    } else {
        // not valid
        cout << "Invalid move, please pick a valid move!" << endl;
        return false;
    }
    return false;
}
