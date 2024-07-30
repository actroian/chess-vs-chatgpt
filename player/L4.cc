#include "L4.h"
#include "player.h"

using namespace std;

L4::L4(bool isWhite) : L3{isWhite} {}

unique_ptr<Move> L4::chooseMove(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> captures = smartCapture(b, p2);

    if (!captures.empty()) {
        int randomMove = rand() % captures.size();
        return std::move(captures[randomMove]);
    }
    return L3::chooseMove(b, p2);
}

vector<unique_ptr<Move>> L4::smartCapture(unique_ptr<Board>& b, Player* p2) {
    vector<unique_ptr<Move>> captures = L2::captureMoves(b, p2);
    vector<unique_ptr<Move>> goodMoves;

    // Define piece values
    unordered_map<char, int> pieceValues = {
        {'p', 1},
        {'n', 3},
        {'b', 3},
        {'r', 5},
        {'q', 9}
    };

    // Only checks if there are multiple pieces to capture
    if(captures.size() >= 2) {
        int maxValue = 0;

        for(auto& move : captures) {
            // Get piece
            auto& piece = b->at(move->end.first, move->end.second);
            if (piece != nullptr) {
                char pieceType = piece->getSymbol();
                int pieceValue = pieceValues[tolower(pieceType)];
                maxValue = max(maxValue, pieceValue);
            }   

        }

        // Filter and add moves that capture the highest value pieces
        for (auto& move : captures) {
            int enemyValue = 0;

            auto& enemyPiece = b->at(move->end.first, move->end.second);
            if (enemyPiece != nullptr) {
                char pieceType = enemyPiece->getSymbol();
                enemyValue = pieceValues[tolower(pieceType)];
                
            }
            if (enemyValue == maxValue) {
                    goodMoves.push_back(std::move(move));
                }
        }
    }
    return goodMoves;
}