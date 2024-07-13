#include "game.h"
#include "piece.h"
using namespace std;

Game::Game(): out{cout} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
}
Game::Game(ostream& out, unique_ptr<Player> p1, unique_ptr<Player> p2) : out{out}, wScore{0}, bScore{0}, p1{std::move(p1)}, p2{std::move(p2)} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
  reset();
}
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
  board.clear();

  // TODO: implement setup command interface
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
  out << endl << "  abcdefgh" << endl;
}
void Game::endGame(int state) {
  switch (state) {
    // doesn't break since we always want default to execute. assume valid state is passed
    case 0:
      ++wScore;
      out << "White wins!" << endl;
    case 1:
      ++bScore;
      out << "Black wins!" << endl;
    case 2:
      wScore += 0.5;
      bScore += 0.5;
      out << "Stalemate!" << endl;
    default:
      out << endl << "Final Score:" << endl;
      out << "White: " << wScore << endl;
      out << "Black: " << bScore << endl;
  }
}
