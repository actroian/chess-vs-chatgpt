#include "human.h"
using namespace std;

Human::Human(bool isWhite): Player{isWhite, false} {}

unique_ptr<Move> Human::chooseMove(unique_ptr<Board>& b, Player* p2) {
    string startLoc = getInput("location of piece you want to move", boardLocations);
    string endLoc = getInput("location you want to move the piece to", boardLocations);
  
    auto start = posToInd[startLoc];
    auto end = posToInd[endLoc];

    return std::make_unique<NormalMove>(start, end);
}
