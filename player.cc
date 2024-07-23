#include "player.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <algorithm>

using namespace std;

Player::Player(bool isWhite): isWhite{isWhite}, inCheck{false} {}
Player::~Player() {}
bool Player::isP1() { return isWhite; }
void Player::setInCheck(bool inCheck) { this->inCheck = inCheck; }
bool Player::move(unique_ptr<Board>& b, const pair<int,int>& start, const pair<int,int>& end) {
  b->placePiece(end.first, end.second, std::move(b->at(start.first, start.second)));

  // check for pawn promotion
  if ((end.first == 7 && isP1()) || (end.first == 0 && !isP1())) {
    Pawn* p = dynamic_cast<Pawn*>(b->at(end.first, end.second).get());
    if (p) {
      string promotion = getInput("pawn promotion", validPromotions);
      b->placePiece(end.first, end.second, b->createPiece(promotion, end));
      cout << "Pawn promoted to " << promotion << endl;
    }
  }
  b->print(cout);
  return true;
}
vector<Move> Player::possibleMoves(unique_ptr<Board>& board) {
  vector<Move> moves;
  for(int row = 0; row <= 7; ++row ) {
    for(int col = 0; col <= 7; ++col) {
      if(board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
        vector<pair<int, int>> validMoves = board->at(row, col)->validMoves();
        for (auto& validmove: validMoves) {
          if (board->at(validmove.first, validmove.second) == nullptr || board->at(validmove.first, validmove.second)->isWhitePiece() != isWhite) {
            if (board->moveable(isWhite, validmove)) {
              Move move = Move({row, col}, {validmove.first, validmove.second}, board);
              if (inCheck) {
                // TODO: if this player is currently in check, only add to moves if the move gets them out of check
              }
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

bool Human::move(unique_ptr<Board>& b, const pair<int,int>& start, const pair<int,int>& end) {
    vector<Move> allmoves = possibleMoves(b);
    Move currentmove = Move(start, end, b);

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
