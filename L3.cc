#include "L3.h"

L3::L3(bool isWhite) : L2{isWhite} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    vector<Move> avoid = avoidCaptureMoves(b);
    int randomMove;

    if (!avoid.empty()) {
        randomMove = rand() % avoid.size();
        return avoid[randomMove];
    }
    L2::chooseMove(b);
    
}

vector<Move> L3::avoidCaptureMoves(unique_ptr<Board>& b) {
    // Implementation of getting avoid capture moves for L3
    vector<Move> allMoves = possibleMoves(b);
    vector<Move> avoid;

    for(const auto& move : allMoves) {
        // check if current square is being attacked by opponent pieces?
    }

    return avoid;
}
