#include "game.h"
#include "piece.h"
#include "globals.h"
using namespace std;

Game::Game(): out{cout} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
}
Game::Game(ostream& out, unique_ptr<Player> p1, unique_ptr<Player> p2) : out{out}, wScore{0}, bScore{0}, p1Turn{true}, p1{std::move(p1)}, p2{std::move(p2)} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
  reset();
}
bool Game::isP1Turn() const { return p1Turn; }
void Game::reset() {
  board[0][0] = make_unique<Rook>(0, 0, *this, false);
  board[7][0] = make_unique<Rook>(7, 0, *this, true);
  board[0][1] = make_unique<Knight>(0, 1, *this, false);
  board[7][1] = make_unique<Knight>(7, 1, *this, true);
  board[0][2] = make_unique<Bishop>(0, 2, *this, false);
  board[7][2] = make_unique<Bishop>(7, 2, *this, true);
  board[0][3] = make_unique<Queen>(0, 3, *this, false);
  board[7][3] = make_unique<Queen>(7, 3, *this, true);
  board[0][4] = make_unique<King>(0, 4, *this, false);
  board[7][4] = make_unique<King>(7, 4, *this, true);
  board[0][5] = make_unique<Bishop>(0, 5, *this, false);
  board[7][5] = make_unique<Bishop>(7, 5, *this, true);
  board[0][6] = make_unique<Knight>(0, 6, *this, false);
  board[7][6] = make_unique<Knight>(7, 6, *this, true);
  board[0][7] = make_unique<Rook>(0, 7, *this, false);
  board[7][7] = make_unique<Rook>(7, 7, *this, true);
  //place pawns;
  for (int i = 0; i <=7 ; ++i) {
    board[6][i] = make_unique<Pawn>(1, i, *this, true);
  }
  for (int i = 0; i <=7 ; ++i) {
    board[1][i] = make_unique<Pawn>(1, i, *this, false);
  }
}
void Game::setup() {
  string cmd, arg1, arg2;

  while (cin >> cmd) {
    if (cmd == "+" ) {
      arg1 = getInput("type of piece", validPieces);
      arg2 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg2];

      if (board[location.first][location.second] == nullptr) out << "Placed piece at " << arg2 << endl;
      else out << "Replaced existing piece at " << arg2 << endl;
      
      unique_ptr<Piece> p = nullptr;
      if (arg1 == "p") {
        p = make_unique<Pawn>(location.first, location.second, *this, p1Turn);
      }
      if (arg1 == "k") {
        p = make_unique<King>(location.first, location.second, *this, p1Turn);
      }
      if (arg1 == "q") {
        p = make_unique<Queen>(location.first, location.second, *this, p1Turn);
      }
      if (arg1 == "b") {
        p = make_unique<Bishop>(location.first, location.second, *this, p1Turn);
      }
      if (arg1 == "r") {
        p = make_unique<Rook>(location.first, location.second, *this, p1Turn);
      }
      if (arg1 == "n") {
        p = make_unique<Knight>(location.first, location.second, *this, p1Turn);
      }
      board[location.first][location.second] = std::move(p);

      print();
    }
    else if (cmd == "-") {
      arg1 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg1];
      board[location.first][location.second] = nullptr;

      out << "Removed piece at: " << arg1 << endl;
      print();
    }
    else if (cmd == "=") {
      arg1 = getInput("colour", validColours);
      
      if (arg1 == validColours[0]) {
        p1Turn = true;
        out << "Next turn set to White." << endl;
      }
      if (arg1 == validColours[1]) {
        p1Turn = false;
        out << "Next turn set to Black." << endl;
      }
    }
    else if (cmd == "done") break;
  }
  // TODO: implement setup mode validation
}
void Game::print() const {
  for (int r = 0; r <= 7; ++r) {
    out << 8-r << " ";
    for (int c = 0; c <= 7; ++c) {
      auto& cell = board[r][c];
      if (cell == nullptr) {
        if ((r%2 == 0 && c%2 == 0) || (r%2 == 1 && c%2 == 1)) {
          out << " ";
          // can also try using ░
        }
        else {
          out << "▒";
        }
      }
      else {
        out << cell->getSymbol();
      }
    }
    out << endl;
  }
  out << endl << "  abcdefgh" << endl << endl;

  if (p1Turn) out << "White to move." << endl;
  else out << "Black to move." << endl;
}
void Game::endGame(int state) {
  switch (state) {
    // doesn't break since we always want default to execute. assume valid state is passed
    case 0:
      ++wScore;
      out << "White wins!" << endl;
      break;
    case 1:
      ++bScore;
      out << "Black wins!" << endl;
      break;
    case 2:
      wScore += 0.5;
      bScore += 0.5;
      out << "Stalemate!" << endl;
      break;
  }
  out << endl << "Final Score:" << endl;
  out << "White: " << wScore << endl;
  out << "Black: " << bScore << endl;
}
