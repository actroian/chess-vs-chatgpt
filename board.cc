#include "board.h"

using namespace std;

Board::Board(Game& game) : game{game} {
    // initialize empty board
    for (int i = 0; i <= 7; ++i) {
        vector<unique_ptr<Piece>> row(8);
        board.push_back(std::move(row));
    }
    resetBoard();
}

unique_ptr<Piece>& Board::at(int row, int col) {
    return board[row][col];
}

void Board::resetBoard() {
    board[0][0] = make_unique<Rook>(0, 0, game, false);
    board[7][0] = make_unique<Rook>(7, 0, game, true);
    board[0][1] = make_unique<Knight>(0, 1, game, false);
    board[7][1] = make_unique<Knight>(7, 1, game, true);
    board[0][2] = make_unique<Bishop>(0, 2, game, false);
    board[7][2] = make_unique<Bishop>(7, 2, game, true);
    board[0][3] = make_unique<Queen>(0, 3, game, false);
    board[7][3] = make_unique<Queen>(7, 3, game, true);
    board[0][4] = make_unique<King>(0, 4, game, false);
    board[7][4] = make_unique<King>(7, 4, game, true);
    board[0][5] = make_unique<Bishop>(0, 5, game, false);
    board[7][5] = make_unique<Bishop>(7, 5, game, true);
    board[0][6] = make_unique<Knight>(0, 6, game, false);
    board[7][6] = make_unique<Knight>(7, 6, game, true);
    board[0][7] = make_unique<Rook>(0, 7, game, false);
    board[7][7] = make_unique<Rook>(7, 7, game, true);

    //place pawns;
    for (int i = 0; i <= 7; ++i) {
        board[6][i] = make_unique<Pawn>(6, i, game, true);
        board[1][i] = make_unique<Pawn>(1, i, game, false);
    }
}

void Board::print(std::ostream& out) const {
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
}

void Board::placePiece(int row, int col, std::unique_ptr<Piece> piece) {
    board[row][col] = std::move(piece);
}

void Board::removePiece(int row, int col) {
    board[row][col] = nullptr;
}