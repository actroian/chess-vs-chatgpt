#include "game.h"
using namespace std;

Chessboard::Chessboard(ostream& out, bool setupMode = false) : out{out} {
  // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }

  if (setupMode) return;

  // TODO: initialize to standard board configuration since we aren't in setup mode
}
void Chessboard::print() const {
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
