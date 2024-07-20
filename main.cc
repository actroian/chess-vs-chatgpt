#include <iostream>
#include "game.h"
#include "globals.h"
using namespace std;

int main() {
  string cmd, arg1, arg2;
  Game game;

  while (cin >> cmd) {
    if (cmd == "game" ) {
      arg1 = getInput("player", validPlayers);
      arg2 = getInput("player", validPlayers);
      
      game.beginGame(arg1, arg2);
    }
    else if (cmd == "resign") {
      if (game.isInGame()) {
        if (!game.board->isP1Turn()) {
          cout << endl << "Black resigns. ";
          game.endGame(0);
        }
        if (game.board->isP1Turn()) {
          cout << endl << "White resigns. ";
          game.endGame(1);
        }
        game.reset();
      }
      else cout << "Cannot end game that is not in progress." << endl;
    }
    else if (cmd == "move") {
      cin >> arg1 >> arg2;
      pair<int, int> start = posToInd[arg1];
      pair<int, int> end = posToInd[arg2];
      game.move(start, end);
    }
    else if (cmd == "setup") {
      if (!game.isInGame()) {
        game.board->setup();
      }
      else cout << "Cannot enter setup mode during a match." << endl;
    }
    else if (cmd == "q") break;
  }
}
