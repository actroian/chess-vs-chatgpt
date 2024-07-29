#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>
#include <map>

class Move;

extern std::vector<std::string> validPieces;
extern std::vector<std::string> boardLocations;
extern std::vector<std::string> validColours;
extern std::map<std::string, std::pair<int,int>> posToInd;
extern std::map<std::pair<int,int>, std::string> indToPos;
extern std::vector<std::string> validPlayers;
extern std::vector<std::string> validSetupCommands;
extern std::vector<std::string> validPromotions;
extern std::vector<std::string> validMainCommands;

void initializePosToInd();
std::string getInput(const std::string&, std::vector<std::string>&);
#endif
