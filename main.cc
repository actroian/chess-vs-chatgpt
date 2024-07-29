#include <iostream>
#include "game.h"
#include "globals.h"

#include <stdlib.h> // for srand and rand
#include <sys/types.h> // for getpid
#include <unistd.h> // for getpid

using namespace std;

int main() {

  // Seed the random number generator once at the start of the program
  int seed = getpid();
  srand(seed);

  string cmd, arg1, arg2;
  Game game;

  while (true) {
    cmd = getInput("command", validMainCommands);

    if (cmd == "game" ) {
      arg1 = getInput("player", validPlayers);
      arg2 = getInput("player", validPlayers);
      
      game.beginGame(arg1, arg2);
    }
    else if (cmd == "resign") {
      if (game.isInGame()) {
        if (!game.board->isP1Turn()) {
          cout << endl << "Black resigns. ";
          game.endGame(0, true);
        }
        if (game.board->isP1Turn()) {
          cout << endl << "White resigns. ";
          game.endGame(1, true);
        }
        game.reset();
      }
      else cout << "Cannot end game that is not in progress." << endl;
    }
    else if (cmd == "move") {
      // check that game is in progress
      if (!game.isInGame()) {
        cout  << "Cannot make move while game is not in progress." << endl;
        continue;
      }

      // invalid move prompts for a new command
      bool validMove = game.initiateMove();
      if (!validMove && ((game.p1->isABot() && game.board->isP1Turn()) || (game.p2->isABot() && !game.board->isP1Turn()))) {
        do {
          validMove = game.initiateMove();
        } while (!validMove);
      }

      game.print(validMove);
    }
    else if (cmd == "setup") {
      if (!game.isInGame()) {
        game.setup();
      }
      else cout << "Cannot enter setup mode during a match." << endl;
    }
    else if (cmd == "q") {
      game.printScore(true);
      break;
    };
  }
}
