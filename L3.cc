#include "L3.h"
#include "player.h"

using namespace std;

L3::L3(bool isWhite) : L2{isWhite} {}

unique_ptr<Move> L3::chooseMove(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> avoid = avoidCaptureMoves(b, p2);
    int randomMove;

    cout << "Number of Avoid: " << avoid.size() << endl;

    if (!avoid.empty()) {
        randomMove = rand() % avoid.size();
        return std::move(avoid[randomMove]);
    }
    return L2::chooseMove(b, p2);
    
}

vector<unique_ptr<Move>> L3::avoidCaptureMoves(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> avoid;

    vector<pair<int, int>> myPos = getMyPiecePositions(b, isWhite);
    vector<unique_ptr<Move>> otherPlayersMoves = p2->possibleMoves(b, p2, false);

    // Vector to store capture positions
    vector<pair<int, int>> capturePositions;

    // Fill capturePositions with positions from otherPlayersMoves
    for (const auto& move : otherPlayersMoves) {
        for (const auto& pos : myPos) {
            if (move->end.first == pos.first && move->end.second == pos.second) {
                // Check if the position is already in capturePositions
                bool found = false;
                for (const auto& capturePos : capturePositions) {
                    if (capturePos == make_pair(pos.first, pos.second)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    capturePositions.push_back(make_pair(pos.first, pos.second));
                }
            }
        }
    }

    vector<unique_ptr<Move>> myMoves = possibleMoves(b, p2, false);

    cout << "How many positions are capturable: " << capturePositions.size() << endl;

    vector<unique_ptr<Move>> possibleAvoidMoves;
    for (auto& move : myMoves) {
        for (const auto& capturePos : capturePositions) {
            if (move->start.first == capturePos.first && move->start.second == capturePos.second) {
                possibleAvoidMoves.push_back(std::move(move));
            }
        }
    }

    return possibleAvoidMoves;

    //TODO: Check if the ending of my move is also not being attack

    // for (auto& posMove: possibleAvoidMoves) {
    //     for (const auto& oppMove : otherPlayersMoves) {
    //         if(oppMove->end.first == posMove->end.first && oppMove->end.second == posMove->end.second) {
    //             // not a valid move
    //             break;
    //         }
    //         avoid.push_back(std::move(posMove));
    //     }
    // }

    // return avoid;
}