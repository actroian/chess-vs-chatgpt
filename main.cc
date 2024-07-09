#include <iostream>
using namespace std;

int main() {
  string cmd, arg1, arg2;

  while (cin >> cmd) {
    if (cmd == "game" ) {
      cin >> arg1 >> arg2;

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
