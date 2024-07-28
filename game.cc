#include "game.h"

using namespace std;

Game::Game() : out{cout}, wScore{0}, bScore{0}, inGame{false}, board{make_unique<Board>()} {
  board->clearBoard();
}

void Game::reset() {
  board->resetBoard();
  p1->setInCheck(false);
  p2->setInCheck(false);
}
bool Game::isInGame() const { return inGame; }

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

  reset();
}

void Game::print(bool lastMoveValid) {
  board->print(out);

  if (!lastMoveValid) {
    out << "Invalid Move. ";
  }

  // check if game is in over
  if (p1->isInCheck()) {
    if (p1->possibleMoves(board).size() == 0) {
      endGame(1);
      return;
    }
    out << "White is in check! ";
  }
  else if (p2->isInCheck()) {
    if (p2->possibleMoves(board).size() == 0) {
      endGame(0);
      return;
    }
    out << "Black is in check! ";
  }
  else if (p1->possibleMoves(board).size() == 0 && p2->possibleMoves(board).size() == 0) {
    // stalemate
    endGame(2);
    return;
  }

  if (board->isP1Turn()) out << "White to move." << endl;
  else out << "Black to move." << endl;
}

unique_ptr<Player> Game::createPlayer(const string& input, bool isWhite) {
  if (input == HUMAN) {
    return make_unique<Human>(isWhite);
  }
  else if (input == L1input) {
    return make_unique<L1>(isWhite);
  }
  else if (input == L2input) {
    return make_unique<L2>(isWhite);
  }
  else if (input == L3input) {
    return make_unique<L3>(isWhite);
  }
  else if (input == L4input) {
    return make_unique<L4>(isWhite);
  }
  else throw runtime_error("missing strings in validInputs vector");
}
void Game::beginGame(const string& p1type, const string& p2type) {
  inGame = true;

  p1 = createPlayer(p1type, true);
  p2 = createPlayer(p2type, false);
  if (!board->isCustom()) board->resetBoard();

  print();
}

void Game::updateState(bool setupMode) {
  // determine if a player is in check
  bool checkWhite = board->isP1Turn();
  bool inCheck = false;

  // if p1's turn is coming up, we check if p2's current possible moves include capturing the king and vice versa
  vector<Move> moves = checkWhite ? p2->possibleMoves(board) : p1->possibleMoves(board);
  for (auto& move: moves) {
    auto loc = move.end;
    if (board->at(loc.first, loc.second) != nullptr && tolower(board->at(loc.first, loc.second)->getSymbol()) == 'k') {
      inCheck = true;
      break;
    } 
  }

  checkWhite ? p1->setInCheck(inCheck) : p2->setInCheck(inCheck);

  // update that the piece has been moved
  if(!setupMode){
    Move lastMove = board->prevMoves.top();
    board->at(lastMove.end.first, lastMove.end.second)->moved();
  }
}

void Game::setup() {
  p1 = createPlayer(HUMAN, true);
  p2 = createPlayer(HUMAN, false);
  board->setup();

  // after we set up the board, check if either player is in check
  updateState(true);
  board->setP1Turn(false);
  updateState(true);
  board->setP1Turn(true);

  if (p1->isInCheck() || p2->isInCheck()) {
    out << "Invalid board configuration: one or more players are in check!" << endl;
    out << "Please setup your board again." << endl;
    setup();
  }
  p1 = nullptr;
  p2 = nullptr;
}

bool Game::move(){
  bool piecemoved;
  if(board->isP1Turn()){
    piecemoved = p1->move(board, p2);
    if(p1->kingInCheck(board, p2)){
      p1->setInCheck(true);
      board->undo();
      return false;
    }
    p1->setInCheck(false);

  }
  else{
    piecemoved = p2->move(board, p1);
    if(p2->kingInCheck(board, p1)){
      p1->setInCheck(true);
      board->undo();
      return false;
    }
    p2->setInCheck(false);
  }

  if (!piecemoved) {
    return false;
  }

  board->setP1Turn(!board->isP1Turn());
  updateState();
  return true;
}