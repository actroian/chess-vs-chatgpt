#include "L1.h"

using namespace std;

L1::L1(bool isWhite) : Player{isWhite} {}

unique_ptr<Move> L1::chooseMove(unique_ptr<Board>& b) {
    vector<unique_ptr<Move>> allMoves = possibleMoves(b);
    int randomMove = rand() % allMoves.size();
    return std::move(allMoves[randomMove]);
}