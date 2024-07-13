#include <iostream>
#include "game.h"
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
  else {
    cout << "Incorrect player type. Try Again." << endl;
    cin >> input;
    return createPlayer(input, isWhite);
  }
}

int main() {
  string cmd, arg1, arg2;
  unique_ptr<Game> game;

  while (cin >> cmd) {
    if (cmd == "game" ) {
      cout << "Choose player 1" << endl;
      cin >> arg1;
      unique_ptr<Player> p1 = createPlayer(arg1, true);

      cout << "Choose player 2" << endl;
      cin >> arg2;
      unique_ptr<Player> p2 = createPlayer(arg2, false);

      game = make_unique<Game>(cout, std::move(p1), std::move(p2));
      
      // for debugging
      cout << game->p1->isWhite() << endl;
      cout << game->p2->isWhite() << endl;
      game->print();
    }
    else if (cmd == "resign") {
      
    }
    else if (cmd == "move") {
      cin >> arg1 >> arg2;

    }
    else if (cmd == "setup") {
      do {
        cin >> cmd;

        if (cmd == "+" ) {
          cin >> arg1 >> arg2;

        }
        else if (cmd == "-") {
          cin >> arg1;

        }
        else if (cmd == "=") {
          cin >> arg1;

        }
      } while (cmd != "done");
      // TODO: add setup verifications as outlined in chess.pdf
    }
  }
}
