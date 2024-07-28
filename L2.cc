#include "L2.h"

using namespace std;

L2::L2(bool isWhite) : L1{isWhite} {}

Move L2::chooseMove(unique_ptr<Board>& b) {
    vector<Move> captures = captureMoves(b);
    // vector<Move> checks = checkMoves(b);

    // // Randomly capture or check
    int select = rand() % 2;
    int randomMove;

    /*        Actual Implementation            */
    if (select && !captures.empty()) {
        randomMove = rand() % captures.size();
        return captures[randomMove];
    }
    // else if (!checks.empty()) {
    //     randomMove = rand() % checks.size();
    //     return checks[randomMove];
    // }
        
    return L1::chooseMove(b);
}

vector<Move> L2::captureMoves(unique_ptr<Board>& b) {
    // Implementation of getting capture moves for L2
    vector<Move> captures;
    vector<Move> allMoves = possibleMoves(b);
    
    for(const auto& move : allMoves) {
        // Ensure the start position has a piece and the end position is not empty
        if(b->at(move.start.first, move.start.second) != nullptr &&
           b->at(move.end.first, move.end.second) != nullptr &&
           b->at(move.end.first, move.end.second)->isWhitePiece() != isWhite) {
            captures.push_back(move);
        }
    }
    return captures;
}

vector<Move> L2::checkMoves(unique_ptr<Board>& b) {
    vector<Move> checks;
    vector<Move> allMoves = possibleMoves(b);

    for (const auto& move : allMoves) {

        if(b->at(move.start.first, move.start.second) != nullptr) {
           // TODO: After Move Refactor
        }
    }

    return checks;
}
