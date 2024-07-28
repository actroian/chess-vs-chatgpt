#include "player.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(bool isWhite, bool isBot): isWhite{isWhite}, inCheck{false}, isBot{isBot} {}
Player::~Player() {}
bool Player::isInCheck() const { return inCheck; }
bool Player::isP1() { return isWhite; }
bool Player::isABot() const { return isBot; }
void Player::setInCheck(bool inCheck) { this->inCheck = inCheck; }
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

bool Player::kingInCheck(unique_ptr<Board>& b, unique_ptr<Player>& p) const {
  vector<Move> moves = p->possibleMoves(b);
  int kingRow = 0;
  int kingCol = 0;

  for(int row = 0; row <= 7; row++) {
    for(int col = 0; col <= 7; col++) {
      if(b->at(row, col) != nullptr) {
        if(b->at(row, col)->isWhitePiece() == isWhite && tolower(b->at(row, col)->getSymbol()) == 'k'){
          kingRow = row;
          kingCol = col;
        }
      } 
    }
  }

  for(auto move : moves){
    if(move.end.first == kingRow && move.end.second == kingCol) {
      return true;
    } 
  }
  return false;
} 

bool Player::castle(std::unique_ptr<Board>& b, std::unique_ptr<Player>& p2, Move move, std::unique_ptr<Move>& castle_move) {
    auto start = move.start;
    auto end = move.end;
    
    if (start.second <= end.second) {
        for (int i = start.second; i < end.second - 1; ++i) {
            b->placePiece(start.first, i + 1, std::move(b->at(start.first, i)));
            b->removePiece(start.first, i);
            if (kingInCheck(b, p2)) {
                b->placePiece(start.first, i, std::move(b->at(start.first, i + 1)));
                b->removePiece(start.first, i + 1);
                b->print(cout);
                return false;
            }
        }
        b->placePiece(end.first, end.second, std::move(b->at(start.first, end.second - 1)));
        b->removePiece(start.first, end.second - 1);
    } else {
        for (int i = start.second; i > end.second + 1; --i) {
            b->placePiece(start.first, i - 1, std::move(b->at(start.first, i)));
            b->removePiece(start.first, i);
            if (kingInCheck(b, p2)) {
                b->placePiece(start.first, i, std::move(b->at(start.first, i - 1)));
                b->removePiece(start.first, i - 1);
                b->print(cout);
                return false;
            }
        }
        b->placePiece(end.first, end.second, std::move(b->at(start.first, end.second + 1)));
        b->removePiece(start.first, end.second + 1);
    }

    b->placePiece(castle_move->end.first, castle_move->end.second, std::move(b->at(castle_move->start.first, castle_move->start.second)));
    b->removePiece(castle_move->start.first, castle_move->start.second);
    b->prevMoves.push(move);
    b->prevMoves.push(*castle_move);

    return true;
}

bool Player::move(unique_ptr<Board>& b, unique_ptr<Player>& p2) {
    vector<Move> allmoves = possibleMoves(b);
    Move move = chooseMove(b);
    auto start = move.start;
    auto end = move.end;

    if (std::find(allmoves.begin(), allmoves.end(), move) != allmoves.end()) {
        // check if the move is a capturing move
        if (b->at(end.first, end.second) != nullptr) {
            move.captured_piece = b->at(end.first, end.second)->getSymbol();
        }

      unique_ptr<Move> castle_move = checkCastle(b, start, end);
      if(castle_move != nullptr) {
          if(castle(b, p2, move, castle_move)){
            b->prevMoves.push(Move(start, end, '\0', castle_move->start, castle_move->end, true ));
            return true;
          };
          return false;
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
      b->prevMoves.push(move);
      return true;
    }

    return false;
}
vector<Move> Player::possibleMoves(const unique_ptr<Board>& board) {
  vector<Move> moves;
  for(int row = 0; row <= 7; ++row ) {
    for(int col = 0; col <= 7; ++col) {
      if(board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
        vector<pair<int, int>> validMoves = board->at(row, col)->validMoves();
        for (auto& validmove: validMoves) {
          Move move = Move({row, col}, {validmove.first, validmove.second});
          if (inCheck) {
            // TODO: if this player is currently in check, only add to moves if the move gets them out of check
          }
          moves.push_back(move);
        }
      }
    }
  }
  return moves;
}

Human::Human(bool isWhite): Player{isWhite, false} {}

Move Human::chooseMove(unique_ptr<Board>& b) {
    string startLoc = getInput("location of piece you want to move", boardLocations);
    string endLoc = getInput("location you want to move the piece to", boardLocations);
  
    auto start = posToInd[startLoc];
    auto end = posToInd[endLoc];

    return Move{start,end};
}
