#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>
#include <map>
#include "move.h"
#include "piece.h"
#include "normalmove.h"
#include "castlemove.h"
#include "enpassantmove.h"
#include "promotionmove.h"

class Move;
class Piece;

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
void emplaceNormalMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, bool first_piece_move = false, Piece* capturedPiece = nullptr);
void emplaceEnpassantMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& capturedPosition, char capturedPiece);
void emplacePromotionMove(std::vector<std::unique_ptr<Move>>& moves, const std::pair<int, int>& start, const std::pair<int, int>& end, char promotedTo, char capturedPiece = '\0');

#endif
