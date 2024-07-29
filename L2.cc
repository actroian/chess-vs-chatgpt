#include "L2.h"
#include "player.h"
using namespace std;

L2::L2(bool isWhite) : L1(isWhite) {}

unique_ptr<Move> L2::chooseMove(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> checks = checkMoves(b, p2);
    vector<unique_ptr<Move>> captures = captureMoves(b, p2);

    int select = rand() % 2;
    int randomMove;

    cout << "Number of Check Moves: " << checks.size() << endl;

    if(!checks.empty()) {
        randomMove = rand() % checks.size();
        return std::move(checks[randomMove]);
    }

    /* Actual Implementation */

    if(select && !captures.empty()) {
        randomMove = rand() % captures.size();
        return std::move(captures[randomMove]);
    }
    else if (!checks.empty()) {
        randomMove = rand() % checks.size();
        return std::move(checks[randomMove]);
    }

    return L1::chooseMove(b, p2);
}

vector<unique_ptr<Move>> L2::captureMoves(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> captures;
    vector<unique_ptr<Move>> allMoves = possibleMoves(b, p2);
    
    for (auto it = allMoves.begin(); it != allMoves.end(); ) {
        if (b->at((*it)->start.first, (*it)->start.second) != nullptr &&
            b->at((*it)->end.first, (*it)->end.second) != nullptr &&
            b->at((*it)->end.first, (*it)->end.second)->isWhitePiece() != isWhite) {
            captures.push_back(std::move(*it));
            it = allMoves.erase(it);
        } else {
            ++it;
        }
    }

    return captures;
}

vector<unique_ptr<Move>> L2::checkMoves(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> checks;
    vector<unique_ptr<Move>> allMoves = possibleMoves(b, p2);

    for (auto& move : allMoves) {
        if(move != nullptr){
        move->move(b, this, p2);

        bool isMoved = false;
        
        if (this->kingInCheck(b, this, p2)) {
            move->undo(*b);
            isMoved = true;
            checks.push_back(std::move(move));
        }
        if(!isMoved){
            move->undo(*b);
        }}
    }
    return checks;
}