#include "L1.h"

using namespace std;

L1::L1(bool isWhite) : Player{isWhite} {}

Move L1::chooseMove(unique_ptr<Board>& b) {
    // Ensures that seed is done once per program
    static bool seeded = false;
    if (!seeded) {
        int seed = getpid();
        srand(seed);
        seeded = true;
    }

    vector<Move> allMoves = possibleMoves(b);
    int randomMove = rand() % allMoves.size();
    return allMoves[randomMove];
}