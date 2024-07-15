#include <iostream>
#include "game.h"
#include "globals.h"
using namespace std;

const string HUMAN = "human";
const string COMPUTER = "computer";
const string L1 = "computer1";
const string L2 = "computer2";
const string L3 = "computer3";
const string L4 = "computer4";

unique_ptr<Player> createPlayer(string& input, bool isWhite) {
  if (input == HUMAN) {
    return make_unique<Human>(isWhite);
  }
  else if (input == COMPUTER) {
    return make_unique<Computer>(isWhite);
  }
  //else if (input == L1) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L2) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L3) {
  //  return make_unique<Computer>(isWhite);
  //}
  //else if (input == L4) {
  //  return make_unique<Computer>(isWhite);
  //}
  else throw runtime_error("missing strings in validInputs vector");
}

int main() {
  string cmd, arg1, arg2;
  unique_ptr<Game> game;

  while (cin >> cmd) {
    if (cmd == "game" ) {
      arg1 = getInput("player", validPlayers);
      unique_ptr<Player> p1 = createPlayer(arg1, true);

      arg2 = getInput("player", validPlayers);
      unique_ptr<Player> p2 = createPlayer(arg2, false);

      game = make_unique<Game>(cout, std::move(p1), std::move(p2));
      
      game->print();
    }
    else if (cmd == "resign") {
      if (!game->isP1Turn()) {
        cout << endl << "Black resigns. ";
        game->endGame(0);
      }
      if (game->isP1Turn()) {
        cout << endl << "White resigns. ";
        game->endGame(1);
      }
      game->reset();
    }
    else if (cmd == "move") {
      cin >> arg1 >> arg2;

    }
    else if (cmd == "setup") {
      game->setup();
    }
    else if (cmd == "q") break;
  }
}
