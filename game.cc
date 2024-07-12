#include "game.h"
#include "piece.h"
using namespace std;

Game::Game(ostream& out, Player& p1, Player& p2) : out{out}, wScore{0}, bScore{0}, p1{p1}, p2{p2} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
  reset();
}
void Game::reset() {
  board[0][0] = make_unique<Rook>(Rook{0, 0, *this, false});
  board[7][0] = make_unique<Rook>(Rook{7, 0, *this, true});
  board[0][1] = make_unique<Knight>(Knight{0, 1, *this, false});
  board[7][1] = make_unique<Knight>(Knight{7, 1, *this, true});
  board[0][2] = make_unique<Bishop>(Bishop{0, 2, *this, false});
  board[7][2] = make_unique<Bishop>(Bishop{7, 2, *this, true});
  board[0][3] = make_unique<Queen>(Queen{0, 3, *this, false});
  board[7][3] = make_unique<Queen>(Queen{7, 3, *this, true});
  board[0][4] = make_unique<King>(King{0, 4, *this, false});
  board[7][4] = make_unique<King>(King{7, 4, *this, true});
  board[0][5] = make_unique<Bishop>(Bishop{0, 5, *this, false});
  board[7][5] = make_unique<Bishop>(Bishop{7, 5, *this, true});
  board[0][6] = make_unique<Knight>(Knight{0, 6, *this, false});
  board[7][6] = make_unique<Knight>(Knight{7, 6, *this, true});
  board[0][7] = make_unique<Rook>(Rook{0, 7, *this, false});
  board[7][7] = make_unique<Rook>(Rook{7, 7, *this, true});
  //place pawns;
  for (int i = 0; i <=7 ; ++i) {
    board[6][i] = make_unique<Pawn>(Pawn{1, i, *this, true});
  }
  for (int i = 0; i <=7 ; ++i) {
    board[1][i] = make_unique<Pawn>(Pawn{1, i, *this, false});
  }
}
void Game::setup() {
  board.clear();

  // TODO: implement setup command interface
}
void Game::print() const {
  for (int r = 0; r <= 7; ++r) {
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
}
