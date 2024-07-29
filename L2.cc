#include "L2.h"
#include "player.h"
using namespace std;

L2::L2(bool isWhite) : L1{isWhite} {}

unique_ptr<Move> L2::chooseMove(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> captures = captureMoves(b, p2);
    // vector<Move> checks = checkMoves(b);

    // // Randomly capture or check
    int select = rand() % 2;
    int randomMove;

    /*        Actual Implementation            */
    if (select && !captures.empty()) {
        randomMove = rand() % captures.size();
        return std::move(captures[randomMove]);
    }
    // else if (!checks.empty()) {
    //     randomMove = rand() % checks.size();
    //     return checks[randomMove];
    // }
        
    return L1::chooseMove(b, p2);
}
vector<unique_ptr<Move>> L2::captureMoves(unique_ptr<Board>& b, Player* p2) {
    // Implementation of getting capture moves for L2
    vector<unique_ptr<Move>> captures;
    vector<unique_ptr<Move>> allMoves = possibleMoves(b, p2);
    
    for (auto it = allMoves.begin(); it != allMoves.end(); ) {
        if (b->at((*it)->start.first, (*it)->start.second) != nullptr &&
            b->at((*it)->end.first, (*it)->end.second) != nullptr &&
            b->at((*it)->end.first, (*it)->end.second)->isWhitePiece() != isWhite) {
            captures.push_back(std::move(*it));
            it = allMoves.erase(it); // Erase the moved element and advance the iterator
        } else {
            ++it;
        }
    }

    return captures;
}

vector<unique_ptr<Move>> L2::checkMoves(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> checks;
    vector<unique_ptr<Move>> allMoves = possibleMoves(b, p2);

    for (const auto& move : allMoves) {

        if(b->at(move->start.first, move->start.second) != nullptr) {
           // TODO: After Move Refactor
        }
    }

    return checks;
}
