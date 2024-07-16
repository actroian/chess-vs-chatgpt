#include "game.h"
#include "piece.h"
#include "globals.h"
using namespace std;

Game::Game(): out{cout}, board{make_unique<Board>(*this)} {}

Game::Game(ostream& out, unique_ptr<Player> p1, unique_ptr<Player> p2) : out{out}, wScore{0}, bScore{0}, p1Turn{true}, p1{std::move(p1)}, p2{std::move(p2)}, board{make_unique<Board>(*this)}{
  board->resetBoard();
}
bool Game::isP1Turn() const { return p1Turn; }
void Game::reset() {
  board->resetBoard();
}
void Game::setup() {
  string cmd, arg1, arg2;

  while (cin >> cmd) {
    if (cmd == "+" ) {
      arg1 = getInput("type of piece", validPieces);
      arg2 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg2];

      if (board->at(location.first, location.second) == nullptr) out << "Placed piece at " << arg2 << endl;
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
      board->placePiece(location.first, location.second, std::move(p));

      print();
    }
    else if (cmd == "-") {
      arg1 = getInput("position on the board", boardLocations);

      pair<int, int> location = posToInd[arg1];
      board->removePiece(location.first, location.second);

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
  board->print(out);

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
