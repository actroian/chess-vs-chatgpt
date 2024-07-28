#include "L3.h"

L3::L3(bool isWhite) : L2{isWhite} {}

unique_ptr<Move> L3::chooseMove(unique_ptr<Board>& b) {
    vector<unique_ptr<Move>> avoid = avoidCaptureMoves(b);
    int randomMove;

    if (!avoid.empty()) {
        randomMove = rand() % avoid.size();
        return std::move(avoid[randomMove]);
    }
    L2::chooseMove(b);
    
}

vector<unique_ptr<Move>> L3::avoidCaptureMoves(unique_ptr<Board>& b) {
    // Implementation of getting avoid capture moves for L3
    vector<unique_ptr<Move>> allMoves = possibleMoves(b);
    vector<unique_ptr<Move>> avoid;

    for(const auto& move : allMoves) {
        // check if current square is being attacked by opponent pieces?
    }

    return avoid;
}
