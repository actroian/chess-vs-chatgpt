#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>
#include <map>

extern std::vector<const std::string> pieceSymbols;
extern std::vector<const std::string> boardLocations;
extern std::vector<const std::string> validColours;
extern std::map<const std::string, std::pair<int,int>> posToInd;
extern std::vector<const std::string> validPlayers;

void initializePosToInd();
std::string getInput(const std::string&, std::vector<const std::string>&);

#endif