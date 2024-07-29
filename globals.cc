#include <iostream>
#include "globals.h"
#include "player.h"
using namespace std;

vector<string> validMainCommands = {"game","move","setup","resign", "q"};
vector<string> validPlayers = {"human", "computer1", "computer2", "computer3", "computer4"};
vector<string> validPieces = {"p", "b", "k", "q", "n", "r", "P", "B", "K", "Q", "N", "R"};
vector<string> validPromotions = {"r", "k", "b", "q"};
vector<string> validSetupCommands = {"+", "-", "=", "done"};
vector<string> validColours = {"white", "black"};
vector<string> boardLocations = {
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", 
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", 
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", 
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", 
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", 
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", 
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", 
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", 
};
map<string, pair<int,int>> posToInd;
map<pair<int,int>, string> indToPos;

const NormalMove NO_LAST_MOVE{{-1,-1},{-1,-1}};

void initializePosToInd() {
    for (int i = 0; i < boardLocations.size(); ++i) {
        const string& pos = boardLocations[i];
        int row = 8 - (pos[1] - '0');  // Convert '1'-'8' to 7-0
        int col = pos[0] - 'a';        // Convert 'a'-'h' to 0-7
        posToInd[pos] = {row, col};
    }
}
void initializeIndToPos() {
    for (const auto& entry : posToInd) {
        indToPos[entry.second] = entry.first;
    }
}
struct PosToIndInitializer {
    PosToIndInitializer() {
        initializePosToInd();
        initializeIndToPos();
    }
};
PosToIndInitializer posToIndInitializer;

string getInput(const string& item, vector<string>& validInputs) {
  string input;

  while (true) {
    cout << "Please enter a " << item << " (e.g. ";
    for (int i = 0; i < min(4, static_cast<int>(validInputs.size())); ++i) cout << (i != 0 ? ", " : "") << validInputs[i];
    cout << "):" << endl;

    if (!(cin >> input)) exit(0);

    // in-place conversion of input to lowercase
    if(validInputs != validPieces) transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

    for (const auto& s: validInputs) {
      if (input == s) {
        return input;
      }
    }
    cout << "Invalid input. Try again." << endl;
  }
}
