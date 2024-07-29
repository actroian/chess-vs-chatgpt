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
            return std::make_unique<CastleMove>(std::make_pair(start.first, start.second), end, std::make_pair(start.first, start.second - 4), std::make_pair(start.first, start.second - 1)); // left side
        }
        if (start.second == end.second - 2 && isWhite == b->at(start.first, start.second + 3)->isWhitePiece()) {
            return std::make_unique<CastleMove>(std::make_pair(start.first, start.second), end, std::make_pair(start.first, start.second + 3), std::make_pair(start.first, start.second + 1)); // right side
        }
    }
    return nullptr;
}
vector<unique_ptr<Move>> Player::allMoves(unique_ptr<Board>& board, Player* p2){
    vector<unique_ptr<Move>> moves;
    for (int row = 0; row <= 7; ++row) {
        for (int col = 0; col <= 7; ++col) {
            if (board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
                vector<unique_ptr<Move>> validMoves = board->at(row, col)->validMoves();
                for (auto& validmove : validMoves) {
                  moves.push_back(std::move(validmove));
                }
            }
        }
    }
    return moves;
}

bool Player::kingInCheck(unique_ptr<Board>& b, Player* p1,  Player* p2) {
    vector<unique_ptr<Move>> moves = p2->allMoves(b, p1);
    int kingRow = 0;
    int kingCol = 0;

    for (int row = 0; row <= 7; row++) {
        for (int col = 0; col <= 7; col++) {
            if (b->at(row, col) != nullptr) {
                if (b->at(row, col)->isWhitePiece() == isWhite && tolower(b->at(row, col)->getSymbol()) == 'k') {
                    kingRow = row;
                    kingCol = col;
                }
            }
        }
    }

    for (const auto& move : moves) {
        if (move->end.first == kingRow && move->end.second == kingCol) {
            return true;
        }
    }
    return false;
}

vector<unique_ptr<Move>> Player::possibleMoves(unique_ptr<Board>& board, Player* p2, bool checkTest) {
    vector<unique_ptr<Move>> moves;
    for (int row = 0; row <= 7; ++row) {
        for (int col = 0; col <= 7; ++col) {
            if (board->at(row, col) != nullptr && board->at(row, col)->isWhitePiece() == isWhite) {
                vector<unique_ptr<Move>> validMoves = board->at(row, col)->validMoves();
                for (auto& validmove : validMoves) {
                    // Clone the move to avoid invalid state after move
                    bool undone = false;
                    if (validmove->move(board, this, p2, false)) {
                        if (!kingInCheck(board, this, p2)) {
                            validmove->undo(*board);
                            undone = true;
                            moves.push_back(std::move(validmove));
                        } 
                    }
                    if(!undone){
                      validmove->undo(*board);
                    }
                }
            }
        }
    }
    return moves;
}

vector<pair<int, int>> Player::getMyPiecePositions(std::unique_ptr<Board>& b, bool isWhite) {
  vector<pair<int, int>> myPos;
  for(int row = 0; row <= 7; row++) {
    for(int col = 0; col <= 7; col++) {
      if(b->at(row, col) != nullptr) {
        if(b->at(row, col)->isWhitePiece() == isWhite){
          myPos.push_back(make_pair(row, col));
        }
      } 
    }
  }
  return myPos;
}

Human::Human(bool isWhite): Player{isWhite, false} {}

unique_ptr<Move> Human::chooseMove(unique_ptr<Board>& b, Player* p2) {
    string startLoc = getInput("location of piece you want to move", boardLocations);
    string endLoc = getInput("location you want to move the piece to", boardLocations);
  
    auto start = posToInd[startLoc];
    auto end = posToInd[endLoc];

    return std::make_unique<NormalMove>(start, end);
}
