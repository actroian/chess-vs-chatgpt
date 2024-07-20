#include "board.h"
#include "globals.h"
using namespace std;

Board::Board() : p1Turn{true}, custom{false} {
    // initialize empty board
  for (int i = 0; i <= 7; ++i) {
    vector<unique_ptr<Piece>> row(8);
    board.push_back(std::move(row));
  }
}

bool Board::isCustom() const { return custom; }
void Board::resetBoard(std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2) {
    clearBoard();
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
    for (int i = 0; i <= 7; ++i) {
        board[6][i] = make_unique<Pawn>(6, i, *this, true);
        board[1][i] = make_unique<Pawn>(1, i, *this, false);
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

void Board::placePiece(int row, int col, unique_ptr<Piece>&& piece) {
  board[row][col] = std::move(piece);
}

void Board::removePiece(int row, int col) {
    board[row][col] = nullptr;
}

unique_ptr<Piece>& Board::at(int row, int col) {
    return board[row][col];
}

bool Board::isP1Turn() const { return p1Turn; }

void Board::setP1Turn(bool isP1Turn) { p1Turn = isP1Turn; }

void Board::clearBoard() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            board[r][c] = nullptr;
        }
    }
    custom = false;
}

void Board::setup() {
  clearBoard();
  
  custom = true;
  string cmd, arg1, arg2;

  cout << "Entered setup mode." << endl;

  while (true) {
    cmd = getInput("setup command", validSetupCommands);
    if (cmd == "+" ) {
      arg1 = getInput("type of piece", validPieces);
      arg2 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg2];
      
      unique_ptr<Piece> p = nullptr;
      if (arg1 == "p") {
        p = make_unique<Pawn>(location.first, location.second, *this, isP1Turn());
      }
      if (arg1 == "k") {
        p = make_unique<King>(location.first, location.second, *this, isP1Turn());
      }
      if (arg1 == "q") {
        p = make_unique<Queen>(location.first, location.second, *this, isP1Turn());
      }
      if (arg1 == "b") {
        p = make_unique<Bishop>(location.first, location.second, *this, isP1Turn());
      }
      if (arg1 == "r") {
        p = make_unique<Rook>(location.first, location.second, *this, isP1Turn());
      }
      if (arg1 == "n") {
        p = make_unique<Knight>(location.first, location.second, *this, isP1Turn());
      }

      if (at(location.first, location.second) == nullptr) cout << "Placed piece " << p->getSymbol() << " at " << arg2 << endl;
      else cout << "Replaced existing piece at " << arg2 << endl;

      placePiece(location.first, location.second, std::move(p));

      print(cout);
    }
    else if (cmd == "-") {
      arg1 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg1];

      if (at(location.first, location.second) != nullptr) cout << "Removed piece " << at(location.first, location.second)->getSymbol() << " at: " << arg1 << endl;
      removePiece(location.first, location.second);

      print(cout);
    }
    else if (cmd == "=") {
      arg1 = getInput("colour", validColours);
      
      if (arg1 == validColours[0]) {
        setP1Turn(true);
        cout << "Next turn set to White." << endl;
      }
      if (arg1 == validColours[1]) {
        setP1Turn(false);
        cout << "Next turn set to Black." << endl;
      }
    }
    else if (cmd == "done") break;
  }
  // TODO: implement setup mode validation
}
