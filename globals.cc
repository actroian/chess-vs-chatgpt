#include <iostream>
#include "globals.h"
using namespace std;

vector<const string> validPlayers = {"human", "computer"/*,"L1", "L2", "L3", "L4"*/};
vector<const string> validPieces = {"p", "b", "k", "q", "n", "r"};
vector<const string> validSetupCommands = {"+", "-", "=", "done"};
vector<const string> validColours = {"white", "black"};
vector<const string> boardLocations = {
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", 
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", 
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", 
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", 
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", 
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", 
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", 
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", 
};
map<const string, pair<int,int>> posToInd;

void initializePosToInd() {
    for (int i = 0; i < boardLocations.size(); ++i) {
        const string& pos = boardLocations[i];
        int row = 8 - (pos[1] - '0');  // Convert '1'-'8' to 7-0
        int col = pos[0] - 'a';        // Convert 'a'-'h' to 0-7
        posToInd[pos] = {row, col};
    }
}
struct PosToIndInitializer {
    PosToIndInitializer() {
        initializePosToInd();
    }
};
PosToIndInitializer posToIndInitializer;

string getInput(const string& item, vector<const string>& validInputs) {
  string input;

  while (true) {
    cout << "Please enter a " << item << " (e.g. ";
    for (int i = 0; i < min(4, static_cast<int>(validInputs.size())); ++i) cout << (i != 0 ? ", " : "") << validInputs[i];
    cout << "):" << endl;

    cin >> input;

    // in-place conversion of input to lowercase
    transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

    for (const auto& s: validInputs) {
      if (input == s) {
        return input;
      }
    }
    cout << "Invalid input. Try again." << endl;
  }
}
