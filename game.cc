#include "game.h"
#include "piece.h"
#include "globals.h"
#include "player.h"
#include "board.h"
using namespace std;

Game::Game() : out{cout}, wScore{0}, bScore{0}, inGame{false}, board{make_unique<Board>()} {
  board->clearBoard();
}

void Game::reset() {
  board->resetBoard(p1, p2);
}
bool Game::isInGame() const { return inGame; }
void Game::print() const {
  board->print(out);

  if (board->isP1Turn()) out << "White to move." << endl;
  else out << "Black to move." << endl;
}
void Game::endGame(int state) {
  inGame = false;

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
  out << "Black: " << bScore << endl << endl;
}

unique_ptr<Player> Game::createPlayer(const string& input, bool isWhite) {
  if (input == HUMAN) {
    return make_unique<Human>(isWhite);
  }
  else if (input == COMPUTER) {
    return make_unique<L1>(isWhite);
  }
  //else if (input == L1input) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L2input) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L3input) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L4input) {
  //  return make_unique<Computer>(isWhite);
  //}
  else throw runtime_error("missing strings in validInputs vector");
}
void Game::beginGame(const string& p1type, const string& p2type) {
  inGame = true;

  p1 = createPlayer(p1type, true);
  p2 = createPlayer(p2type, false);
  if (!board->isCustom()) board->resetBoard(p1, p2);

  print();
}

void Game::move(pair<int, int> start, pair<int, int> end){
  if(board->isP1Turn()){
    cout<<"p1 moving"<<endl;
    bool piecemoved = p1->move(board, start.first, start.second, end.first, end.second);
    if(piecemoved) board->setP1Turn(!board->isP1Turn());

  }
  else{
    cout<<"p2 moving"<<endl;
    bool piecemoved = p2->move(board, start.first, start.second, end.first, end.second);
    if(piecemoved) board->setP1Turn(!board->isP1Turn());

  }
}