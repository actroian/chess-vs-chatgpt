#include "L3.h"

L3::L3(bool isWhite) : L2{isWhite} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    // Ensure random numbers are generated differently
    srand(static_cast<unsigned int>(std::time(0)));

    vector<Move> avoid = avoidCaptureMoves(b);

    // Randomly capture or check
    int select = rand() % 2;
    int randomMove;

    if (select && !avoid.empty()) {
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
