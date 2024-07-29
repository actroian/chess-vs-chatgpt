#include "board.h"
#include "piece.h"
#include "globals.h"
using namespace std;

Board::Board() : p1Turn{true}, custom{false}, window{185,185} {
    // initialize empty board
    for (int i = 0; i <= 7; ++i) {
        std::vector<std::unique_ptr<Piece>> row(8);
        board.push_back(std::move(row));
    }
}


bool Board::isCustom() const { return custom; }
void Board::resetBoard() {
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

void Board::print(std::ostream& out) {
  // clear window to prevent layering
  window.fillRectangle(0,0,185,185,0);

  string terminalOutput, xwindowOutput;
  for (int r = 0; r <= 7; ++r) {
    string num = to_string(8-r) + " ";
    out << num;
    window.drawString(5, 20*(r+1), num);
    for (int c = 0; c <= 7; ++c) {
      auto& cell = board[r][c];
      int screenX = c * 20;
      int screenY = r * 20;
      if (cell == nullptr) {
        if ((r%2 == 0 && c%2 == 0) || (r%2 == 1 && c%2 == 1)) {
          terminalOutput = " ";
          xwindowOutput = " ";
          // can also try using ░
        }
        else {
          terminalOutput = "▒";
          xwindowOutput = "_";
        }
      }
      else {
        char symbol = cell->getSymbol();
        xwindowOutput = string(1, symbol);
        if (tolower(symbol) == 'p') terminalOutput = (cell->isWhitePiece() ? "♟︎":"♙");
        else if (tolower(symbol) == 'b') terminalOutput = (cell->isWhitePiece() ? "♝":"♗");
        else if (tolower(symbol) == 'k') terminalOutput = (cell->isWhitePiece() ? "♚":"♔");
        else if (tolower(symbol) == 'q') terminalOutput = (cell->isWhitePiece() ? "♛":"♕");
        else if (tolower(symbol) == 'r') terminalOutput = (cell->isWhitePiece() ? "♜":"♖");
        else if (tolower(symbol) == 'n') terminalOutput = (cell->isWhitePiece() ? "♞":"♘");
      }
      out << terminalOutput;
      window.drawString(screenX + 20, screenY + 20, xwindowOutput);
    }
    out << endl;
  }
  terminalOutput = "  abcdefgh";
  xwindowOutput = terminalOutput.substr(2);

  out << endl << terminalOutput << endl << endl;
  for (int i = 0; i < xwindowOutput.length(); i++) {
    string letter = string(1,xwindowOutput[i]);
    window.drawString(20*i + 20, 20*9, letter);
  }
}

void Board::placePiece(int row, int col, unique_ptr<Piece>&& piece) {
  board[row][col] = std::move(piece);
  board[row][col]->setPosition(row, col);
}

void Board::removePiece(int row, int col) {
    board[row][col] = nullptr;
}

unique_ptr<Piece>& Board::at(int row, int col) {
    return board[row][col];
}

bool Board::moveable(bool isWhite, const pair<int,int>& move) const {
  return board[move.first][move.second] == nullptr || board[move.first][move.second]->isWhitePiece() != isWhite;
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
    stack<unique_ptr<Move>> newPrevMoves;
    std::swap(prevMoves, newPrevMoves);
}

unique_ptr<Piece> Board::createPiece(string& pieceType, const pair<int,int>& location) const {
  bool isWhite = isupper(pieceType[0]);
  pieceType = tolower(pieceType[0]);

  Board& nonConstThis = const_cast<Board&>(*this);
  if (pieceType == "p") {
    return make_unique<Pawn>(location.first, location.second, nonConstThis, isWhite);
  }
  if (pieceType == "k") {
    return make_unique<King>(location.first, location.second, nonConstThis, isWhite);
  }
  if (pieceType == "q") {
    return make_unique<Queen>(location.first, location.second, nonConstThis, isWhite);
  }
  if (pieceType == "b") {
    return make_unique<Bishop>(location.first, location.second, nonConstThis, isWhite);
  }
  if (pieceType == "r") {
    return make_unique<Rook>(location.first, location.second, nonConstThis, isWhite);
  }
  if (pieceType == "n") {
    return make_unique<Knight>(location.first, location.second, nonConstThis, isWhite);
  }
  return nullptr;
}

bool Board::validateBoard() {
  // check for exactly one king
  pair<int,int> whiteKblackK{0,0};
  for (int r = 0; r <= 7; r++) {
    for (int c = 0; c <= 7; c++) {
      if (at(r,c) != nullptr) {
        if (at(r,c)->getSymbol() == 'K') ++whiteKblackK.first;
        else if (at(r,c)->getSymbol() == 'k') ++whiteKblackK.second;
      }
    }
  }
  if (whiteKblackK.first != 1 || whiteKblackK.second != 1) {
    cout << "Missing/Too many kings. Please setup a valid board." << endl;
    return false;
  }

  // check that pawns aren't in first or last row
  for (int c = 0; c <= 7; c++) {
    if ((at(0, c) != nullptr && tolower(at(0, c)->getSymbol()) == 'p') ||
      (at(7, c) != nullptr && tolower(at(7, c)->getSymbol()) == 'p')) {
        cout << "Pawn placed in first or last row. Please setup a valid board." << endl;
        return false;
      }
  }
  
  return true;
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
      
      unique_ptr<Piece> p = createPiece(arg1, location);

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
  if (!validateBoard()) setup();
}

void Board::undo() {
  if (prevMoves.empty()) {
    // shouldn't reach this
    cout << "Can't undo when no moves have been made" << endl;
    return;
  }

  unique_ptr<Move>& lastMove = prevMoves.top();
  prevMoves.pop();
  lastMove->undo(*this);
}