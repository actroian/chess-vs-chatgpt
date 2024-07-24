#include "L1.h"

L1::L1(bool isWhite) : Player{isWhite} {}

Move L1::chooseMove(unique_ptr<Board>& b) {
    vector<Move> allMoves = possibleMoves(b);
    int randomMove = rand() % allMoves.size();
    return allMoves[randomMove];
}