#include "L1.h"
#include "player.h"
using namespace std;

L1::L1(bool isWhite) : Player{isWhite} {}

unique_ptr<Move> L1::chooseMove(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> allMoves = possibleMoves(b, p2);
    if(!allMoves.empty()){
    int randomMove = rand() % allMoves.size();
    return std::move(allMoves[randomMove]);
    }
    return nullptr;
}