#include "enpassantmove.h"
using namespace std;

EnpassantMove::EnpassantMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& captured_position, char captured_piece)
    : Move(start, end, captured_piece), captured_position(captured_position) {}

bool EnpassantMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent, bool isPromotionMove) const {
    board->placePiece(end.first, end.second, std::move(board->at(start.first, start.second)));
    board->removePiece(start.first, start.second);
    board->removePiece(captured_position.first, captured_position.second);
    if(movingplayer->kingInCheck(board, movingplayer, opponent)){
        // Undo the move if it puts the king in check
        board->placePiece(start.first, start.second, std::move(board->at(end.first, end.second)));
        if (captured_piece != '\0') {
            string piece = string{captured_piece};
            board->placePiece(captured_position.first, captured_position.second, board->createPiece(piece, captured_position));
        }
        return false;
    }
    return true;
}

void EnpassantMove::undo(Board& board) {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        string piece = string{captured_piece};
        board.placePiece(captured_position.first, captured_position.second, board.createPiece(piece, captured_position));
    }
    board.removePiece(end.first, end.second);
}

bool EnpassantMove::operator==(const Move& other) const {
    const EnpassantMove* o = dynamic_cast<const EnpassantMove*>(&other);
    return o && Move::operator==(other) && captured_position == o->captured_position;
}

bool EnpassantMove::operator!=(const Move& other) const {
    return !(*this == other);
}

