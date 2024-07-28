#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>
#include <map>

class Move;

extern std::vector<const std::string> validPieces;
extern std::vector<const std::string> boardLocations;
extern std::vector<const std::string> validColours;
extern std::map<const std::string, std::pair<int,int>> posToInd;
extern std::map<const std::pair<int,int>, std::string> indToPos;
extern std::vector<const std::string> validPlayers;
extern std::vector<const std::string> validSetupCommands;
extern std::vector<const std::string> validPromotions;
extern std::vector<const std::string> validMainCommands;

void initializePosToInd();
std::string getInput(const std::string&, std::vector<const std::string>&);
#endif
