#include "normalmove.h"
using namespace std;

NormalMove::NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece, bool first_piece_move, bool captured_unmoved)
    : Move(start, end, captured_piece), first_piece_move{first_piece_move}, captured_unmoved{captured_unmoved} {}

bool NormalMove::move(unique_ptr<Board>& board, Player* p1, Player* p2, bool isPromotionMove) const {
    board->placePiece(end.first, end.second, std::move(board->at(start.first, start.second)));
    board->removePiece(start.first, start.second);
    if(p1->kingInCheck(board, p1, p2)){
        return false;
    }
    board->at(end.first, end.second)->setUnmoved(first_piece_move);
    return true;
}

void NormalMove::undo(Board& board) {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        string piece = string{captured_piece};
        board.placePiece(end.first, end.second, board.createPiece(piece, end));
        board.at(end.first, end.second)->setUnmoved(captured_unmoved);
    } else {
        board.removePiece(end.first, end.second);
    }
}

bool NormalMove::operator==(const Move& other) const {
    return Move::operator==(other);
}

bool NormalMove::operator!=(const Move& other) const {
    return !(*this == other);
}

